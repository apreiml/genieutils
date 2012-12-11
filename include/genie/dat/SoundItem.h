/*
    geniedat - A library for reading and writing data files of genie
               engine games.
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


#ifndef GENIE_SOUNDITEM_H
#define GENIE_SOUNDITEM_H

#include "genie/serialization/ISerializable.h"

#include "genie/serialization/String.h"


namespace genie
{

class SoundItem : public serial::ISerializable
{

public:
  SoundItem();
  virtual ~SoundItem();
  
  short getFileNameSize();
  
  /// File name of the resource
  /// 13 in games <= TC and 27 in games >= SWGB
  std::string FileName;
  
  /// ID of the resource in the drs file, if -1 the sound file may be stored
  /// in the Sound directory. 
  int32_t ResourceID;
  
  /// Probability out of 100 that this item will be played
  int16_t Probability;
  int16_t Civ;//not in aoe/ror
  int16_t Unknown1;//not in aoe/ror; seems to be unused in tc
  
private:
  friend class boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    serial::FixedString sFileName(FileName, getFileNameSize());
    
    ar & GENIE_NVP2("FileName", sFileName);
    
    ar & GENIE_NVP(ResourceID);
    ar & GENIE_NVP(Probability);
    
    if (getGameVersion() >= genie::GV_AoK)
    {
      ar & GENIE_NVP(Civ);
      ar & GENIE_NVP(Unknown1);
    }
  }
  
};

}

#endif // GENIE_SOUNDITEM_H
