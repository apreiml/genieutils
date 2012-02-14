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


#include "genie/file/ISerializable.h"

#include <cstring>

namespace genie
{
  
//------------------------------------------------------------------------------
ISerializable::ISerializable()
{
  istr_ = 0;
  ostr_ = 0;
  gameVersion_ = GV_None;
}

//------------------------------------------------------------------------------
ISerializable::~ISerializable()
{

}

//------------------------------------------------------------------------------
void ISerializable::readObject(std::istream &istr)
{
  if (getGameVersion() == genie::GV_None)
  {
    std::cout << "Info: (Reading) Game version not set!" << std::endl;
  }

  setOperation(OP_READ);
  istr_ = &istr;
  serializeObject();

}

//------------------------------------------------------------------------------
void ISerializable::writeObject(std::ostream &ostr)
{
  if (getGameVersion() == genie::GV_None)
  {
    std::cout << "Info: (Writing) Game version not set!" << std::endl;
  }

  setOperation(OP_WRITE);
  ostr_ = &ostr;
  serializeObject();
 
}

//------------------------------------------------------------------------------
size_t ISerializable::objectSize(void) 
{
  size_ = 0;
  
  setOperation(OP_CALC_SIZE);
  serializeObject();
  
  return size_;
}

//------------------------------------------------------------------------------
void ISerializable::serializeSubObject(ISerializable * const other)
{
  istr_ = other->istr_;
  ostr_ = other->ostr_;
  operation_ = other->operation_;
  gameVersion_ = other->gameVersion_;
  serializeObject();
}
  
//------------------------------------------------------------------------------
void ISerializable::setOperation(Operation op)
{
  operation_ = op;
}

//------------------------------------------------------------------------------
ISerializable::Operation ISerializable::getOperation(void ) const
{
  return operation_;
}

//------------------------------------------------------------------------------
bool ISerializable::isOperation(Operation op) const
{
  return (op == operation_);
}

//------------------------------------------------------------------------------
void ISerializable::setIStream(std::istream &istr) 
{ 
  istr_ = &istr; 
}

//------------------------------------------------------------------------------
std::istream * ISerializable::getIStream(void) 
{ 
  return istr_; 
}

//------------------------------------------------------------------------------
void ISerializable::setOStream(std::ostream &ostr) 
{ 
  ostr_ = &ostr; 
}

//------------------------------------------------------------------------------
std::ostream * ISerializable::getOStream(void) 
{ 
  return ostr_; 
}

//------------------------------------------------------------------------------
void ISerializable::setGameVersion(GameVersion gv)
{
  gameVersion_ = gv;
}

//------------------------------------------------------------------------------
GameVersion ISerializable::getGameVersion(void )
{
  return gameVersion_;
}

//------------------------------------------------------------------------------
size_t ISerializable::strnlen(const char *str, size_t max_size)
{
  const char *ptr = 0;
  
  for (ptr = str; *ptr != '\0' && max_size-- != 0; ++ptr);
  
  return (ptr - str);
}

//------------------------------------------------------------------------------
std::streampos ISerializable::tellg(void ) const
{
  if (isOperation(OP_READ))
    return istr_->tellg();
  
  return 0;
}

//------------------------------------------------------------------------------
std::string ISerializable::readString (size_t len)
{
  if (len > 0 && !istr_->eof())
  {    
    char *buf = 0;
    serialize<char>(&buf, len);
    
    size_t tmp_len = ISerializable::strnlen(buf, len);
    
    if (tmp_len < len)
      len = tmp_len;
    
    std::string ret(buf, len);
    delete [] buf;
    
    return ret;
  }

  return "";
}

//------------------------------------------------------------------------------
void ISerializable::writeString(std::string str, size_t len)
{
  char *buf = new char[len];
  
  strncpy(buf, str.c_str(), len);
  
  for (unsigned int i=str.size(); i < len; i++)
    buf[i] = 0; // fill up with 0
  
  ostr_->write(buf, len);
  
  delete [] buf;
}



}
