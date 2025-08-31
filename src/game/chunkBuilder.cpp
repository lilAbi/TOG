#include "chunkBuilder.h"

void ChunkBuilder::generateChunkBlockData(Chunk& chunk, glm::ivec2 chunkIndex) {
    spdlog::info("Generating Block Data for chunk at index: {},{}", chunkIndex.x, chunkIndex.y);

    std::array<float, CHUNK_MAX_X * CHUNK_MAX_Z> noiseValues{0};

    perlinNoise->GenUniformGrid2D(noiseValues.data(),
        static_cast<int>(chunkIndex.x * CHUNK_MAX_X),
        static_cast<int>(chunkIndex.y * CHUNK_MAX_Z),
        CHUNK_MAX_X, CHUNK_MAX_Z, 0.01, 1337);

    for (int y{0}; y < CHUNK_MAX_Y; y++ ) {
        for (int z{0}; z < CHUNK_MAX_Z; z++) {
            for (int x{0}; x < CHUNK_MAX_X; x++) {
                //get the max height for the particular (x,z) noise value
                int maxHeight = std::abs(static_cast<int>(noiseValues[x + (z * CHUNK_MAX_X) * 10 ]));
                chunk.blockData[x + (z * CHUNK_MAX_X) + (y * CHUNK_MAX_X * CHUNK_MAX_Z)] = (y < maxHeight ? 1 : 0);
            }
        }
    }

    //flag the chunk to be remeshed
    chunk.dirty = true;
}

void ChunkBuilder::generateChunkMeshSimple(Chunk &chunk, glm::ivec2 chunkIndex) {
    //grab the block data vector from resource manager
    //generate world chunk position coordinates
    float chunkPosX = static_cast<float>(chunkIndex.x) * CHUNK_MAX_X;
    float chunkPosY = 0.0f;
    float chunkPosZ = static_cast<float>(chunkIndex.y) * CHUNK_MAX_Z;
    //container for the vertex data about to make
    std::vector<glm::vec3> vertexData;

    //iterate through the block data array
    for (int y{0}; y < CHUNK_MAX_Y; ++y) {
        for (int z{0}; z < CHUNK_MAX_Z; ++z) {
            for (int x{0}; x < CHUNK_MAX_X; ++x) {
                //check if the block is empty- if so skip
                if(const int currBlockID = chunk.blockData[x + (z * CHUNK_MAX_X) + (y * CHUNK_MAX_X * CHUNK_MAX_Z)]; currBlockID == 0){
                    continue;
                }
                // looking at z face from the front ----
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));

                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));

                // looking at z face from the back ----
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);

                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);

                // looking at x face from the right ----
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);

                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));

                //looking at the x face from the left
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));

                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);


                //looking at the y face from the top
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);

                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y) + 1, chunkPosZ + static_cast<float>(z));

                //looking at the y face from the bottom
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);
                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));

                vertexData.emplace_back(chunkPosX + static_cast<float>(x) + 1, chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z));
                vertexData.emplace_back(chunkPosX + static_cast<float>(x), chunkPosY + static_cast<float>(y), chunkPosZ + static_cast<float>(z) + 1);

            }
        }
    }

    chunk.mesh.meshData = std::move(vertexData);
    chunk.dirty = false;
}
