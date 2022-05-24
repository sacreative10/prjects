cmake_minimum_required(VERSION 3.0.0)
project(VulkanStuff VERSION 0.1.0)

include(CTest)
enable_testing()

# set c++ to c++17
set(CMAKE_CXX_STANDARD 17)


# define DEBUG to enable debug build
# define NODEBUG to disable debug build
# define NDEBUG to disable debug build
add_compile_definitions(DEBUG)


add_executable(VulkanStuff main.cpp)
target_link_libraries(VulkanStuff glfw vulkan)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
