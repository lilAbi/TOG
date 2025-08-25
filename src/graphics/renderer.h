#ifndef TOG_RENDERER_H
#define TOG_RENDERER_H

#include "sceneGraph.h"

//this class handles drawing
class Renderer {
public:
    bool init();

    void draw();

    SceneGraph* getSceneGraph() {return &sceneGraph;}

private:
    SceneGraph sceneGraph;

};


#endif //TOG_RENDERER_H