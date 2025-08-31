#include "game.h"

#include <spdlog/spdlog.h>

bool Game::init(SceneGraph *sg) {

    if ((sceneGraph = sg); !sceneGraph) {
        spdlog::critical("SceneGraph is NULL in game::{}", __func__);
        return false;
    }

    spdlog::info("Starting Initializing World...");
    if (!world.init()) {
        spdlog::critical("World Initialization Failed");
        return false;
    }
    spdlog::info("Finished Initializing World");

    sceneGraph->chunksPtr = world.getChunkContainer();

    return true;
}

void Game::tick(glm::vec3 playerPosition) {
    //update game state
    //update game ui
    //tick the world
    world.tick(playerPosition, sceneGraph);
}
