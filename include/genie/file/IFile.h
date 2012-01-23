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

#ifndef GENIE_IFILE_H
#define GENIE_IFILE_H

#include "ISerializable.h"

#include <boost/utility.hpp>

namespace genie
{

//------------------------------------------------------------------------------
/// Interface providing file loading and saving for ISerializable objects.
//
class IFile : public ISerializable, boost::noncopyable
{
public: 
  
  //----------------------------------------------------------------------------
  IFile();
  
  //----------------------------------------------------------------------------
  virtual ~IFile();
  
  //----------------------------------------------------------------------------
  /// Sets name of file to work with.
  ///
  /// @param filename.
  //
  void setFilename(const char *filename);
  
  //----------------------------------------------------------------------------
  /// Get name of file worked on.
  ///
  /// @return filename.
  //
  const char *getFilename(void) const;
  
  //----------------------------------------------------------------------------
  /// Loads the object from file. Can only be called if filename is already set.
  ///
  /// @exception std::ios_base::failure thrown if file can't be read (file 
  ///                                   doesn't exist, insufficient rights...)
  /// 
  //
  void load(void ) throw (std::ios_base::failure);
  
  //----------------------------------------------------------------------------
  /// Loads the object from file.
  ///
  /// @param filename file name
  /// @exception std::ios_base::failure thrown if file can't be read (file 
  ///                                   doesn't exist, insufficient rights...)
  //
  virtual void load(const char *filename) throw (std::ios_base::failure);
  
  //----------------------------------------------------------------------------
  /// Saves data to file. Can only be called if filename is set through set 
  /// method or the file was loaded using the load method.
  ///
  /// @exception std::ios_base::failure thrown if file can't be written (
  ///                                   insufficient rights...)
  //
  void save(void ) throw (std::ios_base::failure);
  
  //----------------------------------------------------------------------------
  /// Saves data to a different file.
  ///
  /// @param filename file name
  /// @exception std::ios_base::failure thrown if file can't be written (
  ///                                   insufficient rights...)
  //
  virtual void saveAs(const char *filename) throw (std::ios_base::failure);
  
  
private:
  std::string filename_;
};

}

#endif // GENIE_IFILE_H