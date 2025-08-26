#ifndef TOG_WORLD_H
#define TOG_WORLD_H

#include "chunk.h"
#include "utility.h"
#include "graphics/sceneGraph.h"
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <spdlog/spdlog.h>
#include <absl/container/flat_hash_map.h>
#include <vector>

constexpr int WORLD_MAX_X = 9;
constexpr int WORLD_MAX_Z = 9;

class World {
private:
    struct IVec2Eq {
        bool operator()(const glm::ivec2& a, const glm::ivec2& b) const noexcept {
            return a.x == b.x && a.y == b.y; // or: return glm::all(a == b);
        }
    };

public:
    World() = default;
    bool init();
    void tick(SceneGraph* sg, glm::vec3 playerPosition);

private:
    glm::ivec2 playerLastChunkIndex{INT8_MAX,INT8_MAX};
    //container has active chunks and their index in the array
    absl::flat_hash_map<glm::ivec2, int, absl::Hash<glm::ivec2>, IVec2Eq> chunks;
    //container for actual chunk data
    std::vector<Chunk> chunkContainer;
};


#endif //TOG_WORLD_H