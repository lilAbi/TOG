#ifndef TOG_APPLICATION_H
#define TOG_APPLICATION_H

#include "window.h"
#include "graphics/renderer.h"
#include "graphics/camera.h"
#include "game/game.h"

#include <memory>


class Application {
public:
    Application() = default;

    bool init();

    void run();

    void processInput(GLFWwindow* winPtr, float deltaTime);

private:
    Window window;
    Renderer renderer;
    Camera camera{{0.0f, 0.0f, 0.0f,}, {0.0f, 1.0f, 0.0f}};
    Game game;
};


#endif //TOG_APPLICATION_H