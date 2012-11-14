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

#include <boost/serialization/binary_object.hpp>
#include <string.h>

namespace genie
{
  
/// Serialization utils
class SerUtil 
{
public:
  
  /// Serialize a string with fixed size.
  template<class Archive>
  static void sFixString(Archive &ar, const char *name, std::string &str, std::size_t size)
  {
    // TODO dyn cast: check if BinaryOutArchive, else write string
    
    char *cstr = new char[size];
    boost::serialization::binary_object bo(cstr, size);
    
    if (typename Archive::is_saving())
      strncpy(cstr, str.c_str(), size);
      
    ar & bo;
      
    if (typename Archive::is_loading())
      str = std::string(cstr);
  }
};

}

#endif // GENIE_SERUTIL_H
