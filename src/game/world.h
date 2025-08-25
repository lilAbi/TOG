#ifndef TOG_WORLD_H
#define TOG_WORLD_H

#include "chunk.h"
#include "graphics/sceneGraph.h"

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>



//
class World {
public:
    World() = default;

    bool init();

    void tick(SceneGraph* sg, glm::vec3 playerPosition);

private:
    glm::ivec2 calculatePlayerCurrentChunkIndex(glm::vec3 playerPosition);

private:
    glm::ivec2 playerLastChunkIndex{-9,-9};

};


#endif //TOG_WORLD_H