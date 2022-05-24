#include "VulkanEngineApp.hpp"
#include "VulkanEnginePipeline.hpp"
#include <memory>
#include <stdexcept>
#include <vulkan/vulkan_core.h>


namespace VulkanEngine {
	App::App()
	{
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
	}
	App::~App()
	{
		vkDestroyPipelineLayout(m_device.device(), m_pipelineLayout, nullptr);
	}
	void App::run(){
		while(!m_window.shouldClose())
		{
			glfwPollEvents();
		}
	}
	void App::createPipelineLayout()
	{
		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutCreateInfo.setLayoutCount = 0;
		pipelineLayoutCreateInfo.pSetLayouts = nullptr;
		pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
		pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;
		if(vkCreatePipelineLayout(m_device.device(), &pipelineLayoutCreateInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create pipeline layout!");
		}
	}
	void App::createPipeline()
	{
		auto pipelineConfig = VulkanEnginePipeline::defaultPipelineConfig(m_swapChain.width(), m_swapChain.height());
		pipelineConfig.renderPass = m_swapChain.getRenderPass();
		pipelineConfig.pipelineLayout = m_pipelineLayout;
		m_pipeline = std::make_unique<VulkanEnginePipeline>(m_device, pipelineConfig, "../src/shaders/simpshader.vert.spv", "../src/shaders/simpshader.frag.spv");
	}

}
