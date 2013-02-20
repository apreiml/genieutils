/*
    geniedat - A library for reading and writing data files of genie
               engine games.
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


#ifndef GENIE_UNKNOWN_H
#define GENIE_UNKNOWN_H
#include "genie/file/ISerializable.h"

namespace genie
{

class ThirdSubData : public ISerializable
{
public:
  ThirdSubData();
  virtual ~ThirdSubData();

  static const short UNKNOWN1_LEN = 11;
  std::vector<int32_t> Unknown1;

private:
  virtual void serializeObject(void);
};

class SecondSubData : public ISerializable
{
public:
  SecondSubData();
  virtual ~SecondSubData();

  static const short UNKNOWN1_LEN = 6;
  std::vector<int32_t> Unknown1;

private:
  virtual void serializeObject(void);
};

class FirstSubData : public ISerializable
{
public:
  FirstSubData();
  virtual ~FirstSubData();

  static const short UNKNOWN1_LEN = 11;
  std::vector<int32_t> Unknown1;

private:
  virtual void serializeObject(void);
};

class Unknown2ndBlock : public ISerializable
{
public:
  Unknown2ndBlock();
  virtual ~Unknown2ndBlock();

  static const short UNKNOWN1_LEN = 9;
  std::vector<int32_t> Unknown1;

  int32_t Pointer1;
  std::vector<FirstSubData> FirstSubDatas;
  int32_t Pointer2;
  std::vector<SecondSubData> SecondSubDatas;
  int32_t Pointer3;
  std::vector<ThirdSubData> ThirdSubDatas;

  static const short UNKNOWN2_LEN = 2;
  std::vector<int32_t> Unknown2;

private:
  uint32_t Count1;
  uint32_t Count2;
  uint32_t Count3;

  virtual void serializeObject(void);
};

class Unknown1stBlock : public ISerializable
{
public:
  Unknown1stBlock();
  virtual ~Unknown1stBlock();

  int32_t UnknownLevel;
  static const short UNKNOWN1_LEN = 9;
  std::vector<int32_t> Unknown1;

  int32_t Pointer1;
  int32_t Pointer2;
  int32_t Pointer3;

  static const short UNKNOWN2_LEN = 2;
  std::vector<int32_t> Unknown2;

  uint32_t Count1;
  uint32_t Count2;
  uint32_t Count3;

private:
  virtual void serializeObject(void);
};

class Unknown : public ISerializable
{
public:
  Unknown();
  virtual ~Unknown();

  int32_t Pointer;

  std::vector<Unknown1stBlock> Unknown1stBlocks;
  std::vector<Unknown2ndBlock> Unknown2ndBlocks;

private:
  uint32_t total_unknown_count_;

  virtual void serializeObject(void);
};

}

#endif // GENIE_UNKNOWN_H
