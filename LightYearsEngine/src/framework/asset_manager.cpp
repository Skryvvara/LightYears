#include "framework/asset_manager.h"
#include "framework/core.h"

namespace ly {
    std::unique_ptr<AssetManager> AssetManager::instance{nullptr};

    AssetManager::AssetManager() {

    }

    AssetManager& AssetManager::get() {
        if (!instance) {
            instance = std::move(std::unique_ptr<AssetManager>{new AssetManager});
        }
        return *instance;
    }

    void AssetManager::clean_cycle() {
        for(auto iter = loaded_texture_map.begin(); iter != loaded_texture_map.end();) {
            if (iter->second.unique()) {
                iter = loaded_texture_map.erase(iter);
            } else {
                ++iter;
            }
        }
    }

    std::shared_ptr<sf::Texture> AssetManager::load_texture(const std::string& path) {
        auto found = loaded_texture_map.find(path);
        if (found != loaded_texture_map.end()) {
            return found->second;
        }

        std::shared_ptr<sf::Texture> new_texture{new sf::Texture};
        if (new_texture->loadFromFile(path)) {
            loaded_texture_map.insert({path, new_texture});
            return new_texture;
        }

        return std::shared_ptr<sf::Texture>{nullptr};
    }
}