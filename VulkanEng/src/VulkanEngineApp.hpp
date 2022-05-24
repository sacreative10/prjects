#pragma once

#include "VulkanEngineSwapChain.hpp"
#include "VulkanEngineWindow.hpp"
#include "VulkanEnginePipeline.hpp"
#include "VulkanEngineDevice.hpp"
#include <cstdint>
#include <memory>
#include <vector>
#include <vulkan/vulkan_core.h>

namespace VulkanEngine {
	class App {
		public:
			static constexpr uint32_t m_width = 800;
			static constexpr uint32_t m_height = 600;

			App();
			~App();

			// copy constructor
			App(const App&) = delete;
			// copy assignment operator
			App& operator=(const App&) = delete;

		void run();
		private:
			void createPipeline();
			void createPipelineLayout();
			void createCommandBuffers(){}
			void drawFrame(){}
			VulkanEngineWindow m_window{"Vulkan Engine", m_width, m_height};
			VulkanEngineDevice m_device{m_window};
			VulkanEngineSwapChain m_swapChain{m_device, m_window.getExtent()};
			std::unique_ptr<VulkanEnginePipeline> m_pipeline;
			VkPipelineLayout m_pipelineLayout;
			std::vector<VkCommandBuffer> m_commandBuffers;
	};
}
