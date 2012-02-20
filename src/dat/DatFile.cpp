/*
    genie/dat - A library for reading and writing data files of genie
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


#include "genie/dat/DatFile.h"

#include <fstream>
#include <vector>

#include <boost/interprocess/streams/vectorstream.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/copy.hpp>

#include "genie/Types.h"

#include "genie/dat/TerrainRestriction.h"
#include "genie/dat/PlayerColour.h"
#include "genie/dat/Sound.h"
#include "genie/dat/Graphic.h"
#include "genie/dat/Terrain.h"
#include "genie/dat/Techage.h"
#include "genie/dat/UnitHeader.h"
#include "genie/dat/Civ.h"
#include "genie/dat/Research.h"
#include "genie/dat/TerrainBorder.h"
#include "genie/dat/UnitLine.h"

namespace genie
{
  
typedef boost::interprocess::basic_vectorstream< std::vector<char> > v_stream;

//------------------------------------------------------------------------------
DatFile::DatFile() : GraphicsRendering(0), ZeroSpace(0), RenderingPlusSomething(0), 
               UnknownPreTechTree(0),
               Unknown2(0), verbose_(false), file_name_(""), file_(0), 
               file_version_(0)
               
{
  SUnknown2 = -1;
  SUnknown3 = -1;
  SUnknown4 = -1;
  SUnknown5 = -1;
  SUnknown7 = -1;
  SUnknown8 = -1;
}

//------------------------------------------------------------------------------
DatFile::DatFile(std::string file_name, GameVersion gv, bool raw) : 
           GraphicsRendering(0), ZeroSpace(0), RenderingPlusSomething(0), 
           UnknownPreTechTree(0),
           Unknown2(0), verbose_(false), file_name_(""), file_(0), 
           file_version_(0)
{
  SUnknown2 = -1;
  SUnknown3 = -1;
  SUnknown4 = -1;
  SUnknown5 = -1;
  SUnknown7 = -1;
  SUnknown8 = -1;
  
  setGameVersion(gv);
  
  try
  {
    load(file_name, raw);
  }
  catch (...)
  {
    unload();
    throw;
  }
}


//------------------------------------------------------------------------------
DatFile::~DatFile()
{ 
  unload();
}

//------------------------------------------------------------------------------
void DatFile::setFileName(std::string file_name)
{
  file_name_ = file_name;
}

//------------------------------------------------------------------------------
std::string DatFile::getFileName(void ) const
{
  return file_name_;
}


//------------------------------------------------------------------------------
void DatFile::load(std::string file_name, bool raw)
{
  unload();
  
  std::auto_ptr<std::istream> istr;
  
  if (file_name.empty())
  {
    if (file_name_.empty())
      throw std::istream::failure("Can't load file: No filename set!");
    else
      file_name = file_name_;
  }
    
  try 
  {
    istr = openFile(file_name, !raw);
    
    readObject(*istr);
  }
  catch (...)
  {
    unload();
    throw;
  }
}

//------------------------------------------------------------------------------
void DatFile::save(std::string file_name, bool raw)
{
  std::auto_ptr<std::iostream> buf_stream;
  
  if (file_name.empty())
  {
    if (file_name_.empty())
      throw std::istream::failure("Can't save file: No filename set!");
    else
      file_name = file_name_;
  }
  
  try
  {
    buf_stream = createBufferStream();
        
    writeObject(*buf_stream);
    
    writeFile(*buf_stream, file_name, !raw);
    
  }
  catch (...)
  {
    throw;
  }
  
}

//------------------------------------------------------------------------------
void DatFile::extractRaw(std::string to_file_name)
{
  unload();
  
  std::auto_ptr<std::istream> istr = openFile(file_name_, true);
  
  std::ofstream file(to_file_name.c_str(), std::ofstream::binary);
  
  boost::iostreams::copy(*istr, file);
  
  file.close();
}

//------------------------------------------------------------------------------
void DatFile::extractRaw(std::string in_file, std::string out_file)
{
  setFileName(in_file);
  extractRaw(out_file);
}

//------------------------------------------------------------------------------
void DatFile::compress(std::string in_file, std::string out_file)
{
  unload();
  
  std::ifstream file_in(in_file.c_str(), std::ifstream::binary);
 
  writeFile(file_in, out_file, true);
}

//------------------------------------------------------------------------------
void DatFile::setVerboseMode(bool verbose)
{
  verbose_ = verbose;
}

//------------------------------------------------------------------------------
void DatFile::serializeObject(void )
{
  serialize<char>(&file_version_, FILE_VERSION_LEN);
  
  if (getGameVersion() >= genie::GV_SWGB)
  {
    serializeSize<unsigned short>(civ_countSW_, Civs.size());
    serialize<long>(SUnknown2);
    serialize<long>(SUnknown3);
    serialize<long>(SUnknown4);
    serialize<long>(SUnknown5);
    
    if (verbose_)
    {
      std::cout << "Unkown1: " << civ_countSW_ << std::endl;
      std::cout << "Unkown2: " << SUnknown2 << std::endl;
      std::cout << "Unkown3: " << SUnknown3 << std::endl;
      std::cout << "Unkown4: " << SUnknown4 << std::endl;
      std::cout << "Unkown5: " << SUnknown5 << std::endl;
    }
  }
  
  serializeSize<unsigned short>(terrain_restriction_count_, TerrainRestrictions.size());
  serializeSize<unsigned short>(terrain_count_, Terrains.size());
 
  if (verbose_)
  {
    std::cout << file_version_ << std::endl;
    std::cout << "TerRestrictionCount: " <<terrain_restriction_count_ << std::endl;
    std::cout << "TerCount: " << terrain_count_ << std::endl;
  }
  
  serialize<long>(TerrainRestrictionPointers1, terrain_restriction_count_);
  
  if (getGameVersion() >= genie::GV_AoK)
    serialize<long>(TerrainRestrictionPointers2, terrain_restriction_count_);
  
  TerrainRestriction::setTerrainCount(terrain_count_);
  serializeSub<TerrainRestriction>(TerrainRestrictions, terrain_restriction_count_);
    
  serializeSize<unsigned short>(player_color_count_, PlayerColours.size());
  
  if (verbose_)
    std::cout << "PlayerColours: " << player_color_count_ << std::endl;
  
  serializeSub<PlayerColour>(PlayerColours, player_color_count_);
  
  serializeSize<unsigned short>(sound_count_, Sounds.size());
  
  if (verbose_)
    std::cout << "Sounds: " << sound_count_ << std::endl;
   
  serializeSub<Sound>(Sounds, sound_count_);
  
  serializeSize<unsigned short>(graphic_count_, GraphicPointers.size());
  serialize<long>(GraphicPointers, graphic_count_);
  serializeSubWithPointers<Graphic>(Graphics, graphic_count_, GraphicPointers);
  
  if (verbose_)
  {
    std::cout << "Graphics: " << Graphics.size() << std::endl;
    
    std::cout << "GraphicsRendering " << "(0x" << std::hex << tellg();
  }
  //TODO: AoE/RoR: maybe: 
  // struct { short unknown[3]; } terrainheader[terrain_count_]
  serialize<char>(&GraphicsRendering, TERRAIN_HEADER_SIZE);
  
  if (verbose_)
    std::cout << " to 0x" << std::hex << tellg() << std::dec << ")" << std::endl;
    
  serializeSub<Terrain>(Terrains, terrain_count_);
   
  if (verbose_)
    std::cout << "Unknown2 (empty) (0x" << std::hex << tellg() << std::dec;
  
  switch (getGameVersion())
  {
    case genie::GV_AoE:  serialize<char>(&Unknown2, (1837*2)); break; //empty (0x18b4a to 0x199a4)
    case genie::GV_RoR:  serialize<char>(&Unknown2, (1837*2)); break; //empty (0x1b61e to 0x1c478)
    case genie::GV_AoK:  serialize<char>(&Unknown2, 2); break; //empty 0xa254d
    case genie::GV_TC:   serialize<char>(&Unknown2, 0x1B6); break; //empty (0xe446a to 0xe4620)
    case genie::GV_SWGB: serialize<char>(&Unknown2, 1874); break; //1 at beginning (0x1030a5 to 0x1037f7)
    case genie::GV_CC:   serialize<char>(&Unknown2, 938);  break; //empty (0x16e1c0 to 0x16e56a)
    default: break;
  }
  
  if (verbose_)
    std::cout << " to 0x" << std::hex << tellg() << std::dec << ")" << std::endl;
  
  
  // TerrainBorders seem to be unused (are empty) in GV > RoR
  serializeSub<TerrainBorder>(TerrainBorders, 16); //TODO: fixed size?
      
  if (verbose_)
    std::cout << "RenderingPlusSomething?? (0x" << std::hex << tellg() << std::dec;
  
  switch (getGameVersion()) // Empty space.
  {
    case genie::GV_AoE:  serialize<long>(&ZeroSpace, 1); break;
    case genie::GV_RoR:  serialize<long>(&ZeroSpace, 1); break;
    case genie::GV_AoK:  serialize<long>(&ZeroSpace, 7); break;
    case genie::GV_TC:   serialize<long>(&ZeroSpace, 7); break;
    case genie::GV_SWGB: serialize<long>(&ZeroSpace, 7); break;
    case genie::GV_CC:   serialize<long>(&ZeroSpace, 7); break;
    default: break;
  }
  
  serializeSize<unsigned short>(terrain_count2_, Terrains.size());
  
  switch (getGameVersion()) // is this really the techtree?
  {
    case genie::GV_AoE:  serialize<char>(&RenderingPlusSomething, 6946); break; //(0x1f3a0 to 0x20ecc)
    case genie::GV_RoR:  serialize<char>(&RenderingPlusSomething, 15118); break; //(0x21e74 to 0x2598c)
    case genie::GV_AoK:  serialize<char>(&RenderingPlusSomething, 12722); break; //(0xa7f4b to 0xab11f)
    case genie::GV_TC:   serialize<char>(&RenderingPlusSomething, 12722); break; //(0xea01c to 0xed1f0)
    case genie::GV_SWGB: serialize<char>(&RenderingPlusSomething, 698); break; //(0x1091f3 to 0x1094cf)
    case genie::GV_CC:   serialize<char>(&RenderingPlusSomething, 698); break; //(0x173f66 to 0x174242)
    default: break;
  }
    
  if (verbose_)
    std::cout << " to 0x" <<std::hex << tellg() << std::dec << ")" << std::endl;
  
  serializeSize<unsigned long>(techage_count_, Techages.size());
  
  if (verbose_)
    std::cout << "Techage: " << techage_count_ << std::endl;
  
  serializeSub<Techage>(Techages, techage_count_);
  
  if (getGameVersion() >= genie::GV_SWGB) //pos: 0x111936
  {
    serializeSize<unsigned short>(unit_line_count_, UnitLines.size());
    serializeSub<UnitLine>(UnitLines, unit_line_count_);
  }
  
  if (getGameVersion() >= genie::GV_AoK)
  { 
    serializeSize<unsigned long>(unit_count_, UnitHeaders.size());

    if (verbose_)
      std::cout << "Unitcount: " << unit_count_ << std::endl;
    
    serializeSub<UnitHeader>(UnitHeaders, unit_count_);
  }
  
  serializeSize<unsigned short>(civ_count_, Civs.size());
  
  if (verbose_)
    std::cout << "Civcount: " << civ_count_ << std::endl;
  
  serializeSub<Civ>(Civs, civ_count_);
  
  if (getGameVersion() >= genie::GV_SWGB)
    serialize<char>(SUnknown7);
  
  serializeSize<unsigned short>(research_count_, Researchs.size());
  
  if (verbose_)
    std::cout << "Researchcount: " << research_count_ << std::endl;
  
  serializeSub<Research>(Researchs, research_count_);
  
  if (verbose_)
    std::cout << "TechTrees (before eof) (0x" << std::hex << tellg();
  
  if (getGameVersion() >= genie::GV_SWGB)
    serialize<char>(SUnknown8);
  
  if (getGameVersion() >= genie::GV_AoK)
  {
    serialize<long>(UnknownPreTechTree, 7);
    serialize<ISerializable>(TechTree);
    
  }
  
  if (verbose_)
    std::cout << "to 0x" <<std::hex << tellg() << std::dec << ")" << std::endl;  
}

//------------------------------------------------------------------------------
void DatFile::unload()
{
  TerrainRestrictionPointers1.clear();
  TerrainRestrictionPointers2.clear();
  TerrainRestrictions.clear();
  PlayerColours.clear();
  Sounds.clear();
  GraphicPointers.clear();
  Graphics.clear();
  Terrains.clear();
  Techages.clear();
  TechTree.TechTreeAges.clear();
  TechTree.BuildingConnections.clear();
  TechTree.UnitConnections.clear();
  TechTree.ResearchConnections.clear();
  UnitHeaders.clear();
  Civs.clear();
  Researchs.clear();
  UnitLines.clear();
  TerrainBorders.clear();
  UnknownPreTechTree.clear();
  
  delete [] file_version_;
  delete [] GraphicsRendering;
  delete [] ZeroSpace; 
  delete [] RenderingPlusSomething; 
  delete [] Unknown2;
  
  file_version_ = 0;
  GraphicsRendering = 0;
  ZeroSpace = 0;
  RenderingPlusSomething = 0;
  Unknown2 = 0;
}

//------------------------------------------------------------------------------
boost::iostreams::zlib_params DatFile::getZlibParams(void ) const
{  
  namespace io = boost::iostreams;
  
  io::zlib_params params;
  
  // important
  params.window_bits = -15;
  
  // default
  params.level = -1;
  params.method = io::zlib::deflated;
  params.mem_level = 9;
  params.strategy = io::zlib::default_strategy;
  
  return params;
}

//------------------------------------------------------------------------------
std::auto_ptr<std::istream> DatFile::openFile(std::string file_name, bool compressed)
{
  namespace io = boost::iostreams;
  
  try
  {
    io::filtering_istreambuf in;
    
    io::file_source file(file_name, std::fstream::binary);
    
    if (!file.is_open())
      throw std::istream::failure("Can't read file: " + file_name);
    
    // register decompressor
    if (compressed)
      in.push(io::zlib_decompressor(getZlibParams()));
    
    in.push(file);
        
    // extract file to buffer
    std::vector<char> file_buf;
    io::back_insert_device< std::vector<char> > b_ins(file_buf); 
    
    io::copy(in, b_ins);
    
    return std::auto_ptr<std::istream>(new v_stream(file_buf)); 
  }
  catch ( const io::zlib_error &z_err)
  {
    std::cerr << "Zlib decompression failed with error code: "
              <<  z_err.error() << std::endl;
    throw z_err;
  }
  
  return std::auto_ptr<std::istream>(0);
}

//------------------------------------------------------------------------------
std::auto_ptr<std::iostream> DatFile::createBufferStream(void)
{
  std::vector<char> file_buf;
  
  return std::auto_ptr<std::iostream> (new v_stream(file_buf));
}

void DatFile::writeFile(std::istream &istr, std::string file_name, bool compress)
{
  namespace io = boost::iostreams;
  
  try
  {
    io::filtering_ostreambuf out;
    
    io::file_sink file(file_name, std::fstream::binary); 
    
    if (!file.is_open())
      throw std::ostream::failure("Can't open file for writing: " + file_name);
    
    if (compress)
      out.push(io::zlib_compressor(getZlibParams()));
    
    out.push(file);
    
    io::copy (istr, out);
    
  }
  catch (const io::zlib_error &z_err)
  {
    std::cerr << "Zlib compression failed with error code: "
              <<  z_err.error() << std::endl;
    throw z_err;
  }
}

}

