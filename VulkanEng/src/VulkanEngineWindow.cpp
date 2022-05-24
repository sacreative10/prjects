#include "VulkanEngineWindow.hpp"
#include <cstdint>
#include <stdexcept>
#include <string>


namespace VulkanEngine {
	VulkanEngineWindow::VulkanEngineWindow(const std::string& title, const uint32_t width, const uint32_t height) :
		m_title(title),
		m_width(width),
		m_height(height) {
			initWindow();
		}

	VulkanEngineWindow::~VulkanEngineWindow() {
		glfwDestroyWindow(m_window);

		glfwTerminate();
	}
	void VulkanEngineWindow::initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
	}

	void VulkanEngineWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface)
	{
		if(glfwCreateWindowSurface(instance, m_window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}

}
