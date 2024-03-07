#include "game_framework/game_application.h"
#include "level/game_level_1.h"
#include "framework/asset_manager.h"
#include "config.h"

ly::Application* get_application() {
    return new ly::GameApplication{};
}

namespace ly {
    GameApplication::GameApplication()
        : Application{600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close } {
        AssetManager::get().set_asset_root_dir(get_resource_dir());
        std::weak_ptr<GameLevel1> new_world = load_world<GameLevel1>();
    }
}