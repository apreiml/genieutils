/*
    genieutils - <description>
    Copyright (C) 2011  Armin Preiml <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "genie/lang/LangFile.h"

#include <sstream>

#include <iconv.h>
#include <errno.h>

#include "pcrio/pcrio.h"

namespace genie
{
  
const char *LangFile::CONV_DEFAULT_CHARSET = "UTF-8";
  
Logger& LangFile::log = Logger::getLogger("freeaoe.DrsFile");

//------------------------------------------------------------------------------
LangFile::LangFile() 
{
  pfile_ = 0;
  
  default_culture_id_ = 0;
  default_codepage_ = 0;
  
  system_default_charset_ = CONV_DEFAULT_CHARSET;
}
  
//------------------------------------------------------------------------------
LangFile::~LangFile() 
{
  if (to_default_charset_cd_)
    iconv_close(to_default_charset_cd_);
  
  if (from_default_charset_cd_)
    iconv_close(from_default_charset_cd_);
  
  if (pfile_)
    pcr_free(pfile_);
}

//------------------------------------------------------------------------------
void LangFile::load(const char *filename) throw (std::ios_base::failure)
{
  pcr_error_code error_code_ = PCR_ERROR_NONE;  
  
  setFileName(filename);
  
  log.info("-------");
  log.info("Loading \"%s\"", filename);
  
  if (pfile_)
    pcr_free(pfile_);
  
  pfile_ = pcr_read_file(filename, &error_code_);
  
  if (PCR_FAILURE(error_code_))
  {
    pcr_free(pfile_);
    pfile_ = 0;
    
    throw std::ios_base::failure("Load: Can't load file: " + std::string(filename) +
      ": Error: " + std::string(pcr_error_message(error_code_)));
  }
  else
  {
    std::stringstream c_name;
    
    const struct culture_info_array *culture_info_array = pcr_get_culture_info(pfile_);
    struct culture_info *ci_ptr = NULL;
    
    if (culture_info_array->count == 0)
      throw std::string("No culture info! Corrupt file?: ") + std::string(filename);
    
    ci_ptr = &culture_info_array->array[0];
    
    if (culture_info_array->count > 1)
    {
      log.warn("More than one culture in %s! Using the most common clulture!", filename);
      
      for (uint32_t i=0; i<culture_info_array->count; i++)
        if (ci_ptr->item_count < culture_info_array->array[i].item_count)
          ci_ptr = &culture_info_array->array[i];
      
    }
    
    default_culture_id_ = ci_ptr->id;
    default_codepage_ = ci_ptr->codepage;
    
    log.info("Culture Id: %d, Codepage: %d.", default_culture_id_, default_codepage_); 
  
    if (default_codepage_ > 0)
    {
      c_name << "WINDOWS-" << default_codepage_;
     
      log.info("Loading \"%s\" charset converter description.", c_name.str().c_str());
      
      to_default_charset_cd_ = iconv_open(system_default_charset_.c_str(), c_name.str().c_str());
      from_default_charset_cd_ = iconv_open(c_name.str().c_str(), system_default_charset_.c_str());
      
      std::cout << c_name.str().c_str() << std::endl;
      
      if (to_default_charset_cd_ == (iconv_t) - 1 || from_default_charset_cd_ == (iconv_t)-1)
        throw std::string("Cannot open default converter.");
    }
    else
      log.info("Codepage: 0");
  }
}

//------------------------------------------------------------------------------
void LangFile::saveAs(const char *filename) throw (std::ios_base::failure)
{
  pcr_error_code error_code_ = PCR_ERROR_NONE;
  
  if (pfile_ == 0)
    throw std::ios_base::failure("Save: Can't save unloaded file: "
                                 + std::string(filename));
  
  pcr_write_file(filename, pfile_, &error_code_);
  
  if (PCR_FAILURE(error_code_))
    throw std::ios_base::failure("Save: Cant write file: \"" + std::string(filename));
}

//----------------------------------------------------------------------------
std::string LangFile::getString(unsigned int id)
{
  pcr_string e_str;
  
  log.info("%s: getString(%d);", getFileName(), id);
  
  e_str = pcr_get_string(pfile_, id, default_culture_id_);
  
  if (e_str.value == 0)
  {
    log.debug("%s: String [%d] not found!", getFileName(), id);
    return std::string("");
  }
  
  std::string encoded_str, decoded_str;
  
  encoded_str = std::string(e_str.value, e_str.size);
  
  decoded_str = convert_from(encoded_str, e_str.codepage);
  
  pcr_free_string_value (e_str);
  
  log.info("| Result: \"%s\"", decoded_str.c_str());
  
  return decoded_str;
}

//----------------------------------------------------------------------------
void LangFile::setString(unsigned int id, std::string str)
{
  pcr_string e_str;
  std::string encoded_str;
  size_t encoded_c_str_size = 0;
  
  log.info("%s: setString(%d, %s);", getFileName(), id, str.c_str());
  
  encoded_str = convert_to(str, default_codepage_);
  
  log.info("| Convert from \"%s\" to \"%s\".", str.c_str(), encoded_str.c_str());
  
  encoded_c_str_size = strlen(encoded_str.c_str());
  
  e_str.value = new char[encoded_c_str_size];
  strncpy(e_str.value, encoded_str.c_str(), encoded_c_str_size);
  
  e_str.size = encoded_c_str_size;
  e_str.codepage = default_codepage_;
  
  pcr_set_string(pfile_, id, default_culture_id_, e_str); 
  
  delete [] e_str.value;
}
  
void LangFile::setDefaultCharset(const char *charset)
{
  system_default_charset_ = std::string(charset);
}
  
//----------------------------------------------------------------------------
void LangFile::unload(void)
{
  if (pfile_)
    pcr_free(pfile_);
  
  pfile_ = 0;
}

//----------------------------------------------------------------------------
std::string LangFile::convert_to(std::string in, uint32_t codepage)
{
  iconv_t cd;
  std::string encoded_str;
  
  if (codepage == 0)
    return in;
  
  if (codepage == default_codepage_)
    cd = from_default_charset_cd_;
  else
  {
    
    std::stringstream conv_name;
    
    conv_name << "WINDOWS-" << codepage;
    
    if ((cd = iconv_open(conv_name.str().c_str(), system_default_charset_.c_str())) == (iconv_t)(-1))
    {
      std::string error = "Cannot open converter from " + system_default_charset_ +
                          " to " + conv_name.str();
                          
      throw error;
    }
  }
  
  encoded_str = convert(cd, in);
  
  if (codepage != default_codepage_)
    iconv_close(cd);
  
  return encoded_str;
}

//----------------------------------------------------------------------------
std::string LangFile::convert_from(std::string in, uint32_t codepage)
{
  iconv_t cd;
  std::string decoded_str;
  
  if (codepage == 0)
    return in;
  
  if (codepage == default_codepage_)
    cd = to_default_charset_cd_;
  else
  {
    
    std::stringstream conv_name;
    
    conv_name << "WINDOWS-" << codepage;
    
    if ((cd = iconv_open(system_default_charset_.c_str(), conv_name.str().c_str())) == (iconv_t)(-1))
    {
      std::string error = "Cannot open converter from " + conv_name.str() +
                          " to " + system_default_charset_;
                          
      throw error;
    }
  }
  
  decoded_str = convert(cd, in);
  
  if (codepage != default_codepage_)
    iconv_close(cd);
  
  return decoded_str;
}
  
//----------------------------------------------------------------------------
std::string LangFile::convert(iconv_t cd, std::string input)
{
  size_t inleft = input.size();
  char *inbuf = new char[inleft];
  char *inptr = inbuf;
  
  char buf[CONV_BUF_SIZE];
  size_t outleft = CONV_BUF_SIZE, iconv_value = 0;
  char *outptr = buf;

  std::string decoded_str;
  
  strncpy(inbuf, input.c_str(), inleft);
  
  while (cd != (iconv_t)-1 && inleft > 0 && iconv_value == 0)
  { 
    iconv_value = iconv(cd, &inptr, &inleft, &outptr, &outleft);
    
    if (iconv_value == (size_t)-1) 
    {
      if(errno == E2BIG)
      {
        decoded_str += std::string(buf, CONV_BUF_SIZE);
        outleft = CONV_BUF_SIZE;
        outptr = buf;
        iconv_value = 0;
      }
      else  
      {
        delete (inbuf);
        
        std::string error("Error in converting characters: ");

        if(errno == EILSEQ)
          error += "EILSEQ";
        if(errno == EINVAL)
          error += "EINVAL";
        
        log.error("%s", error.c_str());
        
        throw error;
      }
    }
    else
      decoded_str += std::string(buf, CONV_BUF_SIZE - outleft);
      
  }
  
  delete (inbuf);
  
  return decoded_str;
}

}
