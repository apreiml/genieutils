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


#ifndef TECHAGE_H
#define TECHAGE_H
#include "genie/file/ISerializable.h"
#include "TechageEffect.h"

namespace genie
{

class Techage : public ISerializable
{

public:
  Techage();
  virtual ~Techage();
  
  virtual void serializeObject(void);
  
  static short getNameSize(void);
  
  /// Internal name, changing doesn't effect anything.
  std::string Name;
  
  std::vector<TechageEffect> Effects;
  
private:
  /// Number of effects
  unsigned short EffectCount;
};

}

#endif // TECHAGE_H
