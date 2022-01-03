#pragma once
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <cstdlib>

namespace PhysicalDevicesAndQueueFamilies
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
			glfwWindowHint(GLFW_CLIENT_API, GL_NONE);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
			window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
		}

		void mainLoop()
		{

		}
		void cleanup()
		{
			//all of the other vulkan resources should be cleaned up before the instance is destroyed
			vkDestroyInstance(instance, nullptr);

			glfwDestroyWindow(window);

			glfwTerminate();
		}

	private:  //vulkan
		VkInstance instance;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

		void initVulkan()
		{
			//init vulkan library
			createInstance();
			pickPhysicalDevice();
		}
		void createInstance()
		{
			VkApplicationInfo appInfo{};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.apiVersion = VK_API_VERSION_1_0;
			appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pApplicationName = "Hello Vulkan";
			appInfo.pEngineName = "NOENGINE";
			//This is also one of the many structs with a pNext member that can point to extension information in the future.
			appInfo.pNext;


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
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

			std::vector<VkExtensionProperties> extensions(extensionCount);
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
			std::cout << "available extensions : \n";
			for (const auto& extension : extensions)
			{
				std::cout << extension.extensionName << " " << extension.specVersion << '\n';
			}

		}

		void pickPhysicalDevice()
		{
			uint32_t deviceCount = 0;
			vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
			if (deviceCount == 0)
			{
				throw std::runtime_error("failed to find GPUs");
			}
			std::vector<VkPhysicalDevice> devices(deviceCount);
			vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

			//Evaluate each of them and check if they are suitable for the operations.
			for (const auto& device : devices)
			{
				if (isDeviceSuitable(device))
				{
					physicalDevice = device;
				}
			}
		}

		bool isDeviceSuitable(VkPhysicalDevice device)
		{
			//Basic device properties : name ,type ,supported Vulkan versions ...
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(device,&deviceProperties);
			deviceProperties.apiVersion;
			deviceProperties.deviceID;
			deviceProperties.deviceName;
			deviceProperties.deviceType;
			deviceProperties.driverVersion;
			deviceProperties.limits;
			deviceProperties.pipelineCacheUUID;
			deviceProperties.sparseProperties;
			deviceProperties.vendorID;

			//Optional features
			VkPhysicalDeviceFeatures deviceFeatures;
			vkGetPhysicalDeviceFeatures(device,&deviceFeatures);


			//可以给所有的GPU打分排名，返回最高分;使用ordered map
			bool result = deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
				deviceFeatures.geometryShader;



			//Queue families
			QueueFamilyIndices indices = findQueueFamilies(device);

			 return true;
		}

		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphicsFamily;
		};

		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device)
		{
			QueueFamilyIndices indices;

			uint32_t queueFamilyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
			std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(device,&queueFamilyCount,queueFamilies.data());

			return indices;
		}

	};

	int main()
	{
		HelloTriangleApp app;

		app.run();

		return 0;
	}
}
