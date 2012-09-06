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

#include <unicode/ucnv.h>
#include <sstream>

namespace genie
{
  
//------------------------------------------------------------------------------
LangFile::LangFile() 
{
  pfile_ = 0;
  error_code_ = PCR_ERROR_NONE;
}
  
//------------------------------------------------------------------------------
LangFile::~LangFile() 
{
  if (pfile_)
    pcr_free(pfile_);
}

//------------------------------------------------------------------------------
void LangFile::load(const char *fileName) throw (std::ios_base::failure)
{
  error_code_ = PCR_ERROR_NONE;  
  
  pfile_ = pcr_read_file(fileName, &error_code_);
  
  if (PCR_FAILURE(error_code_))
  {
    pcr_free(pfile_);
    pfile_ = 0;
    
    throw std::ios_base::failure("Load: Can't load file: " + std::string(fileName));
  }
}

//------------------------------------------------------------------------------
void LangFile::saveAs(const char *fileName) throw (std::ios_base::failure)
{
  if (PCR_FAILURE(error_code_) || pfile_ == 0)
    throw std::ios_base::failure("Save: Can't save flawed or unloaded file: "
                                 + std::string(fileName));
  
  pcr_write_file(fileName, pfile_, &error_code_);
  
  if (PCR_FAILURE(error_code_))
    throw std::ios_base::failure("Save: Cant write file: \"" + std::string(fileName));
}

//------------------------------------------------------------------------------
std::string LangFile::getString(unsigned int id)
{
  char *dest;
  std::string ret;
  std::stringstream c_name;
  struct enc_string e_str;
  UErrorCode err = U_ZERO_ERROR;
  
  e_str = pcr_get_string(pfile_, id, 0); //TODO language?
  
  c_name << "windows-" << e_str.codepage;
  
  dest = new char[e_str.string->size + 1];
  
  ucnv_convert("UTF-8", c_name.str().c_str(), dest, e_str.string->size + 1, 
               e_str.string->str, -1, &err);
  
  
  if (U_FAILURE(err))
  {
    std::cout << "Warning: Couldn't convert string!" << std::endl; //TODO ex
    ret = std::string(e_str.string->str);
  }
  else
    ret = std::string(dest);
  
  delete [] dest;
  
  return ret;
}

void LangFile::setString(unsigned int id, std::string str)
{
  char *dest;
  std::stringstream c_name;
  struct enc_string e_str;
  std::string new_str;
  UErrorCode err = U_ZERO_ERROR;
  
  e_str = pcr_get_string(pfile_, id, 0); //TODO language?
  
  c_name << "windows-" << e_str.codepage;
  
  dest = new char[str.size()];
  
  ucnv_convert(c_name.str().c_str(), "UTF-8", dest, str.size(), 
               str.c_str(), str.size(), &err);
  
  
  if (U_FAILURE(err))
  {
    std::cout << "Warning: Couldn't convert string!" << std::endl; //TODO ex
    new_str = str;
  }
  else
    new_str = std::string(dest);
  
  delete [] dest;
  
  pcr_set_string(pfile_, id, 0, new_str.c_str()); //TODO language?
}
  
//------------------------------------------------------------------------------
void LangFile::unload(void)
{
  if (pfile_)
    pcr_free(pfile_);
  
  pfile_ = 0;
}

}