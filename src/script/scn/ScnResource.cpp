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

#include "genie/script/scn/ScnResource.h"

#include <fstream>

namespace genie
{
  
ScnResource::ScnResource()
{
  instructionsStringTable = 0;
  hintsStringTable = 0;
  victoryStringTable = 0;
  lossStringTable = 0;
  historyStringTable = 0;
  scoutsStringTable = 0;
  
  bitmapIncluded = 0;
  bitmapWidth = 0;
  bitmapHeigth = 0;
  unknown1 = 1;
  
  bitmapByteSize = 0;
  bitmap = 0;
}

ScnResource::~ScnResource()
{
  delete bitmap;
}

void ScnResource::serializeObject(void)
{
  std::cout << "Resource start pos: " << tellg() << std::endl;
  
  if (getGameVersion() >= genie::GV_AoK)
  {
    serialize<uint32_t>(instructionsStringTable);
    serialize<uint32_t>(hintsStringTable);
    serialize<uint32_t>(victoryStringTable);
    serialize<uint32_t>(lossStringTable);
    serialize<uint32_t>(historyStringTable);
    
    if (getGameVersion() >= genie::GV_TC)
      serialize<uint32_t>(scoutsStringTable);
  }
  
  serializeSizedString<uint16_t>(instructions);
  serializeSizedString<uint16_t>(hints);
  serializeSizedString<uint16_t>(victory);
  serializeSizedString<uint16_t>(loss);
  serializeSizedString<uint16_t>(history);
  
  if (getGameVersion() >= genie::GV_TC)
    serializeSizedString<uint16_t>(scouts);
  
  serializeSizedString<uint16_t>(pregameCinematicFilename);
  serializeSizedString<uint16_t>(victoryCinematicFilename);
  serializeSizedString<uint16_t>(lossCinematicFilename);
  serializeSizedString<uint16_t>(backgroundFilename);
   
  serializeBitmap();
}

void ScnResource::serializeBitmap(void)
{
  serialize<uint32_t>(bitmapIncluded);
  
  serialize<uint32_t>(bitmapWidth);
  serialize<uint32_t>(bitmapHeigth);
  serialize<int16_t>(unknown1);
  
  if (bitmapIncluded == 0)
    return;
      
  if (isOperation(OP_READ))
  {
//     BitmapInfoHeader bmpHeader;
    
//     serialize<BitmapInfoHeader>(bmpHeader);

// TODO generate 1. bitmap header

    char *bmpHeader = 0;
    
    serialize<char>(&bmpHeader, 0x28); //TODO header size constant (or read!!)
    
    bitmapByteSize = *reinterpret_cast<uint32_t *>(bmpHeader + 20);
    
    bitmap = new char[bitmapByteSize];
    
//     strncpy(bitmap, bmpHeader, 0x28);
    for (unsigned int i=0; i < 0x28; i++)
      bitmap[i] = bmpHeader[i];
    
    char *bitmapStart = (bitmap + 0x28);
    
    serialize<char>(&bitmapStart, bitmapByteSize - 0x28);
    
    /*
    if (bmpHeader.headerSize != 0x28)
      std::cerr << "ScnResource: Unknown header size!" << std::endl;
    
    bitmap = new char[bmpHeader.bmpByteSize];
    
    char *bitmapStart = (bitmap + bmpHeader.headerSize);
    
    strncpy(bitmap, reinterpret_cast<char *>(&bmpHeader), bmpHeader.headerSize);
    
    serialize<char>(&bitmapStart, bmpHeader.bmpByteSize - bmpHeader.headerSize);
    
//     serialize<uint8_t>(&bitmap, bmpHeader.bmpByteSize - bmpHeader.headerSize);*/
  }
}

}