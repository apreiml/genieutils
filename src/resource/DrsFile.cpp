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


#include "genie/resource/DrsFile.h"

#include <string>

#include "genie/util/Logger.h"

//#include <file/BinaFile.h>

namespace genie
{

using std::string;

Logger& DrsFile::log = Logger::getLogger("freeaoe.DrsFile");

//------------------------------------------------------------------------------
DrsFile::DrsFile()
{
  header_loaded_ = false;
}


//------------------------------------------------------------------------------
DrsFile::~DrsFile()
{
}

//------------------------------------------------------------------------------
SlpFilePtr DrsFile::getSlpFile(uint32_t id)
{
    slp_map_[id]->readObject(*getIStream());
    
    return slp_map_[id];
}
 
//------------------------------------------------------------------------------
void DrsFile::serializeObject(void)
{
  loadHeader();
}

//------------------------------------------------------------------------------
std::string DrsFile::getSlpTableHeader(void) const
{
  return " plsL";
}

//------------------------------------------------------------------------------
std::string DrsFile::getBinaryTableHeader(void) const
{
  return "anibd";
}

//------------------------------------------------------------------------------
void DrsFile::loadHeader()
{
  if (header_loaded_)
    log.warn("Trying to load header again!"); 
  else
  {
    string copy_right = readString(40);
    
    string version = readString(4);
    
    //File type
    string file_type = readString(12);
    
    num_of_tables_ = read<uint32_t>();
    header_offset_ = read<uint32_t>(); 
    
    // Load table data
    for (uint32_t i = 0; i < num_of_tables_; i++)
    {
      table_types_.push_back(readString(8));
      table_num_of_files_.push_back(read<uint32_t>());
    }
   
    // Load file headers
    for (uint32_t i = 0; i < num_of_tables_; i++)
    {
      for (uint32_t j = 0; j < table_num_of_files_[i]; j++)
      {
        uint32_t id = read<uint32_t>();
        uint32_t pos = read<uint32_t>();
        /*uint32_t len =*/ read<uint32_t>();
                
        if (table_types_[i].compare(getSlpTableHeader()) == 0)
        {
          SlpFilePtr slp(new SlpFile());
          slp->setInitialReadPosition(pos);
          
          slp_map_[id] = slp;
        }
        else
        {
          if (table_types_[i].compare(getBinaryTableHeader()) == 0)
          {
//             BinaFile *bina = new BinaFile(id, pos, len, file_.getIOStream());
//             resource_manager_->addBinaFile(bina);
          }
        }
        // else other TODO: Sounds
        
      }
    }
      
    header_loaded_ = true;
  }
}

}

