add_library(builder SHARED builder.cpp builder.hpp)

set_property(TARGET builder APPEND PROPERTY
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/builder)

add_library(parser SHARED parser.cpp parser.hpp)

set_property(TARGET parser APPEND PROPERTY
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/parser)

add_library(QLog SHARED builder parser)