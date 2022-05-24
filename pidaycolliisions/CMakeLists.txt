cmake_minimum_required(VERSION 3.0.0)
project(pidaycollisions VERSION 0.1.0)

include(CTest)
enable_testing()

# find sfml
find_package(SFML REQUIRED COMPONENTS audio graphics system window)

# link to sfml
set(SFML_INCLUDE_DIR ${SFML_INCLUDE_DIR})
set(SFML_LIBRARIES ${SFML_LIBRARIES})

add_executable(pidaycollisions src/main.cpp)
# link to sfml
target_link_libraries(pidaycollisions sfml-graphics sfml-system sfml-window)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
