#define STB_IMAGE_IMPLEMENTATION
#include "core/application.h"
#include "spdlog/spdlog.h"

int main() {
    Application game;

    if (game.init()) {
        game.run();
    }

    return 0;
}