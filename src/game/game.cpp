#include "game.h"

#include <spdlog/spdlog.h>

bool Game::init(SceneGraph *sg) {

    if ((sceneGraph = sg); !sceneGraph) {
        spdlog::critical("SceneGraph is NULL in {}", __func__);
        return false;
    }

    return true;
}

void Game::tick(glm::vec3 playerPosition) {
    //update game state
    //update game ui
    //tick the world
    world.tick(sceneGraph, playerPosition);
}
