cmake_minimum_required(VERSION 3.0.0)
project(gameengineidk VERSION 0.1.0)
include(GNUInstallDirs)
add_library(gameengineidk SHARED src/gameengineidk.cpp)
set_target_properties(gameengineidk PROPERTIES
  VERSION ${PROJECT_VERSION}
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  C_STANDARD 20
  C_STANDARD_REQUIRED ON
  SOVERSION 1
  PUBLIC_HEADER src/include/gameengineidk.h
)
configure_file(gameengineidk.pc.in gameengineidk.pc @ONLY)
install(TARGETS gameengineidk 
  LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}
)


