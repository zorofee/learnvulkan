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
            //GLFWԭ��������ڴ���OpenGL context,���������Ҫ��������Ҫ����OpenGL context
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
                ����GLFW������еȴ�������¼�����Ϣ����������ϵͳ�ʹ���ϵͳ��Ӧ���������Ϣ��
                �������Ϣ���ڵȴ��������ȴ�����Щ��Ϣ�ٷ��أ�����ú�������������
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