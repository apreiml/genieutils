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

#include "genie/file/IFile.h"
#include <fstream>

namespace genie
{

//------------------------------------------------------------------------------
IFile::IFile()
{
}

//------------------------------------------------------------------------------
IFile::~IFile()
{
}
  
//------------------------------------------------------------------------------
void IFile::setFilename(const char *filename)
{
  filename_ = std::string(filename);
}
  
//------------------------------------------------------------------------------
const char *IFile::getFilename(void) const
{
  return filename_.c_str();
}
  
//------------------------------------------------------------------------------
void IFile::load() throw (std::ios_base::failure)
{
  if (filename_.empty())
    throw std::ios_base::failure("File name not set");
  
  load(filename_.c_str());
}

//------------------------------------------------------------------------------
void IFile::load(const char *filename) throw (std::ios_base::failure)
{
  filename_ = std::string(filename);
  
  std::ifstream file;
  

  file.open(filename, std::ifstream::binary);
  
  if (file.fail())
  {
    file.close();
    throw std::ios_base::failure("Cant read file: \"" + filename_ + "\"");
  }
  else
    readObject(file);
  
  file.close();
}

//------------------------------------------------------------------------------
void IFile::save(void ) throw (std::ios_base::failure)
{
  if (filename_.empty())
    throw std::ios_base::failure("File name not set");
  
  saveAs(filename_.c_str());
}

//------------------------------------------------------------------------------
void IFile::saveAs(const char *filename) throw (std::ios_base::failure)
{
  std::ofstream file;
  
  file.open(filename, std::ofstream::binary);
  
  if (file.fail())
  {
    file.close();
    throw std::ios_base::failure("Cant write to file: \"" + 
                                std::string(filename) + "\"");
  }
  else
    writeObject(file);
  
  file.close();
}
  
}