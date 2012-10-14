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

#ifndef GENIE_LANGFILE_H
#define GENIE_LANGFILE_H

#include <genie/file/IFile.h>
#include <genie/util/Logger.h>
#include <pcrio/pcrio.h>
#include <iconv.h>

struct UConverter;

namespace genie
{

class LangFile : public IFile
{
  
public:
  LangFile();
  virtual ~LangFile();
  
  virtual void load(const char *fileName) throw (std::ios_base::failure);
  virtual void saveAs(const char *fileName) throw (std::ios_base::failure);
  
  // get/set strings in utf-8
  std::string getString(unsigned int id);
  void setString(unsigned int id, std::string str);
  
protected:
  
  virtual void unload(void);
  
  virtual void serializeObject(void) {}
  
private:
  
  static Logger &log;
  
  struct pcr_file *pfile_;
  pcr_error_code error_code_;
  
  uint32_t default_culture_id_;
  uint32_t default_codepage_;
  
  static const unsigned int CONV_BUF_SIZE = 7;
  static const char *CONV_DEFAULT_CHARSET;
  
  std::string system_default_charset_;  // all strings will converted from/to this charset
  
  iconv_t to_default_charset_cd_; 
  iconv_t from_default_charset_cd_; 
  
  /// Convert a utf8 string to codepage
  std::string convert_to(std::string in, uint32_t codepage);
  
  /// Convert a string from codepage to utf8
  std::string convert_from(std::string in, uint32_t codepage);
  
  std::string convert(iconv_t cd, std::string input);//char *in_ptr, size_t in_size);
};
  
}

#endif // GENIE_LANGFILE_H