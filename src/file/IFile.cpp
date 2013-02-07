/*
    genieutils - <description>
    Copyright (C) 2011  Armin Preiml <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "genie/file/IFile.h"

namespace genie
{

//------------------------------------------------------------------------------
IFile::IFile()
{
  loaded_ = false;
}

//------------------------------------------------------------------------------
IFile::~IFile()
{
  fileIn_.close();
}
  
//------------------------------------------------------------------------------
void IFile::setFileName(const char *fileName)
{
  fileName_ = std::string(fileName);
}
  
//------------------------------------------------------------------------------
const char *IFile::getFileName(void) const
{
  return fileName_.c_str();
}
  
//------------------------------------------------------------------------------
void IFile::load() throw (std::ios_base::failure)
{
  if (fileName_.empty())
    throw std::ios_base::failure("Load: File name not set");
  
  load(fileName_.c_str());
}

//------------------------------------------------------------------------------
void IFile::load(const char *fileName) throw (std::ios_base::failure)
{
  if (loaded_)
  {
    unload();
    loaded_ = false;
  }
  
  fileName_ = std::string(fileName);
  
  fileIn_.close(); //TODO: necessary?
  
  fileIn_.open(fileName, std::ios::binary | std::ios::in);
  
  if (fileIn_.fail())
  {
    fileIn_.close();
    throw std::ios_base::failure("Cant read file: \"" + fileName_ + "\"");
  }
  else
  {
    readObject(fileIn_);
    loaded_ = true;
  }
}

//------------------------------------------------------------------------------
void IFile::save(void ) throw (std::ios_base::failure)
{
  if (fileName_.empty())
    throw std::ios_base::failure("Save: File name not set");
  
  saveAs(fileName_.c_str());
}

//------------------------------------------------------------------------------
void IFile::saveAs(const char *fileName) throw (std::ios_base::failure)
{
  std::ofstream file;
  
  file.open(fileName, std::ofstream::binary);
  
  if (file.fail())
  {
    file.close();
    throw std::ios_base::failure("Cant write to file: \"" + 
                                std::string(fileName) + "\"");
  }
  else
    writeObject(file);
  
  file.close();
}


//------------------------------------------------------------------------------
void IFile::unload(void)
{
}
  
}