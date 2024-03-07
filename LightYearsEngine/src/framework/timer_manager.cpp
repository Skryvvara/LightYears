#include "framework/timer_manager.h"

namespace ly {
    unsigned int TimerHandle::_timer_key_counter = 0;

	TimerHandle::TimerHandle()
		: _timer_key{get_next_timer_key()}
	{

	}

    bool operator==(const TimerHandle& lhs, const TimerHandle& rhs)
	{
		return lhs.get_timer_key() == rhs.get_timer_key();
	}

    Timer::Timer(std::weak_ptr<Object> weak_ref, std::function<void()> callback, float duration, bool repeat)
        : _listener{weak_ref, callback} {
            _duration = duration;
            _repeat = repeat;
            _is_expired = false;
            _counter = 0.0f;
    }

    void Timer::tick(float delta_time) {
        if (is_expired()) {
            return;
        }

        _counter += delta_time;
        if (_counter >= _duration) {
            _listener.second();

            if (_repeat) {
                _counter = 0.0f;
            } else {
                set_expired();
            }
        }
    }

    bool Timer::is_expired() const {
        return _is_expired || _listener.first.expired() || _listener.first.lock()->is_pending_destroy();
    }

    void Timer::set_expired() {
        _is_expired = true;
    }

    std::unique_ptr<TimerManager> TimerManager::instance{nullptr};

    TimerManager::TimerManager() : _timers{} {

    }

    TimerManager& TimerManager::get() {
        if (!instance) {
            instance = std::move(std::unique_ptr<TimerManager>(new TimerManager{}));
        }

        return *instance;
    }

    void TimerManager::tick(float delta_time) {
        for (auto iter = _timers.begin(); iter != _timers.end();) {
            if (iter->second.is_expired()) {
                iter = _timers.erase(iter);
            } else {
                iter->second.tick(delta_time);
                ++iter;
            }
        }
    }

    void TimerManager::clear_timer(TimerHandle index) {
        auto iter = _timers.find(index);

        if (iter != _timers.end()) {
            iter->second.set_expired();
        }
    }
}