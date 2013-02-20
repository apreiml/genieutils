/*
    genie/dat - A library for reading and writing data files of genie
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


#include "genie/dat/Unknown.h"

namespace genie
{

//------------------------------------------------------------------------------
Unknown::Unknown()
{
  Pointer = 0;
}

//------------------------------------------------------------------------------
Unknown::~Unknown()
{
}

//------------------------------------------------------------------------------
void Unknown::serializeObject()
{
  serializeSize<uint32_t>(total_unknown_count_, Unknown2ndBlocks.size());

  serialize<int32_t>(Pointer);

  serializeSub<Unknown1stBlock>(Unknown1stBlocks, total_unknown_count_);
  serializeSub<Unknown2ndBlock>(Unknown2ndBlocks, total_unknown_count_);
}

//------------------------------------------------------------------------------
Unknown1stBlock::Unknown1stBlock() : Unknown1(UNKNOWN1_LEN), Unknown2(UNKNOWN2_LEN)
{
  UnknownLevel = 0;
  Pointer1 = 0;
  Pointer2 = 0;
  Pointer3 = 0;
  // Remove these after you have made them automatic.
  Count1 = 0;
  Count2 = 0;
  Count3 = 0;
}

//------------------------------------------------------------------------------
Unknown1stBlock::~Unknown1stBlock()
{
}

//------------------------------------------------------------------------------
void Unknown1stBlock::serializeObject(void)
{
  serialize<int32_t>(UnknownLevel);
  serialize<int32_t>(Unknown1, UNKNOWN1_LEN);
  serialize<uint32_t>(Count1);
  serialize<int32_t>(Pointer1);
  serialize<uint32_t>(Count2);
  serialize<int32_t>(Pointer2);
  serialize<uint32_t>(Count3);
  serialize<int32_t>(Pointer3);
  serialize<int32_t>(Unknown2, UNKNOWN2_LEN);
}

//------------------------------------------------------------------------------
Unknown2ndBlock::Unknown2ndBlock() : Unknown1(UNKNOWN1_LEN), Unknown2(UNKNOWN2_LEN)
{
  Pointer1 = 0;
  Pointer2 = 0;
  Pointer3 = 0;
}

//------------------------------------------------------------------------------
Unknown2ndBlock::~Unknown2ndBlock()
{
}

//------------------------------------------------------------------------------
void Unknown2ndBlock::serializeObject(void)
{
  serialize<int32_t>(Unknown1, UNKNOWN1_LEN);

  serializeSize<uint32_t>(Count1, FirstSubDatas.size());
  serialize<int32_t>(Pointer1);
  serializeSub<FirstSubData>(FirstSubDatas, Count1);

  serializeSize<uint32_t>(Count2, SecondSubDatas.size());
  serialize<int32_t>(Pointer2);
  serializeSub<SecondSubData>(SecondSubDatas, Count2);

  serializeSize<uint32_t>(Count3, ThirdSubDatas.size());
  serialize<int32_t>(Pointer3);
  serializeSub<ThirdSubData>(ThirdSubDatas, Count3);

  serialize<int32_t>(Unknown2, UNKNOWN2_LEN);
}

//------------------------------------------------------------------------------
FirstSubData::FirstSubData() : Unknown1(UNKNOWN1_LEN)
{
}

//------------------------------------------------------------------------------
FirstSubData::~FirstSubData()
{
}

//------------------------------------------------------------------------------
void FirstSubData::serializeObject(void)
{
  serialize<int32_t>(Unknown1, UNKNOWN1_LEN);
}

//------------------------------------------------------------------------------
SecondSubData::SecondSubData() : Unknown1(UNKNOWN1_LEN)
{
}

//------------------------------------------------------------------------------
SecondSubData::~SecondSubData()
{
}

//------------------------------------------------------------------------------
void SecondSubData::serializeObject(void)
{
  serialize<int32_t>(Unknown1, UNKNOWN1_LEN);
}

//------------------------------------------------------------------------------
ThirdSubData::ThirdSubData() : Unknown1(UNKNOWN1_LEN)
{
}

//------------------------------------------------------------------------------
ThirdSubData::~ThirdSubData()
{
}

//------------------------------------------------------------------------------
void ThirdSubData::serializeObject(void)
{
  serialize<int32_t>(Unknown1, UNKNOWN1_LEN);
}

}
