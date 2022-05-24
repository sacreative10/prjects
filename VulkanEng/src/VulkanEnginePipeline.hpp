#pragma once

#include <string>
#include <vector>
#include <vulkan/vulkan_core.h>
#include "VulkanEngineDevice.hpp"


namespace VulkanEngine {
	struct PipeLineConfig{
		VkViewport viewport;
		VkRect2D scissor;
		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

	class VulkanEnginePipeline {
		public:
			VulkanEnginePipeline(VulkanEngineDevice& device, const PipeLineConfig& PipelineConfig, const std::string& vertFilepath, const std::string& fragFilepath);
			~VulkanEnginePipeline();

			// copy constructor
			VulkanEnginePipeline(const VulkanEnginePipeline&) = delete;
			// copy assignment operator
			VulkanEnginePipeline& operator=(const VulkanEnginePipeline&) = delete;

			static PipeLineConfig defaultPipelineConfig(uint32_t width, uint32_t height);

		private:
			static std::vector<char> readFile(const std::string& filepath);


			void CreateGraphicsPipeline(const std::string vertFilepath, const std::string fragFilepath, const PipeLineConfig& PipelineConfig);

			void CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

			VulkanEngineDevice &m_device;
			VkPipeline m_pipeline;
			VkShaderModule m_vertShaderModule;
			VkShaderModule m_fragShaderModule;
	};
}
