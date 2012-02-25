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

#include "genie/script/scn/ScnResource.h"

namespace genie
{

ScnResource::ScnResource()
{
}

ScnResource::~ScnResource()
{
}

void ScnResource::serializeObject(void)
{
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
  
  serialize<uint32_t>(bitmapIncluded);
  serialize<uint32_t>(bitmapWidth);
  serialize<int32_t>(bitmapHeigth);
  serialize<int16_t>(unknown1);
}

}