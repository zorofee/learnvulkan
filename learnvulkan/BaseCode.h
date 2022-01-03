#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

namespace BaseCode
{
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    class HelloTriangleApplication {
    public:
        void run() {
            initWindow();
            initVulkan();
            mainLoop();
            cleanup();
        }

    private:
        GLFWwindow* window;

        void initWindow() {
            /*
            glfwInit();
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
            */

            //initialize the GLFW library
            glfwInit();
            //GLFW原本设计用于创建OpenGL context,因此这里需要告诉它不要创建OpenGL context
            glfwInitHint(GLFW_CLIENT_API,GLFW_NO_API);
            glfwInitHint(GLFW_RESIZABLE,GLFW_FALSE);
            window =  glfwCreateWindow(WIDTH,HEIGHT,"Vulkan",nullptr,nullptr);
        }

        void initVulkan() {

        }

        void mainLoop() {
           /* while (!glfwWindowShouldClose(window)) {
                glfwPollEvents();
            }*/

            while (!glfwWindowShouldClose(window))
            {
                /*
                告诉GLFW检查所有等待处理的事件和消息，包括操作系统和窗口系统中应当处理的消息。
                如果有消息正在等待，它会先处理这些消息再返回；否则该函数会立即返回
                */
                glfwPollEvents();
            }
        }

        void cleanup() {

            //glfwDestroyWindow(window);
            //glfwTerminate();
            glfwDestroyWindow(window);
            glfwTerminate();
        }
    };

    int main() {
        HelloTriangleApplication app;

        try {
            app.run();
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }
}