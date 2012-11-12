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


#ifndef GENIE_RESEARCH_H
#define GENIE_RESEARCH_H
#include "genie/file/ISerializable.h"
#include "ResourceUsage.h"

namespace genie
{

//TODO description. Just adding to vector in file works?
class Research : public ISerializable
{

public:
  Research();
  virtual ~Research();
  virtual void setGameVersion(GameVersion gv);
  
  /// Size of RequiredTechs vector (4 in aoe/ror and 6 in games >= aok)
  uint16_t getRequiredTechsSize(void );

  /// IDs of researches that are required for this tech to appear.
  /// The size of the array is 4 in aoe/ror and 6 at games >= aok
  std::vector<int16_t> RequiredTechs;
   
  /// Size of ResourceCosts vector (3)
  uint16_t getResourceCostsSize(void );
  
  typedef ResourceUsage<int16_t, int16_t, char> ResearchResourceCost;
  
  /// Resource cost in a list of max 3
  std::vector<ResearchResourceCost> ResourceCosts; //3
  
  /// Holds the number of how much of the required technologies you need.
  int16_t RequiredTechCount;
  
  /// ID of the civilization that gets this technologie. -1 if unused
  /// MinGameVersion: aok
  int16_t Civ;      
  
  /// Set to 1 if this tech is enabled in full tech mode or 0 if not.
  /// MinGameVersion: aok
  int16_t FullTechMode;     
  
  /// ID of the unit where this research is available to buy.
  int16_t ResearchLocation; 
  
  /// Index of the name in language.dll
  uint16_t LanguageDLLName;
  
  /// Index of the description in language.dll
  uint16_t LanguageDLLDescription;
  
  /// Number of seconds it takes to research
  int16_t ResearchTime;
  
  /// Holds the techage id that corresponds to this data
  int16_t TechageID;
  
  /// Age tech or not: 0 for regular and 2 for age.
  int16_t Type;
  
  /// ID of the research's icon in icon.slp (frame number - 1)
  int16_t IconID;
  
  /// ID of the button
  char ButtonID;
  
  /// Size of Pointers vector (3)
  static uint16_t getPointersSize();
  
  /// TODO
  /// These numbers point to something (unknown). The first number 
  /// is 100,000 plus the Language FIle ID for the name/description. The 
  /// second number is 149,000 plus the Language File ID for the 
  /// description/help. The third number has been -1 in every technology so far.
  std::vector<int32_t> Pointers;
  
  /// Internal name
  std::string Name;
  
  /// Second internal name
  /// MinGameVersion: SWGB
  std::string Name2;
  
private:
  uint16_t NameLength;
  
  /// MinGameVersion: SWGB
  uint16_t NameLength2;
  
  virtual void serializeObject(void);
};

}

#endif // GENIE_RESEARCH_H
