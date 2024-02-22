#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>

namespace ly {
    class AssetManager {
        public:
            static AssetManager& get();
            std::shared_ptr<sf::Texture> load_texture(const std::string& path);
            void clean_cycle();
            void set_asset_root_dir(const std::string& directory);
        protected:
            AssetManager();
        private:
            static std::unique_ptr<AssetManager> instance;
            std::unordered_map<std::string, std::shared_ptr<sf::Texture>, std::hash<std::string>> loaded_texture_map;
            std::string asset_root_dir;
    };
}