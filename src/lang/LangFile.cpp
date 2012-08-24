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

namespace genie
{
  
//------------------------------------------------------------------------------
LangFile::LangFile() 
{
  pfile_ = 0;
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
  pfile_ = pcr_read_file(fileName);
}

//------------------------------------------------------------------------------
void LangFile::saveAs(const char *fileName) throw (std::ios_base::failure)
{
  pcr_write_file(fileName, pfile_);
}

std::string LangFile::getUtf8String(unsigned int id)
{
  struct enc_string eStr = pcr_get_string(pfile_, id, 0); //TODO language?
  
  //TODO encode to utf8.
  
  return std::string(eStr.string->str);
}

void LangFile::setUtf8String(unsigned int id, std::string str)
{
  //TODO encode from utf8
  
  pcr_set_string(pfile_, id, 0, str.c_str()); //TODO language?
}
  
//------------------------------------------------------------------------------
void LangFile::unload(void)
{
  if (pfile_)
    pcr_free(pfile_);
  
  pfile_ = 0;
}

}