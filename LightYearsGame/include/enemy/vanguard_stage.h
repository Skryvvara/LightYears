#pragma once
#include <SFML/Graphics.hpp>
#include "framework/timer_manager.h"
#include "gameplay/game_stage.h"

namespace ly {
    class VanguardStage : public GameStage {
        public:
            VanguardStage(World* world);

            virtual void begin_play() override;
            virtual void tick(float delta_time) override;
        private:
            virtual void end_play() override;
            void spawn_enemies();
            void switch_row();

            float _spawn_interval;
            float _switch_interval;
            float _spawn_edge_distance;

            sf::Vector2f _left_spawn_location;
            sf::Vector2f _right_spawn_location;
            sf::Vector2f _spawn_location;

            TimerHandle _spawn_timer_handle;
            TimerHandle _switch_timer_handle;

            int _max_rows;
            int _current_row_count;

            int _enemies_per_row;
            int _current_enemies_count;
    };
}
