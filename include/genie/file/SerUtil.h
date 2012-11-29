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

#ifndef GENIE_SERUTIL_H
#define GENIE_SERUTIL_H

#include <iostream>
#include <string>
#include <string.h>

#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>

#include "ISerializable.h"
#include "BinaryOutArchive.h"
#include "BinaryInArchive.h"

/// Macro for calling a SerUtil method, that sets the name parameter of a
/// method to the variables name. Warning: The archive variable must be called
/// ar when using this macro!
#define GENIE_CALL_NVP_SER(method_name, var) \
  genie::SerUtil::method_name(ar, #var, var)
  
#define GENIE_CALL_NVP_SER2(method_name, var, arg) \
  genie::SerUtil::method_name(ar, #var, var, arg)

namespace genie
{

/// Serialization utils
class SerUtil 
{
public:
  
  /// Updates size on write and resizes vector on read
  //
  template<class Archive, class T, class S>
  static void sSize(Archive &ar, const char *name, S &size, std::vector<T> &vec)
  {
    std::cout << "TODO: sSize \n";
  }
  
  template<class T, class S>
  static void sSize(BinaryInArchive &ar, const char *name, S &size, std::vector<T> &vec) 
  {
    ar >> size;
    vec.resize(size);
  }
  
  template<class T, class S>
  static void sSize(BinaryOutArchive &ar, const char *name, S &size, std::vector<T> &vec)
  {
    size = vec.size();
    ar << size;
  }
  
  
  /// Serialize a std::vector
  //
  template<class Archive, class T>
  static void sVec(Archive &ar, const char *name, std::vector<T> &vec)
  {
    ar & boost::serialization::make_nvp(name, vec);
  }
  
  template<class T>
  static void sVec(BinaryInArchive &ar, const char *name, std::vector<T> &vec)
  {
    class std::vector<T>::iterator it = vec.begin();
    ISerializable *ser = 0;
    
    // vector should already have proper size (updateSize)
    for (; it != vec.end(); it++) 
    {
      if ( (ser = dynamic_cast<ISerializable*>(&(*it))) )
        ser->setGameVersion(ar.getGameVersion());
      
      ar >> (*it);
    }
  }
    
  template<class T>
  static void sVec(BinaryOutArchive &ar, const char *name, std::vector<T> &vec)
  {
    class std::vector<T>::iterator it = vec.begin();
    
    for (; it != vec.end(); it++) 
      ar << (*it);
  }
  
  
};

}

#endif // GENIE_SERUTIL_H
