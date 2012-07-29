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


#ifndef GENIE_DATFILE_H
#define GENIE_DATFILE_H

#include <string>
#include <iostream>
#include <auto_ptr.h>

#include "genie/Types.h"
#include "genie/file/IFile.h"
#include "genie/file/Compressor.h"
#include "TerrainRestriction.h";
#include "PlayerColour.h";
#include "Sound.h";
#include "Graphic.h";
#include "Terrain.h";
#include "Techage.h";
#include "UnitHeader.h";
#include "Civ.h";
#include "Research.h";
#include "TerrainBorder.h";
#include "UnitLine.h";
#include "TechTree.h"

namespace boost {
namespace iostreams {
struct zlib_params;
}
}

namespace genie
{

class DatFile : public IFile
{

public:
  //----------------------------------------------------------------------------
  /// Standard constructor
  //
  DatFile();
    
  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~DatFile();
  
  //----------------------------------------------------------------------------
  /// Uncompress dat file.
  //
  void extractRaw(const char *inFile, const char *outFile);
   
  //----------------------------------------------------------------------------
  /// Debug information will be printed to stdout if activated.
  ///
  /// @param verbose true to activate
  //
  void setVerboseMode(bool verbose);
  
public:
  // File data
  static const short FILE_VERSION_LEN = 8;
 
  std::vector<int32_t> TerrainRestrictionPointers1;
  std::vector<int32_t> TerrainRestrictionPointers2;
  std::vector<TerrainRestriction> TerrainRestrictions;
  
  std::vector<PlayerColour> PlayerColours;
  
  std::vector<Sound> Sounds;
  
  std::vector<int32_t> GraphicPointers;
  std::vector<Graphic> Graphics;
        
  static const uint16_t TERRAIN_HEADER_SIZE = 138;
  char *GraphicsRendering;
  std::vector<Terrain> Terrains;
  
  std::vector<TerrainBorder> TerrainBorders;
  
  int32_t *ZeroSpace;
  char *RenderingPlusSomething;
  
  std::vector<Techage> Techages;

  std::vector<UnitHeader> UnitHeaders;
  
  std::vector<Civ> Civs;
        
  std::vector<Research> Researchs;
  
  /// Only present in gv >= SWGB
  std::vector<UnitLine> UnitLines;

  genie::TechTree TechTree;
  
  std::vector<int32_t> UnknownPreTechTree;
   
  /// TC runs fine without this empty data
  char *Unknown2;
  
   //SWGB Unknowns:
  /// Seems to be the CivCount
  int32_t SUnknown2;
  int32_t SUnknown3;
  int32_t SUnknown4;
  int32_t SUnknown5;
  
  char SUnknown7;
  char SUnknown8;
  
private:
  // if true print debug messages
  bool verbose_;
  
  std::string file_name_;
  std::fstream *file_;
  
  char *file_version_;
  
  Compressor compressor_;
  
  uint16_t terrain_restriction_count_;
  uint16_t terrain_count_;
  uint16_t terrain_count2_;
  
  uint16_t player_color_count_;
  uint16_t sound_count_;
  uint16_t graphic_count_;
  uint32_t techage_count_;
  uint32_t unit_count_;
  uint16_t civ_countSW_;
  uint16_t civ_count_;
  uint16_t research_count_;
  
  uint16_t unit_line_count_;
  
  DatFile(const DatFile &other);
  DatFile &operator=(const DatFile &other);
  
  //----------------------------------------------------------------------------
  /// Clears all data.
  //
  virtual void unload(void);
      
  virtual void serializeObject(void);
};

}

#endif // GENIE_DATFILE_H
