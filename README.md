# genieutils #

Genieutils consists of a library and some tools to work with certain data and 
resource files of genie engine games.

Notice that this library is in developement, that means the API will change.
Please also backup your files before editing to avoid file corruption
because of possible bugs.

## Features ###

 *   reading/writing of empires*.dat and genie*.dat files
 *   reading of drs, slp and pal files (partly)
 *   reading of scn/scx files (partly)
 *   reading/writing of lagnuage*.dll files (very early implementation!)

 ## Dependencies ##
 
 To compile this project you will need at least:
   boost-iostreams >= 1.42
   boost-program-options >= 1.42
   zlib
   
 If cmake finds libiconv it will automatically enable language*.dll file
 support. Don't forget to init and update the submodules.