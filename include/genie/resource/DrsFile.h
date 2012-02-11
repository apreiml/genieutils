/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

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


#ifndef GENIE_DRSFILE_H
#define GENIE_DRSFILE_H

#include <vector>
#include <map>
#include <stdint.h>

#include "genie/util/Logger.h"
#include "genie/file/IFile.h"
#include "SlpFile.h"

namespace genie
{

//------------------------------------------------------------------------------
/// Base class for .drs files
class DrsFile : public IFile
{

public:
  //----------------------------------------------------------------------------
  /// Default Constructor.
  ///
  //
  DrsFile();
  
  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~DrsFile();
    
  PalFilePtr pal_;
  
  SlpFilePtr getSlpFile(uint32_t id)
  {
    slp_map_[id]->readObject(*getIStream());
    
    return slp_map_[id];
  }
  
  
private:
  static Logger &log;
  
  bool header_loaded_;
  
  uint32_t num_of_tables_;
  uint32_t header_offset_;
  
  std::vector<std::string> table_types_;
  std::vector<uint32_t> table_num_of_files_;
  
  typedef std::map<uint32_t, SlpFilePtr> SlpMap;
  SlpMap slp_map_;
  
   //----------------------------------------------------------------------------
  /// Loads table and resource headers.
  //
  void loadHeader();
  
  virtual void serializeObject(void);
  
};

}

#endif // GENIE_DRSFILE_H
