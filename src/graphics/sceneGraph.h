#ifndef TOG_SCENEGRAPH_H
#define TOG_SCENEGRAPH_H

#include "meshNode.h"

class SceneGraph {
public:
    SceneGraph() = default;

private:
    //the head will be the players center, and from there it the chunks will be the child
    //MeshNode* head{nullptr};
    std::vector<MeshNode*> heads;
};


#endif //TOG_SCENEGRAPH_H