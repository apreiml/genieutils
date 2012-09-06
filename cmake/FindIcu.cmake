# Copyright (c) 2009, Whispersoft s.r.l.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
# * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above
# copyright notice, this list of conditions and the following disclaimer
# in the documentation and/or other materials provided with the
# distribution.
# * Neither the name of Whispersoft s.r.l. nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Finds ICU library

find_program (Icu_CONFIG_EXECUTABLE icu-config)
if (NOT Icu_CONFIG_EXECUTABLE)
  set (Icu_FOUND FALSE)
else ()
  message ( STATUS "Found ICU" )
  exec_program (${Icu_CONFIG_EXECUTABLE}
    ARGS --ldflags-libsonly
    OUTPUT_VARIABLE Icu_LIBRARY
    RETURN_VALUE ERROR_CODE
    )

  if (ERROR_CODE)
    message (FATAL_ERROR "Cannot find ICU libraries: '${Icu_CONFIG_EXECUTABLE} --ldflags-libsonly' gave errors")
  endif (ERROR_CODE)

  separate_arguments(Icu_LIBRARY)

  exec_program (${Icu_CONFIG_EXECUTABLE}
    ARGS --cppflags-searchpath|sed s/^-I//
    OUTPUT_VARIABLE Icu_INCLUDE
    RETURN_VALUE ERROR_CODE
    )
  separate_arguments(Icu_INCLUDE)

  if (Icu_LIBRARY)
    set (Icu_FOUND TRUE)
  endif (Icu_LIBRARY)

endif (NOT Icu_CONFIG_EXECUTABLE)

if (Icu_FOUND)
   if (NOT Icu_FIND_QUIETLY)
      message(STATUS "Found Icu: ${Icu_LIBRARY}")
   endif (NOT Icu_FIND_QUIETLY)
else (Icu_FOUND)
   if (Icu_FIND_REQUIRED)
      message(STATUS "Looked for ICU libraries.")
      message(FATAL_ERROR "==========> Could NOT find Icu library")
   endif (Icu_FIND_REQUIRED)
endif (Icu_FOUND)
