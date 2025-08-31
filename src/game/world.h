#ifndef TOG_WORLD_H
#define TOG_WORLD_H

#define GLM_ENABLE_EXPERIMENTAL

#include "chunk.h"
#include "chunkBuilder.h"
#include "utility.h"
#include "graphics/sceneGraph.h"

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <spdlog/spdlog.h>
#include <absl/container/flat_hash_map.h>


constexpr int WORLD_MAX_X = 9;
constexpr int WORLD_MAX_Z = 9;

class SceneGraph;

class World {
public:
    World() = default;

    bool init();

    void tick(glm::vec3 playerPosition, SceneGraph* sg);

    bool static canLoadChunk(glm::ivec2 chunkIndexToLoad) { return false; }

    absl::flat_hash_map<glm::ivec2, Chunk, absl::Hash<glm::ivec2>, IVec2Eq>* getChunkContainer() {return &chunks;}

private:
    //the chunk index that the player was last at
    glm::ivec2 playerLastChunkIndex{INT8_MAX,INT8_MAX};
    //container has active chunks and their index in the array
    //each key is the delta change in index from the current chunk index the player is in to the remote chunk (remote - current)
    absl::flat_hash_map<glm::ivec2, Chunk, absl::Hash<glm::ivec2>, IVec2Eq> chunks;
    //container for actual chunk data
    //std::vector<Chunk> chunkContainer{WORLD_MAX_X*WORLD_MAX_Z};
    ChunkBuilder chunkBuilder;
};


#endif //TOG_WORLD_H