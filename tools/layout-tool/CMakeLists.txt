cmake_minimum_required(VERSION 3.3)

add_executable(layout-tool
  sources/layout.cpp
  sources/reader.cpp
  sources/main.cpp)
target_include_directories(layout-tool
  PRIVATE sources)
