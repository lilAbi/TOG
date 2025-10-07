#ifndef TOG_WINDOW_H
#define TOG_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include "graphics/camera.h"

#include <memory>
#include <functional>

class Window {
private:
    struct GLFWWinPtrDeleter {
        void operator()(GLFWwindow* ptr) const {
            spdlog::info("Destroying GLFW Window Ptr");
            glfwDestroyWindow(ptr);
        }
    };
public:
    Window() = default;
    //initialize glfw window
    bool init(Camera* cam);
    //return unique ptr to the glfw window
public:
    std::unique_ptr<GLFWwindow, GLFWWinPtrDeleter> glfwWindowPtr{nullptr};
    int width;
    int height;
    Camera* camera{nullptr};

};


#endif //TOG_WINDOW_H