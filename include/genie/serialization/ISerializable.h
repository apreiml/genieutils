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


#ifndef GENIE_SERIAL_ISERIALIZABLE_H
#define GENIE_SERIAL_ISERIALIZABLE_H

#include <iostream>
#include <vector>
#include <string.h>
#include <stdint.h>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

#include "genie/Types.h"

/// Creates a name value pair with variable name as name
#define GENIE_NVP(var) BOOST_SERIALIZATION_NVP(var)

#define GENIE_NVP2(name, var) boost::serialization::make_nvp(name, var)


namespace genie
{
  
namespace serial
{
    
//------------------------------------------------------------------------------
/// Generic base class for genie file serialization
//
class ISerializable
{

public:  
  //----------------------------------------------------------------------------
  ISerializable() : gameVersion_(GV_None) {};
  
  //----------------------------------------------------------------------------
  virtual ~ISerializable() {};
  
  //----------------------------------------------------------------------------
  virtual void setGameVersion(GameVersion gv) { gameVersion_ = gv; };
  GameVersion getGameVersion(void) const { return gameVersion_; };
  
  //----------------------------------------------------------------------------
  static void setDefaultGameVersion(GameVersion gv) { defaultGameVersion = gv; };
  static GameVersion getDefaultGameVersion(void) { return defaultGameVersion; };
  
  /// Updates the game version of all objects in vec
  //
  template <typename T>
  static void updateGameVersion(GameVersion gv, std::vector<T> &vec)
  {
    for (unsigned int i=0; i<vec.size(); i++)
    {
      ISerializable *item = dynamic_cast<ISerializable *>(&vec[i]);
      item->setGameVersion(gv);
    }
  }
  
protected:
  /// Updates the gv of all objects with the gv of this object.
  //
  template <typename T>
  void updateGameVersion(std::vector<T> &vec)
  {
    updateGameVersion<T>(getGameVersion(), vec);
  }
  
private:
  GameVersion gameVersion_;
  
  static GameVersion defaultGameVersion;
};

} // End of namespace serial
} // End of namespace genie

#endif // GENIE_SERIAL_ISERIALIZABLE_H
