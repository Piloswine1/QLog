add_library(builder STATIC builder.cpp builder.hpp)

set_property(TARGET builder APPEND PROPERTY
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})
