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


#include "genie/dat/GraphicDelta.h"

namespace genie
{

GraphicDelta::GraphicDelta()
{
  GraphicID = -1;
  Unknown1 = 0;
  Unknown2 = 0;
  Unknown3 = 0;
  DirectionX = 0;
  DirectionY = 0;
  Unknown4 = -1;
  Unknown5 = 0;
}

GraphicDelta::~GraphicDelta()
{

}

void GraphicDelta::serializeObject(void )
{
  serialize<int16_t>(GraphicID);
  serialize<int16_t>(Unknown1);
  serialize<int16_t>(Unknown2);
  serialize<int16_t>(Unknown3);
  serialize<int16_t>(DirectionX);
  serialize<int16_t>(DirectionY);
  serialize<int16_t>(Unknown4);
  serialize<int16_t>(Unknown5);
}

}
