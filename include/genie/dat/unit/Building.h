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


#ifndef BUILDING_H
#define BUILDING_H

#include "genie/file/ISerializable.h"
#include "BuildingAnnex.h"

namespace genie
{
  
namespace unit
{

class Building : public ISerializable
{

public:
  Building();
  virtual ~Building();
  
  virtual void serializeObject(void);
  
  short ConstructionGraphicID;
  short SnowGraphicID; //not in aok/aoe/ror
  /// Enabler for annex units.
  short AdjacentMode;
  char Unknown31;
  char Unknown31b;
  short StackUnitID;
  short TerrainID;
  short Unknown32;
  short ResearchID;
  char Unknown33;
  
  static const unsigned short BUILDING_ANNEXES_CNT = 4;
  
  std::vector<unit::BuildingAnnex> Annexes; // 4
  short HeadUnit;
  short TransformUnit;
  short Unknown34;
  short ConstructionSound;
  char GarrisonType;
  float GarrisonHealRate;
  long Unknown35;
  short Unknown36;
  
  static const unsigned short UNKNOWN37_SIZE = 6;
  std::vector<char> Unknown37; // 6
  
};

}

}

#endif // BUILDING_H
