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

#ifndef GENIE_SERIAL_STRING_H
#define GENIE_SERIAL_STRING_H

#include <string>
#include <cstring>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/binary_object.hpp>

#include "BinaryOutArchive.h"
#include "BinaryInArchive.h"

namespace genie
{
namespace serial
{
 
/// Fixed length string serialization
class FixedString
{
public:
  FixedString(std::string &str, std::size_t size) : str_(str), size_(size) {};
  
  std::size_t size(void) const { return size_; };
  void size(std::size_t size) { size_ = size; };
  
  std::string &str(void) const { return str_; };
private:
  std::string &str_;
  std::size_t size_;
  
  friend class boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & boost::serialization::make_nvp("Value", str_);
  }
  
  void serialize(BinaryOutArchive &ar, const unsigned int version)
  {
    char *cstr = new char[size_]; //TODO test if buffer[highest string size] is faster
    strncpy(cstr, str_.c_str(), size_); // strncpy aligns dest with \0 until size
    ar & boost::serialization::make_binary_object(cstr, size_);
    delete cstr;
  }
  
  void serialize(BinaryInArchive &ar, const unsigned int version)
  {
    char *cstr = new char[size_];
    ar & boost::serialization::make_binary_object(cstr, size_);
    str_ = std::string(cstr);
    delete cstr;
  }
  
};

template<class SizeType>
class String
{
public:
  String(std::string &str) : str_(str) { size_ = str.size(); };
  
  template<class Archive>
  void serialSize(Archive &ar) {}
  
  void serialSize(BinaryInArchive &ar, bool cString=true)
  {
    ar & size_;
  }
  
  void serialSize(BinaryOutArchive &ar, bool cString=true)
  {
    size_ = str_.size();
    
    if (cString && size_ != 0)
      size_++;   //counting \0
    ar & size_;
  }
  
private:
  std::string &str_;
  SizeType size_;
  
  friend class boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & boost::serialization::make_nvp("String", str_);
  }
  
  void serialize(BinaryOutArchive &ar, const unsigned int version)
  {
    char *cstr = new char[size_]; //TODO test if buffer[highest string size] is faster
    strncpy(cstr, str_.c_str(), size_); // strncpy aligns dest with \0 until size
    ar & boost::serialization::make_binary_object(cstr, size_);
    delete cstr;
  }
  
  void serialize(BinaryInArchive &ar, const unsigned int version)
  {
    char *cstr = new char[size_];
    ar & boost::serialization::make_binary_object(cstr, size_);
    str_ = std::string(cstr);
    delete cstr;
  }
  
};

} // End of namespace serial
} // End of namespace genie

//BOOST_CLASS_IMPLEMENTATION(genie::serial::FixedString, boost::serialization::object_serializable)

#endif // GENIE_SERIAL_STRING_H
