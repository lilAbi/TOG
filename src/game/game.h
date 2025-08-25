#ifndef TOG_GAME_H
#define TOG_GAME_H

#include "graphics/sceneGraph.h"
#include "world.h"

//this will contain the game state
class Game {
public:
    Game() = default;

    bool init(SceneGraph* sg);

    void tick(glm::vec3 playerPosition);

private:
    SceneGraph* sceneGraph{nullptr};
    World world;
};


#endif //TOG_GAME_H