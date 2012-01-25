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


#ifndef RESEARCH_H
#define RESEARCH_H
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
  
  virtual void serializeObject(void);
  
  /// Size of RequiredTechs vector (4 in aoe/ror and 6 in games >= aok)
  unsigned short getRequiredTechsSize(void );

  /// IDs of researches that are required for this tech to appear.
  /// The size of the array is 4 in aoe/ror and 6 at games >= aok
  std::vector<short> RequiredTechs;
   
  /// Size of ResourceCosts vector (3)
  unsigned short getResourceCostsSize(void );
  
  typedef ResourceUsage<short, short, char> ResearchResourceCost;
  
  /// Resource cost in a list of max 3
  std::vector<ResearchResourceCost> ResourceCosts; //3
  
  /// Holds the number of how much of the required technologies you need.
  short RequiredTechCount;
  
  /// ID of the civilization that gets this technologie. -1 if unused
  /// MinGameVersion: aok
  short Civ;      
  
  /// Set to 1 if this tech is enabled in full tech mode or 0 if not.
  /// MinGameVersion: aok
  short FullTechMode;     
  
  /// ID of the unit where this research is available to buy.
  short ResearchLocation; 
  
  /// Index of the name in language.dll
  unsigned short LanguageDllName;
  
  /// Index of the description in language.dll
  unsigned short LanguageDllDescription;
  
  /// Number of seconds it takes to research
  short ResearchTime;
  
  /// Holds the techage id that corresponds to this data
  short TechageID;
  
  /// Age tech or not: 0 for regular and 2 for age.
  short Type;
  
  /// ID of the research's icon in icon.slp (frame number - 1)
  short IconID;
  
  /// ID of the button
  char ButtonID;
  
  /// Size of Pointers vector (3)
  static unsigned short getPointersSize();
  
  /// TODO
  /// These numbers point to something (unknown). The first number 
  /// is 100,000 plus the Language FIle ID for the name/description. The 
  /// second number is 149,000 plus the Language File ID for the 
  /// description/help. The third number has been -1 in every technology so far.
  std::vector<long> Pointers;
  
  /// Internal name
  std::string Name;
  
  /// Second internal name
  /// MinGameVersion: SWGB
  std::string Name2;
  
private:
  unsigned short NameLength;
  
  /// MinGameVersion: SWGB
  unsigned short NameLength2;
};

}

#endif // RESEARCH_H
