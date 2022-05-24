cmake_minimum_required(VERSION 3.0)

project(VulkanEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17")

# all sources are in the src directory
file(GLOB SRC_FILES src/*.cpp)


# make the executable
add_executable(VulkanEngine ${SRC_FILES})

# link to glfw and Vulkan
target_link_libraries(VulkanEngine PUBLIC glfw vulkan)
