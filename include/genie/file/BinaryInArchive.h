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

#ifndef GENIE_BINARYINARCHIVE_H
#define GENIE_BINARYINARCHIVE_H

#include <boost/archive/detail/common_iarchive.hpp>
#include <cstddef> // std::size_t

namespace genie
{

class BinaryInArchive : public boost::archive::detail::common_iarchive<BinaryInArchive>
{
public:
  // permit serialization system privileged access to permit
  // implementation of inline templates for maximum speed.
  friend class boost::archive::load_access;
  
  BinaryInArchive(std::istream &istr)
  {
    this->istr_ = &istr;
  }
  
  template<class T>
  void load(T & t)
  {
    istr_->read(reinterpret_cast<char *>(&t), sizeof(T)); 
    //std::cout << "Read: " << t << std::endl;
  }
  
  void load_binary(void *address, std::size_t count)
  {
    istr_->read(reinterpret_cast<char *>(address), count);
  }
  
private:
  std::istream *istr_;
  
  // Ignore additional stored information
  virtual void vload(boost::archive::version_type &t) {}
  virtual void vload(boost::archive::object_id_type &t) {}
  virtual void vload(boost::archive::object_reference_type &t) {}
  virtual void vload(boost::archive::class_id_type &t) {}
  virtual void vload(boost::archive::class_id_reference_type &t) {}
  virtual void vload(boost::archive::class_id_optional_type &t) {}
  virtual void vload(boost::archive::class_name_type & t) {}
  virtual void vload(boost::archive::tracking_type &t) {}
};

// #define BOOST_SERIALIZATION_REGISTER_ARCHIVE(Archive)

}

#endif // GENIE_BINARYINARCHIVE_H
