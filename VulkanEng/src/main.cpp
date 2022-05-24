#include "VulkanEngineApp.hpp"
#include <iostream>



int main()
{
    VulkanEngine::App app;

    try {
	app.run();
    } catch (const std::exception& e) {
	std::cerr << e.what() << std::endl;
	return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
