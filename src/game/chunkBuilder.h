#ifndef TOG_CHUNKBUILDER_H
#define TOG_CHUNKBUILDER_H

#include "chunk.h"

#include "FastNoise/FastNoise.h"
#include <spdlog/spdlog.h>


/*
 *  The purpose of this class is to handle the
 *  creation of chunk details upon generation
 *
 */

class ChunkBuilder {
public:
    ChunkBuilder() = default;
    //generate chunk block array data
    void generateChunkBlockData(Chunk& chunk, glm::ivec2 chunkIndex);
    //generate mesh vertex data for array - Simple
    void generateChunkMeshSimple(Chunk& chunk, glm::ivec2 chunkIndex) {};
    //generate mesh vertex data for array - Greedy
    void generateChunkMeshGreedy(Chunk& chunk, glm::ivec2 chunkIndex) {};
private:
    FastNoise::SmartNode<FastNoise::Perlin> perlinNoise{FastNoise::New<FastNoise::Perlin>()};
};


#endif //TOG_CHUNKBUILDER_H