#ifndef TOG_RENDERER_H
#define TOG_RENDERER_H

#include "sceneGraph.h"
#include "platform/opengl/shader.h"

//this class handles drawing
class Renderer {
public:
    bool init();

    void draw();

    SceneGraph* getSceneGraph() {return &sceneGraph;}

private:
    unsigned int VBO{}, VAO{};
    Shader shader;
    SceneGraph sceneGraph{};
};


#endif //TOG_RENDERER_H