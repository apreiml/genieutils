/*
    genieutils - <description>
    Copyright (C) 2011  Armin Preiml <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef GENIE_ISERIALIZABLE_H
#define GENIE_ISERIALIZABLE_H

#include <iostream>

#include "genie/Types.h"
#include <vector>
#include <string.h>
#include <stdint.h>

namespace genie
{
  
//------------------------------------------------------------------------------
/// Generic base class for genie file serialization
//
class ISerializable
{

public:  
  //----------------------------------------------------------------------------
  ISerializable();
  
  //----------------------------------------------------------------------------
  virtual ~ISerializable();
  
  //----------------------------------------------------------------------------
  /// Set position to start reading the object from stream
  //
  void setInitialReadPosition(std::streampos pos);
  
  //----------------------------------------------------------------------------
  std::streampos getInitialReadPosition(void) const;
  
  //----------------------------------------------------------------------------
  /// Read object from istream.
  ///
  /// @param istr Input stream to read from
  //
  void readObject(std::istream &istr);
  
  //----------------------------------------------------------------------------
  /// Write object to stream.
  ///
  /// @param ostr Output stream to write to
  //
  void writeObject(std::ostream &ostr);
  
  //----------------------------------------------------------------------------
  /// Returns size in bytes.
  //
  virtual size_t objectSize(void);
  
  //----------------------------------------------------------------------------
  /// Serialize this object as a subobject of another one.
  ///
  /// @param root The object to serialize from.
  //
  void serializeSubObject(ISerializable *const root);
  
  //----------------------------------------------------------------------------
  /// 
  //
  virtual void setGameVersion(GameVersion gv);
  
  //----------------------------------------------------------------------------
  GameVersion getGameVersion(void) const;
  
  static void setDefaultGameVersion(GameVersion gv);
  static GameVersion getDefaultGameVersion(void);
  
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
  
  //----------------------------------------------------------------------------
  /// Needs access to get and set stream methods for (de)compressing.
  //
  friend class Compressor;
  
protected:
  
  enum Operation
  {
    OP_READ = 0,
    OP_WRITE = 1,
    OP_CALC_SIZE = 2
  };
  
  /// Updates the gv of all objects with the gv of this object.
  //
  template <typename T>
  void updateGameVersion(std::vector<T> &vec)
  {
    updateGameVersion<T>(getGameVersion(), vec);
  }
  
  //----------------------------------------------------------------------------
  /// Set operation to process
  ///
  /// @param op operation
  //
  void setOperation(Operation op);
  
  //----------------------------------------------------------------------------
  /// Get current operation
  ///
  /// @return operation
  //
  Operation getOperation(void ) const;
  
  //----------------------------------------------------------------------------
  /// Check if given operation is active.
  ///
  /// @param op operation to check
  //
  bool isOperation(Operation op) const;
  
  //----------------------------------------------------------------------------
  void setIStream(std::istream &istr);
  
  //----------------------------------------------------------------------------
  std::istream * getIStream(void);
  
  //----------------------------------------------------------------------------
  void setOStream(std::ostream &ostr);
  
  //----------------------------------------------------------------------------
  std::ostream * getOStream(void);
  
  //----------------------------------------------------------------------------
  /// @return position of the istreams get pointer.
  //
  std::streampos tellg(void ) const;
  
  //----------------------------------------------------------------------------
  /// Custom strnlen for mingw32.
  ///
  /// @param str char array to get length from.
  /// @param max_size max array length
  /// @return string length
  //
  static size_t strnlen(const char *str, size_t max_size);
  
  //----------------------------------------------------------------------------
  /// Derived classes need to implement this method. It will automatically be
  /// called on reading or writing an Object.
  //
  virtual void serializeObject(void) = 0;
  
  //----------------------------------------------------------------------------
  /// Reads a string from istr. Returns empty string if len parameter is 0.
  /// The string will be cut at the first \0.
  ///
  /// @param len Number of characters to read.
  //
  std::string readString(size_t len);
  
  //----------------------------------------------------------------------------
  /// Writes a string to ostr.
  ///
  /// @param str string to write
  /// @param len number of chars to write.
  //
  void writeString(std::string str, size_t len);
  
  //----------------------------------------------------------------------------
  /// Generic read method for basic data types.
  ///
  /// @return read data
  //
  template <typename T>
  T read()
  {
    T ret;

    if (!istr_->eof())
      istr_->read(reinterpret_cast<char *>(&ret), sizeof(ret));
    
    return ret;
  }
  
  //----------------------------------------------------------------------------
  /// Generic write method for basic data types.
  ///
  /// @param data to write.
  //
  template <typename T>
  void write(T &data)
  {
    ostr_->write(reinterpret_cast<char *>(&data), sizeof(T)); 
  }

  //----------------------------------------------------------------------------
  /// Generic read method for arrays. It allocates new space if pointer is 0.
  //
  template <typename T>
  void read(T **array, size_t len)
  {   
    if (!istr_->eof())
    {
      if (*array == 0)
        *array = new T[len];
      
      istr_->read(reinterpret_cast<char *>(*array), sizeof(T) * len);
    }
  }
  
  //----------------------------------------------------------------------------
  /// Writes an array to file.
  //
  template <typename T>
  void write(T *data, size_t len)
  {
    ostr_->write(reinterpret_cast<char *>(data), sizeof(T) * len);
  }
  
  //----------------------------------------------------------------------------
  /// Serializes a string with preceeding size. Template argument is the data
  /// type of the size.
  ///
  /// @param str string to serialize
  /// @param cString if enabled, string ends with a \0 (default)
  //
  template <typename T>
  void serializeSizedString(std::string &str, bool cString = true)
  {
    T size;
    
    serializeSize<T>(size, str, cString);
    serialize<std::string>(str, size);
  }
  
  template <typename T>
  void serializeSizedStrings(std::vector<std::string> &vec, size_t size, 
                             bool cString = true)
  {
    if (isOperation(OP_READ))
    {
      vec.resize(size);
    }
    
    for (size_t i=0; i<size; i++)
      serializeSizedString<T>(vec[i], cString);
    
  }
  
  //----------------------------------------------------------------------------
  /// Serialize method for basic data types. 
  /// Reads or writes data dependent on set operation.
  //
  template <typename T>
  void serialize(T &data)
  {
    switch(getOperation())
    {
      case OP_WRITE:
        write<T>(data);
        break;
      case OP_READ:
        data = read<T>();
        break;
      case OP_CALC_SIZE:
        size_ += sizeof(T);
        break;
    }
  }
  
  template <typename T>
  void serialize(ISerializable &data)
  {
    data.serializeSubObject(this);
    
    if (isOperation(OP_CALC_SIZE))
      size_ += data.objectSize();
  }
  
  //----------------------------------------------------------------------------
  /// Reads or writes an array of data dependent on Write_ flag.
  //
  template <typename T>
  void serialize(T **data, size_t len)
  {
    switch(getOperation())
    {
      case OP_WRITE:
        write<T>(*data, len);
        break;
      case OP_READ:
        read<T>(data, len);
        break;
      case OP_CALC_SIZE:
        size_ += sizeof(T) * len;
        break;
    }
  }
  
  //----------------------------------------------------------------------------
  /// Spezialization of std::strings.
  //
  template <typename T>
  void serialize(std::string &str, size_t len)
  {
    if (len > 0)
    {
      switch(getOperation())
      {
        case OP_WRITE:
          writeString(str, len);
          break;
        case OP_READ:
          str = readString(len);
          break;
        case OP_CALC_SIZE:
          size_ += sizeof(char) * len;
          break;
      }
    }
  }
  
  //----------------------------------------------------------------------------
  /// Reads or writes an array of data to/from a vector dependent on opeartion.
  //
  template <typename T>
  void serialize(std::vector<T> &vec, size_t size)
  {
    switch(getOperation())
    {
      case OP_WRITE:
        if (vec.size() != size)
          std::cerr << "Warning!: vector size differs len!" << vec.size() << " " << size <<  std::endl;
        
        for (typename std::vector<T>::iterator it = vec.begin(); it != vec.end(); 
            it ++)
          write<T>(*it);
        
        break;
        
      case OP_READ:
        vec.resize(size);
        
        for (size_t i=0; i < size; i++)
          vec[i] = read<T>();
        
        break;
     
      case OP_CALC_SIZE:
        size_ += size * sizeof(T);
        break;
    }
  }

  //----------------------------------------------------------------------------
  /// Serializes a collection of objects that inherit from ISerializable.
  //
  template <typename T>
  void serializeSub(std::vector<T> &vec, size_t size)
  {
    if (isOperation(OP_WRITE) || isOperation(OP_CALC_SIZE))
    {
      if (vec.size() != size)
        std::cerr << "Warning!: vector size differs size!" << vec.size() << " " << size <<  std::endl;
      
      for (typename std::vector<T>::iterator it = vec.begin(); it != vec.end();
           it ++)
      {
        ISerializable *data = dynamic_cast<ISerializable *>(&(*it));
       
        data->serializeSubObject(this);
        
        if (isOperation(OP_CALC_SIZE))
          size_ += data->objectSize();
      }
    }
    else
    {      
      vec.resize(size);
      
      for (size_t i=0; i < size; i++)
      {
        ISerializable *cast_obj = dynamic_cast<ISerializable *>(&vec[i]);
        cast_obj->serializeSubObject(this);
      }
    }
  }
  
  //----------------------------------------------------------------------------
  /// Serialize a vector size number. If size differs, the number will be
  /// updated.
  //
  template <typename T>
  void serializeSize(T &data, size_t size)
  {
    if (isOperation(OP_WRITE))
      data = size;
    
    serialize<T>(data);
  }
  
  //----------------------------------------------------------------------------
  /// Spezialization of serializeSize for strings.
  ///
  /// @param data size to serialize
  /// @param str string to get size from
  /// @param c_str true if cstring (ending with \0).
  /// 
  template <typename T>
  void serializeSize(T &data, std::string str, bool cString=true)
  {
    // calculate new size
    if (isOperation(OP_WRITE))
    {
      size_t size = str.size();
      
      if (cString && size != 0)
        size++;   //counting \0
        
      data = size;
    }
    
    serialize<T>(data);
  }
  
  //----------------------------------------------------------------------------
  /// Necessary for graphic objects. The pointer array contains entries with
  /// value 0. If a pointer is 0, a empty graphic object will be inserted into
  /// the vector.
  //
  template <typename T>
  void serializeSubWithPointers(std::vector<T> &vec, size_t size, 
                                std::vector<int32_t> &pointers)
  {
    if (isOperation(OP_WRITE) || isOperation(OP_CALC_SIZE))
    {
      for (size_t i=0; i < size; i++)
      {
        if (pointers[i] != 0)
        {
          ISerializable *data = dynamic_cast<ISerializable *>(&vec[i]);
          
          data->serializeSubObject(this);
          
          if (isOperation(OP_CALC_SIZE))
            size_ += data->objectSize();
        }
      }
    }
    else
    {
      vec.resize(size);
      
      for (size_t i=0; i < size; i++)
      {        
        T *obj = &vec[i]; 
        
        if (pointers[i] != 0)
        {
          ISerializable *cast_obj = dynamic_cast<ISerializable *>(obj);
          cast_obj->serializeSubObject(this);
        }
      }
    }
  }
  
  //----------------------------------------------------------------------------
  /// Spezialization of serialize for std::pair. 
  ///
  /// @param p pair
  /// @param only_first if true only the first element will be serialized
  //
  template <typename T>
  void serialize(std::pair<T, T> &p, bool only_first=false)
  {
    switch(getOperation())
    {
      case OP_WRITE:
        write<T>(p.first);
      
        if (!only_first)
          write<T>(p.second);
        break;
        
      case OP_READ:
        p.first = read<T>();
      
        if (!only_first)
          p.second = read<T>();
        break;
        
      case OP_CALC_SIZE:
        size_ += sizeof(T);
        
        if (!only_first)
          size_ += sizeof(T);
        break;
    }
  }
  
private:
  std::istream *istr_;
  std::ostream *ostr_;
  
  std::streampos init_read_pos_;
  
  Operation operation_;
  
  GameVersion gameVersion_;
  
  static GameVersion defaultGameVersion;
  
  size_t size_;
};

//----------------------------------------------------------------------------
/// Copies data from src to dest, but also allocates memory for dest or
/// sets dest to 0 if src is 0.
//
template <typename T>
void arraycpy(T **dest, const T *src, size_t size)
{
  if (src == 0)
    *dest = 0;
  else
  {
    *dest = new T[size];
    memcpy(*dest, src, size * sizeof(T));
  }
}
  
}

#endif // GENIE_ISERIALIZABLE_H
