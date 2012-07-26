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


#ifndef GENIE_GRAPHICATTACKSOUND_H
#define GENIE_GRAPHICATTACKSOUND_H
#include "genie/file/ISerializable.h"

namespace genie
{

class GraphicAttackSound : public ISerializable
{

public:
  GraphicAttackSound();
  virtual ~GraphicAttackSound();
  
  //TODO: Vector
  int16_t SoundDelay;
  int16_t SoundID;
  int16_t SoundDelay2;
  int16_t SoundID2;
  int16_t SoundDelay3;
  int16_t SoundID3;

private:
  virtual void serializeObject(void);
};

}

#endif // GENIE_GRAPHICATTACKSOUND_H
