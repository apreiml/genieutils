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


#include "genie/resource/PalFile.h"

#include <iostream>
#include <stdexcept>

namespace genie
{

using std::string;

Logger& PalFile::log = Logger::getLogger("genie.PalFile");

//------------------------------------------------------------------------------
PalFile::PalFile() : num_colors_(0)
{
  
}

//------------------------------------------------------------------------------
PalFile::~PalFile()
{

}

void PalFile::serializeObject(void)
{
  if (isOperation(OP_READ))
  {
    std::istream *istr = getIStream();

    *istr >> type_;
    
    if (type_.find("JASC-PAL") != 0)
    {
      log.error("Not a color palette!");
      //TODO: Exception
      return;
    }
    
    *istr >> unknown_;
    
    *istr >> num_colors_;
    
    for (uint32_t i=0; i<num_colors_; i++)
    {
      uint32_t color_in;
      sf::Color color_out;
      
      *istr >> color_in;
      color_out.r = color_in;
      
      *istr >> color_in;
      color_out.g = color_in;
      
      *istr >> color_in;
      color_out.b = color_in;
      
      color_out.a = 255;  //transparency off
      
      colors_.push_back(color_out);
    }
  }
  
}

//------------------------------------------------------------------------------
sf::Color& PalFile::operator[](uint16_t index)
{
  if (index < 0 || index >= num_colors_)
  {
    log.warn("PalFile::operator[]: index out of range!");
    throw std::out_of_range("PalFile: out of range");
  }
  
  return colors_[index];
}

}


