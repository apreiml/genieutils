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
#include <pcrio/pcrio.h>

namespace genie
{

class LangFile : public IFile
{
  
public:
  LangFile();
  virtual ~LangFile();
  
  virtual void load(const char *fileName) throw (std::ios_base::failure);
  virtual void saveAs(const char *fileName) throw (std::ios_base::failure);
  
  std::string getUtf8String(unsigned int id);
  void setUtf8String(unsigned int id, std::string str);
  
protected:
  
  virtual void unload(void);
  
  virtual void serializeObject(void) {}
  
private:
  struct pcr_file *pfile_;
  
};
  
}

#endif // GENIE_LANGFILE_H