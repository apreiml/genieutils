/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

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


#ifndef GENIE_COLOR_PALETTE_H
#define GENIE_COLOR_PALETTE_H

#include <string>
#include <vector>
#include <stdint.h>
#include <boost/shared_ptr.hpp>

#include <SFML/Graphics/Color.hpp>

#include "genie/util/Logger.h"
#include "genie/file/IFile.h"

namespace genie
{

//------------------------------------------------------------------------------
/// Class for parsing aoe color palletes.
//
class PalFile : public IFile
{

public:
  //----------------------------------------------------------------------------
  /// Constructor
  //
  PalFile();
  
  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~PalFile();
   
  //----------------------------------------------------------------------------
  /// Returns a color at given index.
  ///
  /// @param index index of color in palette
  /// @return color object
  //
  sf::Color getColorAt(uint16_t index);  
  
private:
  
  static Logger &log;
  
  std::vector<sf::Color> colors_;
  
  uint32_t num_colors_;
  
  virtual void serializeObject(void);
};

typedef boost::shared_ptr<PalFile> PalFilePtr;

}

#endif // GENIE_COLOR_PALETTE_H
