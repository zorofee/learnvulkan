#pragma once
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <cstdlib>

namespace Instance
{
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;


	class HelloTriangleApp
	{


	public:
		void run()
		{
			initWindow();
			initVulkan();
			mainLoop();
			cleanup();
		}
	private:
		GLFWwindow* window;

		void initWindow()
		{
			glfwInit();
			glfwWindowHint(GLFW_CLIENT_API,GL_NONE);
			glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
			window = glfwCreateWindow(WIDTH,HEIGHT,"Vulkan",nullptr,nullptr);
		}

		void mainLoop()
		{
		
		}
		void cleanup()
		{
			//all of the other vulkan resources should be cleaned up before the instance is destroyed
			vkDestroyInstance(instance,nullptr);

			glfwDestroyWindow(window);

			glfwTerminate();
		}

	private:  //vulkan
		VkInstance instance;

		void initVulkan()
		{
			//init vulkan library
			createInstance();
		}
		void createInstance()
		{
			VkApplicationInfo appInfo{};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.apiVersion = VK_API_VERSION_1_0;
			appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pApplicationName = "Hello Vulkan";
			appInfo.pEngineName = "NOENGINE";
			//This is also one of the many structs with a pNext member that can point to extension information in the future.
			appInfo.pNext ;


			VkInstanceCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = &appInfo;

			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions;
			glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			createInfo.enabledExtensionCount = glfwExtensionCount;
			createInfo.ppEnabledExtensionNames = glfwExtensions;
			createInfo.enabledLayerCount = 0;   //talk later
			createInfo.flags;
			createInfo.pNext;
			createInfo.ppEnabledLayerNames;


			/*
			Object creation function parameters:
			1.Pointer to struct with creation info;
			2.Pointer to custom allocator callbacks ;
			3.Pointer to the variable that stores the handle to the new object.
			*/
			VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
		
			//Checking for extension support
			uint32_t extensionCount;
			vkEnumerateInstanceExtensionProperties(nullptr,&extensionCount,nullptr);

			std::vector<VkExtensionProperties> extensions(extensionCount);
			vkEnumerateInstanceExtensionProperties(nullptr,&extensionCount,extensions.data());
			std::cout << "available extensions : \n";
			for (const auto& extension:extensions)
			{
				std::cout << extension.extensionName<<" "<<extension.specVersion<<'\n';
			}
		
		}

	};

	int main()
	{
		HelloTriangleApp app;

		app.run();

		return 0;
	}
}
