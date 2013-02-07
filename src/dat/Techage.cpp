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


#include "genie/dat/Techage.h"

namespace genie
{
  
//------------------------------------------------------------------------------
Techage::Techage()
{
  Name = "";
}

//------------------------------------------------------------------------------
Techage::~Techage()
{
}

void Techage::setGameVersion(GameVersion gv)
{
  ISerializable::setGameVersion(gv);
  
  updateGameVersion(Effects);
}

short Techage::getNameSize(void )
{
  return 31;
}

//------------------------------------------------------------------------------
void Techage::serializeObject(void )
{
  serialize<std::string>(Name, getNameSize());
  serializeSize<uint16_t>(EffectCount, Effects.size());
  serializeSub<TechageEffect>(Effects, EffectCount);
}

}
