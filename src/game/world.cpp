#include "world.h"

bool World::init() {
    //load from memory

    return true;
}

//handles chunk generation
//handles chunk meshing
//handles updating the scene graph
void World::tick(SceneGraph* sg, glm::vec3 playerPosition) {

    //load and unload chunks around the player location
    if (const auto index = calculatePlayerCurrentChunkIndex(playerPosition); index != playerLastChunkIndex) {
        spdlog::info("Players current chunk index {},{}", index.x, index.y);

        playerLastChunkIndex = index;
    }
    //if the player is not in the last chunk coordinate
    //  update the scene graph to unload/load the chunks that are in the range
    //      if chunk is not able to be loaded, then lets go ahead and generate it

}