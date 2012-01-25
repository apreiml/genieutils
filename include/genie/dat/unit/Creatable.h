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


#ifndef GENIE_CREATABLE_H
#define GENIE_CREATABLE_H

#include "genie/file/ISerializable.h"
#include "../ResourceUsage.h"

namespace genie
{
  
namespace unit
{

class Creatable : public ISerializable
{

public:
  Creatable();
  virtual ~Creatable();
  
  virtual void serializeObject(void);
  
  static short getResourceCostsSize();
  
  typedef ResourceUsage<short, short, short> ResourceCost;
  
  std::vector<ResourceCost> ResourceCosts; //3
  short TrainTime;
  short TrainLocationID;
  char ButtonID;
  char Unknown26;//not in aoe/ror
  
  static const short UNKNOWN27_SIZE = 3;
  std::vector<short> Unknown27; //3 //not in aoe/ror
  char Unknown28;//not in aoe/ror
  char MissileGraphicDelay;//not in aoe/ror
  char HeroMode;//not in aoe/ror
  std::pair<short, short> GarrisonGraphic; //not in aoe/ror
  float AttackMissileDuplicationAmount1;//not in aoe/ror
  char AttackMissileDuplicationAmount2;//not in aoe/ror
  
  static const short AMDBUNKNOWN_SIZE = 3;
  /// The area from which projectiles spawn. Size and randomness.
  std::vector<float> AttackMissileDuplicationSpawning; //3 //not in aoe/ror
  
  long AttackMissileDuplicationUnit;//not in aoe/ror
  long AttackMissileDuplicationGraphic;//not in aoe/ror
  
  //TODO: 
  /*
   * 1.Determines adjacent unit graphics
    2.Enter 0 or 1
    3.If “1”, the building will have the capability to change graphics depending 
    on the buildings adjacent to it. For instance, a single wall will be a
    wall end piece, but if a wall is placed between two other walls, it will 
    have a different graphic.
   */
  char Unknown29;//not in aoe/ror
  short DisplayedPierceArmour;
  
};

}

}

#endif // GENIE_CREATABLE_H
