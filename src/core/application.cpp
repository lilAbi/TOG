#include "application.h"

#include <spdlog/spdlog.h>

bool Application::init() {
    spdlog::info("Initializing sub-systems");

    spdlog::info("Starting Initializing Window...");
    if (!window.init(&camera)) {
        spdlog::critical("Failed Initializing Window");
        return false;
    }
    spdlog::info("Finished Initializing Window");

    spdlog::info("Starting Initializing Renderer...");
    if (!renderer.init()) {
        spdlog::critical("Failed Initializing Renderer");
        return false;
    }
    spdlog::info("Finished Initializing Renderer");

    spdlog::info("Starting Initializing Game...");
    if (!game.init(renderer.getSceneGraph())) {
        spdlog::critical("Failed Initializing Game");
        return false;
    }
    spdlog::info("Finished Initializing Game");

    return true;
}

void Application::run() {
    spdlog::info("Starting Application Run Loop...");
    GLFWwindow* winPtr = window.glfwWindowPtr.get();
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(winPtr)) {
        const auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(winPtr, deltaTime);

        //spdlog::info("Camera Position: {} {} {}", camera.position.x, camera.position.y, camera.position.z);

        game.tick(camera.position);

        renderer.draw(camera);

        glfwSwapBuffers(winPtr);
        glfwPollEvents();
    }

    spdlog::info("Application Finished Running");
}

void Application::processInput(GLFWwindow* winPtr, float deltaTime) {

    if (glfwGetKey(winPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(winPtr, true);

    if (glfwGetKey(winPtr, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyBoard(CameraDirection::FORWARD, deltaTime);
    if (glfwGetKey(winPtr, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyBoard(CameraDirection::BACKWARD, deltaTime);
    if (glfwGetKey(winPtr, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyBoard(CameraDirection::LEFT, deltaTime);
    if (glfwGetKey(winPtr, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyBoard(CameraDirection::RIGHT, deltaTime);

}

