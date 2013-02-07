/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

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


#ifndef GENIE_SLPFRAME_H
#define GENIE_SLPFRAME_H

#include "genie/file/ISerializable.h"

#include <istream>
#include <vector>
#include <stdint.h>

#include "PalFile.h"


namespace genie
{
  
//------------------------------------------------------------------------------
/// Class for reading a frame of a slp file. Once loaded the image can be
/// obtained as a pixel array. A pixel is stored as the index of a color
/// in a palette.
///
/// TODO: Check file corruption
/// TODO: One (or more??) mask for player color and outline (and shadow?)
//
class SlpFrame : protected ISerializable
{
  
public:  
  //----------------------------------------------------------------------------
  /// Constructor
  ///
  SlpFrame();
  
  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~SlpFrame();
  
//   void serializeHeader(void);
    
  //----------------------------------------------------------------------------
  /// Set slp file position inside the stream. It's necesarry for calculating
  /// file offsets.
  //
  void setSlpFilePos(std::streampos pos);
  
  //----------------------------------------------------------------------------
  /// Loads header data. The headers of frames are stored after the header of 
  /// the slp file.
  //
  void loadHeader(std::istream &istr);
  
  //----------------------------------------------------------------------------
  /// Loads frame data and creates an image. Frame data is located after all
  /// frame headers of the slp file.
  //
  void load(std::istream &istr);
  
  //----------------------------------------------------------------------------
  /// Get images width.
  //
  uint32_t getWidth(void) const;
  
  //----------------------------------------------------------------------------
  /// Get images height.
  //
  uint32_t getHeight(void) const;
  
  
  //----------------------------------------------------------------------------
  /// Get index of the color that should be transparent.
  //
  uint8_t getTransparentPixelIndex(void) const;
  
  //----------------------------------------------------------------------------
  /// Returns a pixel array containing the indexes of a color in a palette.
  ///
  /// @return pixel array size of (width * height)
  //
  const uint8_t* getPixelIndexes(void) const;
  
  //----------------------------------------------------------------------------
  /// Returns the outline created by loading the frame.
  /// Outline is the border of the sprite shown if a object is behind another
  /// one.
  ///
  /// @return loaded outline
  //
  // TODO
  
  //----------------------------------------------------------------------------
  /// Returns the mask colored with color of given players index.
  ///
  /// @param player index
  /// @return player color mask
  //
  // getPlayerColorMask(uint8_t player) const; //TODO
  
  //----------------------------------------------------------------------------
  /// Get the hotspot of the frame. The Hotspot is the isometric center of 
  /// the object presented by this frame.
  ///
  /// @return x coordinate of the hotspot
  // 
  int32_t getHotspotX() const;
  
  //----------------------------------------------------------------------------
  /// Get the hotspot of the frame. The Hotspot is the isometric center of 
  /// the object presented by this frame.
  ///
  /// @return y coordinate of the hotspot
  //
  int32_t getHotspotY() const;
 
private:
  
  std::streampos slp_file_pos_;
 
  uint32_t cmd_table_offset_;
  uint32_t outline_table_offset_;
  uint32_t palette_offset_;
  uint32_t properties_;
  
  uint32_t width_;
  uint32_t height_;
  int32_t hotspot_x_;
  int32_t hotspot_y_;
  
  std::vector<int16_t> left_edges_;
  std::vector<int16_t> right_edges_;
  
 
  uint8_t transparent_index_;
  uint8_t *image_pixel_indexes_;
  
  uint8_t player_color_index_;
  
  // Element for player_color vector, the vector stores position (x, y) of
  // a player color pixel and the palette index for the color
  struct PlayerColorElement
  {
    uint32_t x;
    uint32_t y;
    uint8_t index;
  };
  
  std::vector<PlayerColorElement> player_color_mask_;
  
  //std::vector<uint8_t> payer_color_mask_;
  
  std::vector<uint8_t> img_color_index_array_;
  
  virtual void serializeObject(void);
  
  //----------------------------------------------------------------------------
  /// Reads the edges of the frame. An edge int is the number of pixels in 
  /// a row which are transparent. There are two 16 bit unsigned integers for
  /// each side of a row. One starting from left and the other starting from the
  /// right side.
  /// Assuming stream pointer is at beginning of edges array.
  //
  void readEdges();
  
  //----------------------------------------------------------------------------
  /// Reads pixel indexes from file and sets the pixels according to the
  /// colors from the palette.
  /// It is assumed that the stream pointer is at the start of the pixel array.
  ///
  /// @param row row to set pixels at
  /// @param col column to set pixels from
  /// @param count how many pixels should be read
  /// @param player_col if true, pixel will be written to player color image
  //
  void readPixelsToImage(uint32_t row, uint32_t &col, uint32_t count, 
                         bool player_col = false);
  
  //----------------------------------------------------------------------------
  /// Sets the next count of pixels to given color without reading from stream.
  ///
  /// @param row row to set pixels at
  /// @param col column to set pixels from
  /// @param count how many pixels should be set
  /// @param color color to set
  /// @param player_col if true, pixel will be written to player color image
  //
  void setPixelsToColor(uint32_t row, uint32_t &col, uint32_t count, 
                        uint8_t color_index, bool player_col = false);
  
  //----------------------------------------------------------------------------
  /// This method returns either the count stored in command byte or (if not 
  /// stored in command) the value of the next byte.
  ///
  /// @param data command byte
  //
  uint8_t getPixelCountFromData(uint8_t data);
};

typedef boost::shared_ptr<SlpFrame> SlpFramePtr;

}

#endif // GENIE_SLPFRAME_H
