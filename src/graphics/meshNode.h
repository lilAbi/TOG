#ifndef TOG_MESHNODE_H
#define TOG_MESHNODE_H

#include "mesh.h"

#include <vector>
#include <glm/glm.hpp>

struct MeshNode {
    Mesh* mesh;     //could be invalid anytime?

    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 eulerRotation{0.0f, 0.0f, 0.0f};
    glm::vec3 scale{1.0f, 1.0f, 1.0f};
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    std::vector<MeshNode*> children{};
    MeshNode* parent{nullptr};
};


#endif //TOG_MESHNODE_H