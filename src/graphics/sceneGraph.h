#ifndef TOG_SCENEGRAPH_H
#define TOG_SCENEGRAPH_H

#include "meshNode.h"
#include "game/chunk.h"
#include <absl/container/flat_hash_map.h>
#include "game/world.h"

class World;

class SceneGraph {
public:
    SceneGraph() = default;

public:
    absl::flat_hash_map<glm::ivec2, Chunk, absl::Hash<glm::ivec2>, IVec2Eq>* chunksPtr{};
    bool redraw{false};
private:
    //the head will be the players center, and from there it the chunks will be the child
    //MeshNode* head{nullptr};
    std::vector<MeshNode*> heads{};
};


#endif //TOG_SCENEGRAPH_H