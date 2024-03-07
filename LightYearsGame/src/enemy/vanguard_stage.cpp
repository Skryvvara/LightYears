#include <memory>
#include "framework/timer_manager.h"
#include "framework/world.h"
#include "enemy/vanguard_stage.h"
#include "enemy/vanguard.h"
#include "weapon/bullet_shooter.h"

namespace ly {
    VanguardStage::VanguardStage(World* world) : GameStage{world} {
        _spawn_interval = 1.5f;
        _switch_interval = 3.0f;
        _spawn_edge_distance = 100.0f;

        _left_spawn_location = sf::Vector2f{0.0f, 0.0f};
        _right_spawn_location = sf::Vector2f{0.0f, 0.0f};
        _spawn_location = sf::Vector2f{0.0f, 0.0f};

        _max_rows = 4;
        _current_row_count = 0;

        _enemies_per_row = 5;
        _current_enemies_count = 0;
    }

    void VanguardStage::begin_play() {
        auto window_size = get_world()->get_window_size();
        _left_spawn_location = sf::Vector2f{ _spawn_edge_distance, -100.0f };
        _right_spawn_location = sf::Vector2f{ window_size.x - _spawn_edge_distance, -100.0f };

        switch_row();
    }

    void VanguardStage::end_play() {
        TimerManager::get().clear_timer(_spawn_timer_handle);
        TimerManager::get().clear_timer(_switch_timer_handle);
    }

    void VanguardStage::tick(float delta_time) {
        GameStage::tick(delta_time);
    }

    void VanguardStage::spawn_enemies() {
        std::weak_ptr<Vanguard> new_vanguard = get_world()->spawn_actor<Vanguard>();
        new_vanguard.lock()->set_actor_location(_spawn_location);
        _current_enemies_count++;
        if (_current_enemies_count == _enemies_per_row) {
            TimerManager::get().clear_timer(_spawn_timer_handle);
            _switch_timer_handle = TimerManager::get().set_timer(get_weak_ref(), &VanguardStage::switch_row, _switch_interval, false);
        }
    }

    void VanguardStage::switch_row() {
        if (_current_row_count == _max_rows) {
            end_stage();
            return;
        }

        _current_enemies_count = 0;

        if (_spawn_location == _left_spawn_location) {
			_spawn_location = _right_spawn_location;
		} else {
			_spawn_location = _left_spawn_location;
		}


        _spawn_timer_handle = TimerManager::get().set_timer(get_weak_ref(), &VanguardStage::spawn_enemies, _spawn_interval, true);
        _current_row_count++;
    }
}
