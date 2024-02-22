#include "game_framework/game_application.h"
#include "framework/world.h"

ly::Application* get_application() {
    return new ly::GameApplication{};
}

namespace ly {
    GameApplication::GameApplication() {
        load_world<World>();
    }
}