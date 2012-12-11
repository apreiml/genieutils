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


#ifndef GENIE_SOUND_H
#define GENIE_SOUND_H

#include <vector>

#include "genie/file/ISerializable.h"
#include "genie/serialization/Vector.h"

#include "SoundItem.h"


namespace genie
{

class Sound : public ISerializable
{

public:
  Sound();
  virtual ~Sound();
  virtual void setGameVersion(GameVersion gv);
  
  int32_t ID;
  int32_t Unknown1;      // This is always equal to 300000
  std::vector<SoundItem> Items;

private:
  
  virtual void serializeObject(void);
  
  friend class boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    serial::ObjVector<SoundItem, uint16_t> sItems(Items, getGameVersion());
    
    ar & GENIE_NVP(ID);
    sItems.serialSize(ar);
    ar & GENIE_NVP(Unknown1);
    
    ar & GENIE_NVP2("Items", sItems);
  }
  
};

}

#endif // GENIE_SOUND_H
