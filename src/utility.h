#ifndef TOG_UTILITY_H
#define TOG_UTILITY_H

#include "game/chunk.h"
#include <glm/glm.hpp>
#include <vector>

inline glm::ivec2 calculatePlayerCurrentChunkIndex(glm::vec3 playerPosition) {
    return glm::ivec2{static_cast<int>(std::floor(playerPosition.x/CHUNK_MAX_X)), static_cast<int>(std::floor(playerPosition.z/CHUNK_MAX_Z))};
}

inline std::vector<glm::ivec2> listChunkIndicesAroundCenter(const glm::ivec2 centerChunk, int radius) {
    //add the chunk index into a ring like format
    std::vector<std::vector<glm::ivec2>> rings(static_cast<std::size_t>(radius)+1);
    int count = 1;
    rings[0].push_back(centerChunk);
    for (int dz{-radius}; dz <= radius; dz++) {
        for (int dx{-radius}; dx <= radius; dx++) {
            if (dx == 0 && dz == 0) continue;
            if ((dx*dx + dz*dz) > radius*radius) continue;
            const std::size_t index = std::max(std::abs(dx), std::abs(dz));
            rings[index].push_back({centerChunk.x + dx, centerChunk.y + dz});
            count++;
        }
    }

    //flat out into a single vector
    std::vector<glm::ivec2> out;
    out.reserve(count);
    for (int r{0}; r <= radius; r++) {
        out.insert(out.end(), rings[r].begin(), rings[r].end());
    }
    return out;
}

inline std::vector<glm::ivec2> listChunkIndicesAroundCenterSimple(const glm::ivec2 centerChunk, int radius) {
    std::vector<glm::ivec2> out;
    out.reserve(radius*radius);

    for (int dz{-radius}; dz <= radius; dz++) {
        for (int dx{-radius}; dx <= radius; dx++) {
            if ((dx*dx + dz*dz) > radius*radius) continue;
            out.push_back({centerChunk.x + dx, centerChunk.y + dz});
        }
    }

    return out;
}


#endif //TOG_UTILITY_H
