#include "chunkBuilder.h"

void ChunkBuilder::generateChunkBlockData(Chunk& chunk, glm::ivec2 chunkIndex) {
    spdlog::info("Generating Block Data for chunk at index: {},{}", chunkIndex.x, chunkIndex.y);
    spdlog::info("Chunk Block Data Size {}", chunk.blockData.size());


    std::array<float, CHUNK_MAX_X * CHUNK_MAX_Z> noiseValues{0};

    perlinNoise->GenUniformGrid2D(noiseValues.data(),
        static_cast<int>(chunkIndex.x * CHUNK_MAX_X),
        static_cast<int>(chunkIndex.y * CHUNK_MAX_Z),
        CHUNK_MAX_X, CHUNK_MAX_Z, 0.01, 1337);

    for (int y{0}; y < CHUNK_MAX_Y; y++ ) {
        for (int x{0}; x < CHUNK_MAX_X; x++) {
            for (int z{0}; z < CHUNK_MAX_Z; z++) {
                //get the max height for the particular (x,z) noise value
                int maxHeight = std::abs(static_cast<int>(noiseValues[x + (z * CHUNK_MAX_Z)]));
                chunk.blockData[z + (x * CHUNK_MAX_X) + (y * CHUNK_MAX_X * CHUNK_MAX_Y)] = (y < maxHeight ? 1 : 0);
            }
        }
    }
}
