cmake_minimum_required(VERSION 3.0.0)
project(Asteroid VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Asteroid main.cpp)
# link to sfml
target_link_libraries(Asteroid sfml-graphics sfml-window sfml-system)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
