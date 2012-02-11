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


#ifndef GENIE_BIRD_H
#define GENIE_BIRD_H

#include "genie/file/ISerializable.h"
#include "../UnitCommand.h"

namespace genie
{
  
namespace unit
{

class Bird : public ISerializable
{

public:
  Bird();
  virtual ~Bird();
  
  short SheepConversion;//FFFF = No, 0000 = Yes
  float SearchRadius;
  float WorkRate;
  std::pair<short, short> DropSite;
  
  /// If activated unit switches villager types
  char VillagerMode;
  short MoveSound;
  short StopSound;
  /// Some animals have this.
  char AnimalMode;
  unsigned short CommandCount;//only in aoe/ror
  std::vector<UnitCommand> Commands;//only in aoe/ror
  
private:
  virtual void serializeObject(void);
};

}

}

#endif // GENIE_BIRD_H
