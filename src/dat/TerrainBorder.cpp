/*
    genie/dat - A library for reading and writing data files of genie
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


#include "genie/dat/TerrainBorder.h"

namespace genie
{

TerrainBorder::TerrainBorder() : Colors(3)
{
}

TerrainBorder::~TerrainBorder()
{
}

unsigned int TerrainBorder::getNameSize()
{
  return 13;
}

unsigned int TerrainBorder::getUnknown3Size()
{
  return 1410;
}

void TerrainBorder::serializeObject(void )
{ 
  //serialize<short>(Unknown1);
  serialize<short>(Enabled);
  
  serialize<std::string>(Name, getNameSize());
  serialize<std::string>(Name2, getNameSize());
  
  serialize<long>(RessourceID);
  
  serialize<long>(Unknown3);
  serialize<long>(Unknown4);
  
  serialize<char>(Colors, 3);
  
  serialize<char>(Unknown5);
  
  serialize<long>(Unknown6);
  serialize<long>(Unknown7);
  
  serializeSub<TBFrameData>(Frames, 230);
  
  serialize<short>(FrameCount);
  
  serialize<short>(Unknown8);
  serialize<short>(Unknown9);
  serialize<short>(Unknown10);
}


TBFrameData::TBFrameData()
{
  
}

TBFrameData::~TBFrameData()
{
  
}

void TBFrameData::serializeObject(void )
{
  serialize<short>(FrameID);
  serialize<short>(Flag1);
  serialize<short>(Flag2);
}

}
