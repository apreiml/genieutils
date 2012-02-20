/*
    genieutils - <description>
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

#ifndef GENIE_COMPRESSOR_H
#define GENIE_COMPRESSOR_H

#include <boost/noncopyable.hpp>
#include <boost/smart_ptr.hpp>
#include <iostream>

namespace boost {
namespace iostreams {
struct zlib_params;
}
}

namespace genie
{
  
class Compressor : public boost::noncopyable
{
public:
  //----------------------------------------------------------------------------
  Compressor();
  
  //----------------------------------------------------------------------------
  virtual ~Compressor();
  
  //----------------------------------------------------------------------------
  /// Decompresses istream and returns buffered data.
  ///
  /// @param istr input stream to decompress
  /// @return decompressed input stream
  //
  boost::shared_ptr<std::istream> startDecompression(std::istream *istr);
  
  //----------------------------------------------------------------------------
  /// Closes decompressed stream. Returns compressed istream given at start.
  ///
  /// @return input stream given at startDecompression
  //
  std::istream *stopDecompression(void);
  
  //----------------------------------------------------------------------------
  std::iostream *startCompression(std::ostream *ostr);
  
  //----------------------------------------------------------------------------
  std::ostream *stopCompression(std::istream *ostr);
  
private:
  std::istream *istream_;
  boost::shared_ptr<std::istream> uncompressedIstream_;
  
  //----------------------------------------------------------------------------
  /// Get zlib parameters necessary for (de)compressing genie archives.
  ///
  /// @return struct with set parameters
  //
  boost::iostreams::zlib_params getZlibParams(void) const;
};

}

#endif // GENIE_COMPRESSOR_H