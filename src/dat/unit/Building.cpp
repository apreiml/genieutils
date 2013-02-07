/*
    genie/dat - A library for reading and writing data files of genie
               engine games.
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


#include "genie/dat/unit/Building.h"

namespace genie
{
  
namespace unit
{

Building::Building() : Unknown37(UNKNOWN37_SIZE)
{
  ConstructionGraphicID = -1;
  SnowGraphicID = -1;
  AdjacentMode = 0;
  Unknown31 = 0;
  Unknown31b = 0;
  StackUnitID = -1;
  TerrainID = -1;
  Unknown32 = -1;
  ResearchID = -1;
  Unknown33 = 0;
  Annexes.resize(BUILDING_ANNEXES_CNT);
  HeadUnit = -1;
  TransformUnit = -1;
  Unknown34 = -1;
  ConstructionSound = -1;
  GarrisonType = 0;
  GarrisonHealRate = 0;
  Unknown35 = 0;
  Unknown36 = -1;
}

Building::~Building()
{

}
void Building::serializeObject(void )
{
  serialize<int16_t>(ConstructionGraphicID);
  
  if (getGameVersion() >= genie::GV_TC)
    serialize<int16_t>(SnowGraphicID);
  
  serialize<int16_t>(AdjacentMode);
  serialize<char>(Unknown31);
  serialize<char>(Unknown31b);
  serialize<int16_t>(StackUnitID);
  serialize<int16_t>(TerrainID);
  serialize<int16_t>(Unknown32);
  serialize<int16_t>(ResearchID);
  
  if (getGameVersion() >= genie::GV_AoK)
  {
    serialize<char>(Unknown33);
    serializeSub<unit::BuildingAnnex>(Annexes, 4);
    serialize<int16_t>(HeadUnit);
    serialize<int16_t>(TransformUnit);
    serialize<int16_t>(Unknown34);
  }
  
  serialize<int16_t>(ConstructionSound);
  
  if (getGameVersion() >= genie::GV_AoK)
  {
    serialize<char>(GarrisonType);
    serialize<float>(GarrisonHealRate);
    serialize<int32_t>(Unknown35);
    serialize<int16_t>(Unknown36);
    serialize<char>(Unknown37, UNKNOWN37_SIZE);
  }
}

}

}

