#ifndef TOG_MESH_H
#define TOG_MESH_H

#include <vector>
#include "glm/glm.hpp"

class Mesh {
public:
    std::vector<glm::vec3> meshData;
    std::vector<glm::vec3> textureData;
};


#endif //TOG_MESH_H