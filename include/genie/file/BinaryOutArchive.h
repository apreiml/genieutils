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

#ifndef GENIE_BINARYOUTARCHIVE_H
#define GENIE_BINARYOUTARCHIVE_H

#include <boost/archive/detail/common_oarchive.hpp>
#include <cstddef> // std::size_t

namespace genie
{

class BinaryOutArchive : public boost::archive::detail::common_oarchive<BinaryOutArchive>
{
public:
  // permit serialization system privileged access to permit
  // implementation of inline templates for maximum speed.
  friend class boost::archive::save_access;
  
  BinaryOutArchive(std::ostream &ostr)
  {
    this->ostr = &ostr;
  }
  
  template<class T>
  void save(T & t)
  {
    ostr->write(reinterpret_cast<const char *>(&t), sizeof(T)); 
  }
  
  void save_binary(void *address, std::size_t count){};
  
private:
  std::ostream *ostr;
  
  // Ignore additional stored information
  virtual void vsave(const boost::archive::version_type t) {}
  virtual void vsave(const boost::archive::object_id_type t) {}
  virtual void vsave(const boost::archive::object_reference_type t) {}
  virtual void vsave(const boost::archive::class_id_type t) {}
  virtual void vsave(const boost::archive::class_id_reference_type t) {}
  virtual void vsave(const boost::archive::class_id_optional_type t) {}
  virtual void vsave(const boost::archive::class_name_type & t) {}
  virtual void vsave(const boost::archive::tracking_type t) {}
};

// #define BOOST_SERIALIZATION_REGISTER_ARCHIVE(Archive)

}

#endif // GENIE_BINARYOUTARCHIVE_H