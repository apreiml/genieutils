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

#ifndef GENIE_ICOMPRESSED_FILE_H
#define GENIE_ICOMPRESSED_FILE_H

#include "IFile.h"

namespace genie
{
 
class ICompressedFile : public IFile
{
public:
  ICompressedFile();
  virtual ~ICompressedFile();
  /*
  virtual void open(const char*filename);
  
  void open(const char *filename, bool compressed=true);
  
  virtual void save();
  
  virtual void saveAs(const char *filename);
  
  virtual void close(void ); */
};
  
}

#endif // GENIE_ICOMPRESSED_FILE_H