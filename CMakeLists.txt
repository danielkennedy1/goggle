cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Goggle VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(goggle
    src/main.cpp
    src/index/file/FileReader.cpp
)

include_directories(
  src/
  src/index/file/
  src/core/
)
