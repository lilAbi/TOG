#ifndef TOG_CHUNKBUILDER_H
#define TOG_CHUNKBUILDER_H

#include "chunk.h"

#include "FastNoise/FastNoise.h"
#include <spdlog/spdlog.h>
#include "utility/utility.h"

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
    void generateChunkMeshSimple(Chunk& chunk, glm::ivec2 chunkIndex);
    //generate mesh vertex data for array - Greedy
    void generateChunkMeshGreedy(Chunk& chunk, glm::ivec2 chunkIndex) {};

private:
    bool canBuildTree(glm::vec3 location);
private:
    FastNoise::SmartNode<FastNoise::Perlin> perlinNoise{FastNoise::New<FastNoise::Perlin>()};
    FastNoise::SmartNode<FastNoise::Perlin> treeNoise{FastNoise::New<FastNoise::Perlin>()};
    FastNoise::SmartNode<FastNoise::Checkerboard> checkerBoardNoise{FastNoise::New<FastNoise::Checkerboard>()};
    FastNoise::SmartNode<FastNoise::FractalFBm> fractal{FastNoise::New<FastNoise::FractalFBm>()};
};


#endif //TOG_CHUNKBUILDER_H