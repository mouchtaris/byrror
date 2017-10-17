# ¯\_(ツ)_/¯ vim: et ts=2 sw=2

cmake_minimum_required(VERSION 3.7)
project(byrror VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#include_directories(
#       ext/rxcpp/Rx/v2/src/
#)

set(SOURCE_FILES 
  main.cpp
  src/with.cpp
  src/base.cpp
  include/with.h
  include/base.h
)

add_executable(byrror ${SOURCE_FILES})
set_target_properties( byrror
  PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
  INCLUDE_DIRECTORIES /home/nikos/op/byrror/include
  COMPILE_FLAGS "-pedantic -Wall -Wextra"
  )
