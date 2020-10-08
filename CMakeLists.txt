cmake_minimum_required(VERSION 3.10)

project(QLog_On_Cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
