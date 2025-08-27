#include "world.h"

bool World::init() {
    //load from memory


    return true;
}

//handles chunk generation
//handles chunk meshing
//handles updating the scene graph
void World::tick(glm::vec3 playerPosition) {

    //load and unload chunks around the player location
    if (const auto currPlayerChunkIndex = calculatePlayerCurrentChunkIndex(playerPosition); currPlayerChunkIndex != playerLastChunkIndex) {
        spdlog::info("Players current chunk index {},{}", currPlayerChunkIndex.x, currPlayerChunkIndex.y);

        //grab the chunk indices that are around the current player
        std::vector<glm::ivec2> activeChunkIndices = listChunkIndicesAroundCenterSimple(currPlayerChunkIndex, 3);

        //
        for (glm::ivec2& activeChunkIndex : activeChunkIndices) {
            glm::ivec2 deltaIndex = activeChunkIndex - currPlayerChunkIndex;
            //do we load or do we generate
            if (canLoadChunk(activeChunkIndex)) {
                //load chunk
                //loadChunkFromDisk(chunks[deltaIndex], activeChunkIndex);
            } else {
                //generate chunk
                //chunkBuilder.chunkbuild(activeChunkIndex, chunks[deltaIndex])
                //
            }

        }


        playerLastChunkIndex = currPlayerChunkIndex;
    }
    //if the player is not in the last chunk coordinate
    //  update the scene graph to unload/load the chunks that are in the range
    //      if chunk is not able to be loaded, then lets go ahead and generate it

}