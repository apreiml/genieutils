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


#include "genie/dat/unit/DeadFish.h"

namespace genie
{
  
namespace unit
{

DeadFish::DeadFish(GameVersion gv) : Unknown16(0)
{
  setGameVersion(gv);
  WalkingGraphic.first = -1;
  WalkingGraphic.second = -1;
  RotationSpeed = 0;
  Unknown11 = 0;
  TrackingUnit = -1;
  TrackingUnitUsed = 0;
  TrackingUnitDensity = 0;
  Unknown12 = 0;
}

DeadFish::~DeadFish()
{

}
void DeadFish::setGameVersion(GameVersion gv)
{
  ISerializable::setGameVersion(gv);
  
  Unknown16.resize(getUnknown16Size());
}

short DeadFish::getUnknown16Size()
{
  if (getGameVersion() >= genie::GV_AoK)
    return 17;
  else
    return 1;
}

void DeadFish::serializeObject(void )
{
  serialize<int16_t>(WalkingGraphic);
  serialize<float>(RotationSpeed);
  serialize<char>(Unknown11);
  serialize<int16_t>(TrackingUnit);
  serialize<char>(TrackingUnitUsed);
  serialize<float>(TrackingUnitDensity);
  
  if (getGameVersion() >= genie::GV_AoK)
    serialize<float>(Unknown12);
    
  serialize<char>(Unknown16, getUnknown16Size());
}

}

}

