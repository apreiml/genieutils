/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

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


#include "genie/resource/SlpFile.h"

#include <stdexcept>

#include "genie/resource/SlpFrame.h"
#include "genie/resource/PalFile.h"

namespace genie
{

Logger& SlpFile::log = Logger::getLogger("genie.SlpFile");

//------------------------------------------------------------------------------
SlpFile::SlpFile() : IFile()
{
  loaded_ = false;
}

//------------------------------------------------------------------------------
SlpFile::~SlpFile()
{
}

//------------------------------------------------------------------------------
void SlpFile::serializeObject(void)
{
  if (isOperation(OP_READ) && !loaded_)
  {
    loadFile();
  }
}

//------------------------------------------------------------------------------
void SlpFile::loadFile()
{
  readHeader();
  
  frames_.resize(num_frames_);
  
  // Load frame headers
  for (uint32_t i = 0; i < num_frames_; i++)
  {
    frames_[i] = SlpFramePtr(new SlpFrame());
    frames_[i]->loadHeader(*getIStream());
    frames_[i]->setSlpFilePos(getInitialReadPosition());
  }

  // Load frame content
  for (FrameVector::iterator it = frames_.begin(); it != frames_.end(); it ++)
  {
    (*it)->load(*getIStream());
  }
  
  loaded_ = true;
}

//------------------------------------------------------------------------------
void SlpFile::unload(void )
{
  if (!loaded_)
    log.warn("Trying to unload a not loaded slpfile!");
  
  frames_.clear();
  num_frames_ = 0;
  
  loaded_ = false;
}

//------------------------------------------------------------------------------
bool SlpFile::isLoaded(void ) const
{
  return loaded_;
}

//------------------------------------------------------------------------------
uint32_t SlpFile::getFrameCount()
{
  return num_frames_;
}

//------------------------------------------------------------------------------
// int32_t SlpFile::getId()
// {
//   return id_;
// }

//------------------------------------------------------------------------------
SlpFramePtr SlpFile::getFrame(uint32_t frame)
{
  if (frame >= frames_.size())
  {
    log.error("Trying to get frame [%u] from index out of range!", frame);
    throw std::out_of_range("getFrame()");
  }
  
  return frames_[frame];
}


//------------------------------------------------------------------------------
void SlpFile::readHeader()
{
  std::string version = readString(4);
  num_frames_ = read<uint32_t>();
  
  std::string comment = readString(24);
}

}
