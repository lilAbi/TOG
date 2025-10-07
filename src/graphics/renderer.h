#ifndef TOG_RENDERER_H
#define TOG_RENDERER_H

#include "sceneGraph.h"
#include "platform/opengl/shader.h"
#include "camera.h"
#include "utility/stb_image.h"

#include <map>

//this is using counter clockwise

inline std::vector<std::string> imagesToLoad{
    "/Users/abi/CLionProjects/TOG/resources/texture/grass.png",
    "/Users/abi/CLionProjects/TOG/resources/texture/wood.png",
    "/Users/abi/CLionProjects/TOG/resources/texture/dirt.png"
};

//this class handles drawing
class Renderer {
public:
    bool init();

    void draw(Camera& camera);

    void buildTextureArray();

    SceneGraph* getSceneGraph() {return &sceneGraph;}

private:
    unsigned int VBO{}, VAO{}, TEXCOORD{};
    unsigned int textureArray{0};
    Shader shader;
    SceneGraph sceneGraph{};
};



#endif //TOG_RENDERER_H