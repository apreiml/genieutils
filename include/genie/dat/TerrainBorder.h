/*
    geniedat - A library for reading and writing data files of genie
               engine games.
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


#ifndef TERRAINBORDER_H
#define TERRAINBORDER_H
#include "genie/file/ISerializable.h"

namespace genie
{

class TBFrameData : public ISerializable
{
public:
  TBFrameData();
  virtual ~TBFrameData();
  
  virtual void serializeObject(void);
  
  short FrameID;
  short Flag1;
  short Flag2;
  
};
  
/// Seems to be unused in GV > RoR
class TerrainBorder : public ISerializable
{
public:
  TerrainBorder();
  virtual ~TerrainBorder();
  
  static unsigned int getNameSize();
  
  static unsigned int getUnknown3Size();
  
  virtual void serializeObject(void);
  
  short Enabled;
  
  /// Internal long name
  std::string Name;
  
  /// Internal SLP name
  std::string Name2;
  
  /// ID of the SLP Resource in BORDER.DRS
  long RessourceID; 
  
  long Unknown3; // 0
  long Unknown4; // -1
  
  std::vector<char> Colors;
  
  char Unknown5;
  long Unknown6; // 6 and 7 both zero, part of frame data?
  long Unknown7;
  
  std::vector<TBFrameData> Frames;
  
  short FrameCount; //?
  
  short Unknown8; // always 0
  short Unknown9;
  short Unknown10;
};

}

#endif // TERRAINBORDER_H
