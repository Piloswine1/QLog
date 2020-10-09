add_library(parser SHARED parser.cpp parser.hpp)

set_property(TARGET parser APPEND PROPERTY
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})