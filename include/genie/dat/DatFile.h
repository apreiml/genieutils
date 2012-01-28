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
#include "genie/file/ISerializable.h"

#include "TerrainRestriction.h"
#include "PlayerColour.h"
#include "Sound.h"
#include "Graphic.h"
#include "Terrain.h"
#include "Techage.h"
#include "UnitHeader.h"
#include "Civ.h"
#include "Research.h"
#include "TerrainBorder.h"
#include "UnitLine.h"
#include "TechTree.h"

namespace boost {
namespace iostreams {
struct zlib_params;
}
}

namespace genie
{

class DatFile : public ISerializable
{

public:
  //----------------------------------------------------------------------------
  /// Standard constructor
  //
  DatFile();
  
  //----------------------------------------------------------------------------
  /// Loads the file in constructor
  ///
  /// @param file_name name of the dat file to load
  /// @param gv
  /// @param raw if true, file will be loaded form an uncompressed file
  //
  DatFile(std::string file_name, GameVersion gv, bool raw=false);
  
  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~DatFile();
  
  //----------------------------------------------------------------------------
  /// Set the name of the data file to operate on.
  ///
  /// @param file_name file name
  //
  void setFileName(std::string file_name);
  
  //----------------------------------------------------------------------------
  /// Returns name of current file.
  //
  std::string getFileName(void) const;
    
  //----------------------------------------------------------------------------
  /// Loads the data from a file.
  ///
  /// @param file_name if empty or not set, file_name set with setFileName
  ///                  will be used.
  /// @param raw if true load data from a uncompressed file
  //
  void load(std::string file_name="", bool raw=false);
  
  //----------------------------------------------------------------------------
  /// Saves the data to a file.
  ///
  /// @param file_name if empty or not set, file_name set with setFileName
  ///                  will be used.
  /// @param raw if true data is saved uncompressed
  //
  void save(std::string file_name="", bool raw=false);
  
  //----------------------------------------------------------------------------
  /// Uncompress and directly store data to a file.
  //
  void extractRaw(std::string to_file_name);
  void extractRaw(std::string in_file, std::string out_file);
  
  //----------------------------------------------------------------------------
  /// Reads a raw file in and stores it compressed
  //
  void compress(std::string in_file, std::string out_file);
  
  //----------------------------------------------------------------------------
  /// Debug information will be printed to stdout if activated.
  ///
  /// @param verbose true to activate
  //
  void setVerboseMode(bool verbose);
  
public:
  // File data
  static const short FILE_VERSION_LEN = 8;
 
  std::vector<long> TerrainRestrictionPointers1;
  std::vector<long> TerrainRestrictionPointers2;
  std::vector<TerrainRestriction> TerrainRestrictions;
  
  std::vector<PlayerColour> PlayerColours;
  
  std::vector<Sound> Sounds;
  
  std::vector<long> GraphicPointers;
  std::vector<Graphic> Graphics;
        
  static const unsigned short TERRAIN_HEADER_SIZE = 138;
  char *GraphicsRendering;
  std::vector<Terrain> Terrains;
  
  std::vector<TerrainBorder> TerrainBorders;
  
  long *ZeroSpace;
  char *RenderingPlusSomething;
  
  std::vector<Techage> Techages;

  std::vector<UnitHeader> UnitHeaders;
  
  std::vector<Civ> Civs;
        
  std::vector<Research> Researchs;
  
  /// Only present in gv >= SWGB
  std::vector<UnitLine> UnitLines;

  genie::TechTree TechTree;
  
  std::vector<long> UnknownPreTechTree;
   
  /// TC runs fine without this empty data
  char *Unknown2;
  
   //SWGB Unknowns:
  /// Seems to be the CivCount
  long SUnknown2;
  long SUnknown3;
  long SUnknown4;
  long SUnknown5;
  
  char SUnknown7;
  char SUnknown8;
  
protected:
  virtual void serializeObject(void);
  
private:
  // if true print debug messages
  bool verbose_;
  
  std::string file_name_;
  std::fstream *file_;
  
  
  char *file_version_;
  
  unsigned short terrain_restriction_count_;
  unsigned short terrain_count_;
  unsigned short terrain_count2_;
  
  unsigned short player_color_count_;
  unsigned short sound_count_;
  unsigned short graphic_count_;
  unsigned long techage_count_;
  unsigned long unit_count_;
  unsigned short civ_countSW_;
  unsigned short civ_count_;
  unsigned short research_count_;
  
  unsigned short unit_line_count_;
  
  DatFile(const DatFile &other);
  DatFile &operator=(const DatFile &other);
  
  //----------------------------------------------------------------------------
  /// Clears all data.
  //
  void unload(void);
    
  //----------------------------------------------------------------------------
  /// Get zlib parameters necessary for (de)compressing genie archives.
  ///
  /// @return struct with set parameters
  //
  boost::iostreams::zlib_params getZlibParams(void) const;
  
  //----------------------------------------------------------------------------
  /// Opens an istream of the file to read from and copies it to a buffer.
  ///
  /// @param file_name 
  /// @param compressed if true it will be uncompressed on opening
  //
  std::auto_ptr<std::istream> openFile(std::string file_name, bool compressed=true);
  
  //----------------------------------------------------------------------------
  ///
  //
  std::auto_ptr<std::iostream> createBufferStream(void);
  
  //----------------------------------------------------------------------------
  /// Writes from stream to file.
  ///
  /// @param istr stream to read data from
  /// @param file_name file to write data to
  /// @param compress if output will be compressed
  //
  void writeFile(std::istream &istr, std::string file_name, bool compress=true);
};

}

#endif // GENIE_DATFILE_H
