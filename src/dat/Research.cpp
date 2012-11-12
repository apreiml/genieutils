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


#include "genie/dat/Research.h"

namespace genie
{

//------------------------------------------------------------------------------
Research::Research() : RequiredTechs(getRequiredTechsSize(), -1),
                       ResourceCosts(getResourceCostsSize()),
                       Pointers(getPointersSize())
{
  RequiredTechCount = 0;
  Civ = -1;
  FullTechMode = 0;
  ResearchLocation = -1;
  LanguageDLLName = 7000;
  LanguageDLLDescription = 8000;
  ResearchTime = 0;
  TechageID = -1;
  Type = 0;
  IconID = -1;
  ButtonID = 0;
  Pointers[0] = 107000;
  Pointers[1] = 157000;
  Pointers[2] = -1;
  NameLength = 0;
  Name = "";
  NameLength2 = 0;
  Name2 = "";
}

//------------------------------------------------------------------------------
Research::~Research()
{
}

void Research::setGameVersion(GameVersion gv)
{
  ISerializable::setGameVersion(gv);
  
  RequiredTechs.resize(getRequiredTechsSize(), -1);
  
  updateGameVersion(ResourceCosts);
}

//------------------------------------------------------------------------------
uint16_t Research::getRequiredTechsSize()
{
  if (getGameVersion() >= genie::GV_AoK)
    return 6;
  else 
    return 4;
}

//------------------------------------------------------------------------------
uint16_t Research::getResourceCostsSize()
{
  return 3;
}

//------------------------------------------------------------------------------
uint16_t Research::getPointersSize()
{
  return 3;
}

//------------------------------------------------------------------------------
void Research::serializeObject(void )
{
  serialize<int16_t>(RequiredTechs, getRequiredTechsSize());
              
  serializeSub<ResearchResourceCost>(ResourceCosts, getResourceCostsSize());
  serialize<int16_t>(RequiredTechCount);
  
  if (getGameVersion() >= genie::GV_AoK)
  {
    serialize<int16_t>(Civ);
    serialize<int16_t>(FullTechMode);
  }
  
  serialize<int16_t>(ResearchLocation);
  serialize<uint16_t>(LanguageDLLName);
  serialize<uint16_t>(LanguageDLLDescription);
  serialize<int16_t>(ResearchTime);
  serialize<int16_t>(TechageID);
  serialize<int16_t>(Type);
  serialize<int16_t>(IconID);
  serialize<char>(ButtonID);
  serialize<int32_t>(Pointers, getPointersSize()); //TODO: AoE/RoR: [0..1]: LanguagePointer
  
  serializeSize<uint16_t>(NameLength, Name);
  if (NameLength > 0)
    serialize<std::string>(Name, NameLength);
  
  if (getGameVersion() >= genie::GV_SWGB)
  {
    serializeSize<uint16_t>(NameLength2, Name2); 
    if (NameLength2 > 0)
      serialize<std::string>(Name2, NameLength2);
  }
  
}

}
