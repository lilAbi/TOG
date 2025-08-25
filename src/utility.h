#ifndef TOG_UTILITY_H
#define TOG_UTILITY_H

#include "game/chunk.h"
#include <glm/glm.hpp>
#include <vector>

inline glm::ivec2 calculatePlayerCurrentChunkIndex(glm::vec3 playerPosition) {
    return glm::ivec2{static_cast<int>(std::floor(playerPosition.x/CHUNK_MAX_X)), static_cast<int>(std::floor(playerPosition.z/CHUNK_MAX_Z))};
}

inline std::vector<glm::ivec2> grabChunkIndicesAroundCenter(const glm::ivec2 centerChunk, int radius) {
    std::vector<std::vector<glm::ivec2>> rings(static_cast<std::size_t>(radius)+1);

    for (int dz{-radius}; dz <= radius; dz++) {

    }

}


#endif //TOG_UTILITY_H
