#include "world.h"

bool World::init() {
    //load from memory
    //chunkContainer = std::move(std::vector<Chunk>{WORLD_MAX_X*WORLD_MAX_Z});
    //allocate enough memory up ahead
    chunks.reserve(WORLD_MAX_X*WORLD_MAX_Z);

    return true;
}

//handles chunk generation
//handles chunk meshing
//handles updating the scene graph
void World::tick(glm::vec3 playerPosition, SceneGraph* sg) {
    //load and unload chunks around the player location
    if (const auto currPlayerChunkIndex = calculatePlayerCurrentChunkIndex(playerPosition); currPlayerChunkIndex != playerLastChunkIndex) {
        spdlog::info("Players current chunk index {},{}", currPlayerChunkIndex.x, currPlayerChunkIndex.y);

        //grab the chunk indices that are around the current player
        std::vector<glm::ivec2> activeChunkIndices = listChunkIndicesAroundCenterSimple(currPlayerChunkIndex, 5);
        for (glm::ivec2& activeChunkIndex : activeChunkIndices) {
            glm::ivec2 deltaIndex = activeChunkIndex - currPlayerChunkIndex;
            //do we load or do we generate
            if (canLoadChunk(activeChunkIndex)) {
                //load chunk
                //loadChunkFromDisk(chunks[deltaIndex], activeChunkIndex);
            } else {
                //generate chunk
                chunkBuilder.generateChunkBlockData(chunks[deltaIndex], activeChunkIndex);
            }
            //does the chunk need to remesh?
            if (chunks[deltaIndex].dirty == true) {
                chunkBuilder.generateChunkMeshSimple(chunks[deltaIndex], activeChunkIndex);
            }
        }
        sg->redraw = true;
        playerLastChunkIndex = currPlayerChunkIndex;
    }
    //if the player is not in the last chunk coordinate
    //  update the scene graph to unload/load the chunks that are in the range
    //      if chunk is not able to be loaded, then lets go ahead and generate it

}