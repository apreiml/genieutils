project(genieutils)


find_package(Boost 1.42 COMPONENTS iostreams program_options REQUIRED)

include_directories(
    include/
    ${Boost_INCLUDE_DIRS}
    )

set(FILE_SRC
    src/file/ISerializable.cpp
    src/file/IFile.cpp
    src/file/ICompressedFile.cpp
    )

set(LANG_SRC
    src/lang/LangFile.cpp
    )



add_library(genieutils ${FILE_SRC} ${LANG_SRC})

add_executable(main main.cpp)
target_link_libraries(main genieutils)

