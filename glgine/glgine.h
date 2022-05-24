#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vulkan/vulkan.h>

// Buffer Description struct
struct BufferDescription {
    VkBufferUsageFlags usage;
    VkMemoryPropertyFlags properties;
};
