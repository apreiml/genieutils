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

#ifndef GENIE_SERIAL_VECTOR_H
#define GENIE_SERIAL_VECTOR_H

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/vector.hpp>

#include "genie/serialization/ISerializable.h"
#include "BinaryOutArchive.h"
#include "BinaryInArchive.h"

namespace genie
{
namespace serial
{

/// class for serializing Vectors containing Objects of ISerializable
template<class ItemType, class SizeType>
class ObjVector
{
public:
  ObjVector(std::vector<ItemType> &vec) : vec_(vec) { size_ = 0; gameVersion_ = GV_None; };
  ObjVector(std::vector<ItemType> &vec, GameVersion gv) : vec_(vec), gameVersion_(gv) { size_ = 0; };
  
  template<class Archive>
  void serialSize(Archive &ar) {}
  
  void serialSize(BinaryInArchive &ar)
  {
    ar & size_;
    vec_.resize(size_);
  }
  
  void serialSize(BinaryOutArchive &ar)
  {
    size_ = vec_.size();
    ar & size_;
  }
  
private: 
  std::vector<ItemType> &vec_;
  SizeType size_;
  GameVersion gameVersion_;
  
  friend class boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    class std::vector<ItemType>::iterator it = vec_.begin();
    ISerializable *ser = 0;
    
    // vector should already have proper size (serialSize)
    for (; it != vec_.end(); it++) 
    {
      if (gameVersion_ != GV_None && Archive::is_loading::value && (ser = dynamic_cast<ISerializable*>(&(*it))) )
        ser->setGameVersion(gameVersion_); 
      
      ar & boost::serialization::make_nvp("Item", (*it));
    }
  }
  
  void serialize(BinaryInArchive &ar, const unsigned int version)
  {
    class std::vector<ItemType>::iterator it = vec_.begin();
    ISerializable *ser = 0;
    
    // vector should already have proper size (updateSize)
    for (; it != vec_.end(); it++) 
    {
      if (gameVersion_ != GV_None && (ser = dynamic_cast<ISerializable*>(&(*it))) )
        ser->setGameVersion(gameVersion_);
      
      ar & (*it);
    }
  }
  
  void serialize(BinaryOutArchive &ar, const unsigned int version)
  {
    class std::vector<ItemType>::iterator it = vec_.begin();
    
    for (; it != vec_.end(); it++) 
      ar & (*it);
  }
  
};

} // End of namespace serial
} // End of namespace genie

//BOOST_CLASS_IMPLEMENTATION(genie::serial::Vector, boost::serialization::object_serializable)

#endif // GENIE_SERIAL_VECTOR_H
