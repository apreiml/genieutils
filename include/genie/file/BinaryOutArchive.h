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
    this->ostr_ = &ostr;
  }
  
  template<class T>
  void save(const T & t)
  {
//     std::cout << "write: " << t << std::endl;
    ostr_->write(reinterpret_cast<const char *>(&t), sizeof(T)); 
  }
 /* 
  void save(const std::string &t) 
  { 
    std::cout << "string" << t << std::endl; 
  }*/
  
  void save_binary(const void *address, std::size_t count)
  {
    ostr_->write(reinterpret_cast<const char*>(address), count);
  }
  
private:
  std::ostream *ostr_;
  
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
}

#endif // GENIE_BINARYOUTARCHIVE_H