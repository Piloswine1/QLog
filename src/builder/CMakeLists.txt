add_library(builder SHARED builder.cpp builder.hpp)

set_property(TARGET builder APPEND PROPERTY
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})