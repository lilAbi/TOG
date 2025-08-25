#include "window.h"
#include <spdlog/spdlog.h>

static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);

bool Window::init() {
    glfwInit();
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowPtr.reset(glfwCreateWindow(1920/2, 1080/2, "Tower Of God", nullptr, nullptr));

    if (!glfwWindowPtr) {
        spdlog::critical("GLFW Window PTR failed to create");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(glfwWindowPtr.get());
    glfwSetWindowUserPointer(glfwWindowPtr.get(), static_cast<void*>(this));

    glfwSetInputMode(glfwWindowPtr.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glfwSetFramebufferSizeCallback(glfwWindowPtr.get(), frameBufferSizeCallback);
    //glfwSetKeyCallback(glfwWindowPtr.get(), keyCallback);
    //glfwSetCursorPosCallback(glfwWindowPtr.get(), cursorPositionCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::critical("Failed to initialize GLAD");
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    return true;
}

static void frameBufferSizeCallback(GLFWwindow* window, int width, int height){
    if(auto* handle{static_cast<Window*>(glfwGetWindowUserPointer(window))}; handle){
        spdlog::info("FrameBufferSize Callback Called");
        handle->width = width;
        handle->height = height;
        glViewport(0, 0, width, height);
    }
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(const auto* handle{static_cast<Window*>(glfwGetWindowUserPointer(window))}; handle) {
        //handle->eventManager->publish( std::make_shared<KeyEvent>(window, key, scancode, action, mods) );
    }
}

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
    if(const auto* handle{static_cast<Window*>(glfwGetWindowUserPointer(window))}; handle) {
        //handle->eventManager->publish( std::make_shared<MousePosEvent>(window, xpos, ypos) );
    }
}