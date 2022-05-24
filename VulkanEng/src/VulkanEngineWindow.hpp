#pragma once

#include <cstdint>
#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace VulkanEngine {
	class VulkanEngineWindow {
	public:
		VulkanEngineWindow(const std::string& title, const uint32_t width, const uint32_t height);
		~VulkanEngineWindow();

		// copy constructor
		VulkanEngineWindow(const VulkanEngineWindow&) = delete;
		// copy assignment operator
		VulkanEngineWindow& operator=(const VulkanEngineWindow&) = delete;

		bool shouldClose() { return glfwWindowShouldClose(m_window); }

		void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

		VkExtent2D getExtent() { return {m_width, m_height}; }

	private:
		void initWindow();
	private:
		GLFWwindow* m_window;
		std::string m_title;
		uint32_t m_width;
		uint32_t m_height;
	};
}
