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


#ifndef GENIE_GRAPHICDELTA_H
#define GENIE_GRAPHICDELTA_H

#include "genie/file/ISerializable.h"

#include "genie/serialization/ISerializable.h"
#include "genie/serialization/BinaryInArchive.h"
#include "genie/serialization/BinaryOutArchive.h"

namespace genie
{

class GraphicDelta : public ISerializable
{

public:
  GraphicDelta();
  virtual ~GraphicDelta();
  
  int16_t GraphicID;
  int16_t Unknown1;
  int16_t Unknown2;
  int16_t Unknown3;
  int16_t DirectionX; //In Pixels?
  int16_t DirectionY; //In Pixels?
  int16_t Unknown4;
  int16_t Unknown5;
  
private:
  virtual void serializeObject(void);
  
  friend class boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & GENIE_NVP(GraphicID);
    ar & GENIE_NVP(Unknown1);
    ar & GENIE_NVP(Unknown2);
    ar & GENIE_NVP(Unknown3);
    ar & GENIE_NVP(DirectionX);
    ar & GENIE_NVP(DirectionY);
    ar & GENIE_NVP(Unknown4);
    ar & GENIE_NVP(Unknown5);
  }
};

}

#endif // GENIE_GRAPHICDELTA_H
