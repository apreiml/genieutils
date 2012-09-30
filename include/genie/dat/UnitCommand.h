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


#ifndef GENIE_UNITCOMMAND_H
#define GENIE_UNITCOMMAND_H
#include "genie/file/ISerializable.h"

namespace genie
{

class UnitCommand : public ISerializable
{

public:
  UnitCommand();
  virtual ~UnitCommand();
  
  int16_t One;
  int16_t ID;
  char Unknown1;
  int16_t Type;
  int16_t ClassID;
  int16_t UnitID;
  int16_t Unknown2;
  int16_t ResourceIn;
  int16_t SubType;
  int16_t ResourceOut;
  int16_t Unknown3;
  float WorkRateMultiplier;
  float ExecutionRadius;
  float ExtraRange;
  char Unknown4;
  float Unknown5;
  char Unknown6;
  char Unknown7;
  int32_t Unknown8;
  char Unknown9;
  char Unknown10;
  char Unknown11;
  
  static short getGraphicsSize(void);
  std::vector<int16_t> Graphics;
  
private:
  virtual void serializeObject(void);
};

}

#endif // GENIE_UNITCOMMAND_H
