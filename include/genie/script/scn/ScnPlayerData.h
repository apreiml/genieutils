/*
    genieutils - <description>
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

#ifndef GENIE_SCN_PLAYER_DATA_H
#define GENIE_SCN_PLAYER_DATA_H

#include "genie/file/ISerializable.h"

#include <stdint.h>

namespace genie
{
  
class ScnPlayerData1 : public ISerializable
{
public:
  ScnPlayerData1();
  virtual ~ScnPlayerData1();
  
  /// boolean
  uint32_t active; 
  
  /// boolean
  uint32_t human;
  
  uint32_t civilizationId;
  
  /// constant = 4 ??
  uint32_t unknown1;
  
private:
  virtual void serializeObject(void);
};
  
class ScnPlayerData2 : public ISerializable
{
public:
  ScnPlayerData2();
  virtual ~ScnPlayerData2();
  
  
  
private:
  virtual void serializeObject(void);
  
};
  
}

#endif // GENIE_SCN_PLAYER_DATA_H