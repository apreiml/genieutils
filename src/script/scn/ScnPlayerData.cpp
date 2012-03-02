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

#include "genie/script/scn/ScnPlayerData.h"

namespace genie
{
  
ScnPlayerData1::ScnPlayerData1()
{
}

ScnPlayerData1::~ScnPlayerData1()
{
}

void ScnPlayerData1::serializeObject(void)
{
  serialize<uint32_t>(active);
  serialize<uint32_t>(human);
  serialize<uint32_t>(civilizationId);
  serialize<uint32_t>(unknown1);
}

  
ScnPlayerData2::ScnPlayerData2()
{
}

ScnPlayerData2::~ScnPlayerData2()
{
}

void ScnPlayerData2::serializeObject(void)
{
}
  
}