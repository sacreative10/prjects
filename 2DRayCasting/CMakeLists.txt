cmake_minimum_required(VERSION 3.0.0)
project(2DRayCasting VERSION 0.1.0)

include(CTest)
enable_testing()
# set clang compiler
set(CMAKE_C_COMPILER /usr/lib/llvm/14/bin/clang)
set(CMAKE_CXX_COMPILER /usr/lib/llvm/14/bin/clang++)
# set c++ standard to c++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_GENERATOR "Ninja")
message(STATUS "CMAKE_GENERATOR: ${CMAKE_GENERATOR}")
find_library(SFML sfml-graphics sfml-window sfml-system)

add_executable(2DRayCasting src/main.cpp src/wall.cpp src/ray.cpp src/object.cpp)
target_link_libraries(2DRayCasting sfml-graphics sfml-window sfml-system)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
