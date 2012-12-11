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


#include "genie/dat/Sound.h"

namespace genie
{

Sound::Sound() 
{
  ID = -1;
  Unknown1 = 300000;
}

Sound::~Sound()
{

}

void Sound::setGameVersion(GameVersion gv)
{
  ISerializable::setGameVersion(gv);
  
  serial::ISerializable::updateGameVersion(gv, Items); //TODO iorw change
}

void Sound::serializeObject(void )
{
  // TODO remove if implemented
    if (isOperation(OP_READ))
  {
    BinaryInArchive bia(*getIStream());
    bia.setGameVersion(getGameVersion());
    bia >> *this;
  } 
  else if (isOperation(OP_WRITE)) 
  {
    BinaryOutArchive boa(*getOStream());
    boa.setGameVersion(getGameVersion());;
    boa << *this;
  }
  /*
  serialize<int32_t>(ID);
  serializeSize<uint16_t>(ItemCount, Items.size());
  serialize<int32_t>(Unknown1);
  
  serializeSub<SoundItem>(Items, ItemCount);
  */
}


}
