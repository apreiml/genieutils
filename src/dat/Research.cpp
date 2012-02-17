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
Research::Research() 
{
  RequiredTechCount = 0;
  Civ = -1;
  FullTechMode = 0;
  ResearchLocation = -1;
  LanguageDllName = 7000;
  LanguageDllDescription = 8000;
  ResearchTime = 0;
  TechageID = -1;
  Type = 0;
  IconID = -1;
  ButtonID = 0;
  NameLength = 0;
  Name = "";
  NameLength2 = 0;
  Name2 = "";
}

//------------------------------------------------------------------------------
Research::~Research()
{
}

//------------------------------------------------------------------------------
unsigned short Research::getRequiredTechsSize()
{
  if (getGameVersion() >= genie::GV_AoK)
    return 6;
  else 
    return 4;
}

//------------------------------------------------------------------------------
unsigned short Research::getResourceCostsSize()
{
  return 3;
}

//------------------------------------------------------------------------------
unsigned short Research::getPointersSize()
{
  return 3;
}

//------------------------------------------------------------------------------
void Research::serializeObject(void )
{
  serialize<short>(RequiredTechs, getRequiredTechsSize());
              
  serializeSub<ResearchResourceCost>(ResourceCosts, getResourceCostsSize());
  serialize<short>(RequiredTechCount);
  
  if (getGameVersion() >= genie::GV_AoK)
  {
    serialize<short>(Civ);
    serialize<short>(FullTechMode);
  }
  
  serialize<short>(ResearchLocation);
  serialize<unsigned short>(LanguageDllName);
  serialize<unsigned short>(LanguageDllDescription);
  serialize<short>(ResearchTime);
  serialize<short>(TechageID);
  serialize<short>(Type);
  serialize<short>(IconID);
  serialize<char>(ButtonID);
  serialize<long>(Pointers, getPointersSize()); //TODO: AoE/RoR: [0..1]: LanguagePointer
  
  serializeSize<unsigned short>(NameLength, Name);
  if (NameLength > 0)
    serialize<std::string>(Name, NameLength);
  
  if (getGameVersion() >= genie::GV_SWGB)
  {
    serializeSize<unsigned short>(NameLength2, Name2); 
    if (NameLength2 > 0)
      serialize<std::string>(Name2, NameLength2);
  }
  
}

}
