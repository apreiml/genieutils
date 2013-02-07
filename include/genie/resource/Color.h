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


#ifndef GENIE_COLOR_H
#define GENIE_COLOR_H

#include <stdint.h>

namespace sf
{
  class Color;
}

namespace genie
{
    
//------------------------------------------------------------------------------
/// Basic RGBA color class.
//
class Color
{
public:
  
  //----------------------------------------------------------------------------
  /// Creates a basic black color (0, 0, 0, 255)
  //
  Color();
  
  //----------------------------------------------------------------------------
  //
  Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255); 
  
  virtual ~Color();
  
  uint8_t r; /// Red
  uint8_t g; /// Green
  uint8_t b; /// Blue
  uint8_t a; /// Alpha
  
  //Static members:
  static const Color Transparent;
  
  
};

}

#endif // GENIE_COLOR_H