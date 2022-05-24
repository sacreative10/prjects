cmake_minimum_required(VERSION 3.0.0)
project(MazeGeneration VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(SFML 2.5 COMPONENTS system window graphics)

add_executable(MazeGeneration src/Renderer.cpp src/mazeCell.cpp src/Maze.cpp src/MazeGeneration.cpp)
target_link_libraries(MazeGeneration sfml-graphics sfml-window sfml-system pthread)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
