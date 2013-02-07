/*
    geniedat - A library for reading and writing data files of genie
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


#ifndef GENIE_PROJECTILE_H
#define GENIE_PROJECTILE_H

#include "genie/file/ISerializable.h"
#include "AttackOrArmor.h"

namespace genie
{
  
namespace unit
{

class Projectile : public ISerializable
{

public:
  Projectile();
  virtual ~Projectile();
  
  char Unknown20; //2 //aoe/ror 1, aok 1, tc 2
  char Unknown20_1;
  uint16_t AttackCount;
  std::vector<unit::AttackOrArmor> Attacks;
  uint16_t ArmourCount;
  std::vector<unit::AttackOrArmor> Armours;
  int16_t Unknown21;
  float MaxRange;
  float BlastRadius;
  float ReloadTime1;
  int16_t ProjectileUnitID;
  
  /// Percentage value determining the probability of an attack hiting
  int16_t AccuracyPercent;
  
  /// Used in AoE/RoR for towers.
  char TowerMode;
  int16_t Delay;
  
  static short getGraphicDisplacementSize();
  std::vector<float> GraphicDisplacement; //3
  
  char Unknown23;
  float MinRange;
  float GarrisonRecoveryRate;
  int16_t AttackGraphic;
  int16_t DisplayedMeleeArmour;
  int16_t DisplayedAttack;
  float DisplayedRange;
  float ReloadTime2;
  
private: 
  virtual void serializeObject(void);
  
};

}

}

#endif // GENIE_PROJECTILE_H
