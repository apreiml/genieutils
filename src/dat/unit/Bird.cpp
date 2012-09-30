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


#include "genie/dat/unit/Bird.h"

namespace genie
{
  
namespace unit
{

Bird::Bird()
{
  SheepConversion = -1;
  SearchRadius = 0;
  WorkRate = 0;
  DropSite.first = -1;
  DropSite.second = -1;
  VillagerMode = 0;
  MoveSound = -1;
  StopSound = -1;
  AnimalMode = 0;
}

Bird::~Bird()
{

}
void Bird::serializeObject(void )
{
  serialize<int16_t>(SheepConversion);
  serialize<float>(SearchRadius);
  serialize<float>(WorkRate);
  serialize<int16_t>(DropSite);
  serialize<char>(VillagerMode);
  serialize<int16_t>(MoveSound);
  serialize<int16_t>(StopSound);
  serialize<char>(AnimalMode);
  
  if (getGameVersion() <= genie::GV_RoR)
  {
    serializeSize<uint16_t>(CommandCount, Commands.size());
    serializeSub<UnitCommand>(Commands, CommandCount);
  }
}

}

}

