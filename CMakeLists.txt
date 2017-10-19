# ¯\_(ツ)_/¯ vim: et ts=2 sw=2

cmake_minimum_required(VERSION 3.7)
project(byrror VERSION 0.0.0 LANGUAGES CXX)

#include_directories(
#       ext/rxcpp/Rx/v2/src/
#)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

set(SOURCE_FILES 
  main.cpp
  src/with.cpp
  src/base.cpp
  src/Stream.cpp
  src/ContainerStream.cpp
  example/iteration.cpp
)

add_executable(byrror ${SOURCE_FILES})

set_target_properties( byrror
  PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
  COMPILE_FLAGS "-pedantic -Wall -Wextra"
  C_COMPILER /usr/bin/clang
  )
