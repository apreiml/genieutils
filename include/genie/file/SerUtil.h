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

#include "BinaryOutArchive.h"
#include "BinaryInArchive.h"

/// Macro for calling a SerUtil method, that sets the name parameter of a
/// method to the variables name. Warning: The archive variable must be called
/// ar when using this macro!
#define GENIE_CALL_NVP_SER(method_name, name, arg2) \
  genie::SerUtil::method_name(ar, "name", name, arg2)

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
    ar & boost::serialization::make_nvp<std::string>(name, str);
  }
  
  static void sFixString(BinaryOutArchive &ar, const char *name, std::string &str, std::size_t size)
  {
    char *cstr = new char[size]; //TODO test if buffer[highest string size] is faster
    
    strncpy(cstr, str.c_str(), size); // strncpy aligns dest with \0 until size
      
    ar & boost::serialization::make_binary_object(cstr, size);
    
    delete cstr;
    
  }
  
  static void sFixString(BinaryInArchive &ar, const char *name, std::string &str, std::size_t size)
  {
    char *cstr = new char[size];
    
    ar & boost::serialization::make_binary_object(cstr, size);
      
    str = std::string(cstr, size);
    delete cstr;
  }
  
  
};

}

#endif // GENIE_SERUTIL_H
