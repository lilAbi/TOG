#ifndef TOG_RENDERER_H
#define TOG_RENDERER_H
#include "sceneGraph.h"
#include "platform/opengl/shader.h"
#include "camera.h"

//this class handles drawing
class Renderer {
public:
    bool init();

    void draw(Camera& camera);

    void buildTextureArray();

    SceneGraph* getSceneGraph() {return &sceneGraph;}

private:
    unsigned int VBO{}, VAO{};
    unsigned int textureArray{0};
    Shader shader;
    SceneGraph sceneGraph{};
};


#endif //TOG_RENDERER_H