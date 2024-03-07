#pragma once
#include <memory>
#include <functional>
#include "framework/object.h"

namespace ly {
    struct TimerHandle
	{
	public:
		TimerHandle();
		unsigned int get_timer_key() const { return _timer_key; }
	private:
		unsigned int _timer_key;
		static unsigned int _timer_key_counter;
		static unsigned int get_next_timer_key() { return ++_timer_key_counter; }
	};

	struct TimerHandleHashFunction
	{
	public:
		std::size_t operator()(const TimerHandle& timer_handle) const
		{
			return timer_handle.get_timer_key();
		}
	};

	bool operator==(const TimerHandle& lhs, const TimerHandle& rhs);

    struct Timer {
        public:
            Timer(std::weak_ptr<Object> weak_ref, std::function<void()> callback, float duration, bool repeat = false);
            void tick(float delta_time);
            bool is_expired() const;
            void set_expired();
        private:
            std::pair<std::weak_ptr<Object>, std::function<void()>> _listener;
            float _duration;
            float _counter;
            bool _repeat;
            bool _is_expired;
    };

    class TimerManager {
        public:
            static TimerManager& get();

            template<typename ClassName>
            TimerHandle set_timer(std::weak_ptr<Object> weak_ref, void(ClassName::*callback)(), float duration, bool repeat = false) {
                TimerHandle new_handle{};
                _timers.insert({new_handle, Timer(weak_ref, [=] {(static_cast<ClassName*>(weak_ref.lock().get())->*callback)(); }, duration, repeat)});
                return new_handle;
            }

            void clear_timer(TimerHandle index);

            void tick(float delta_time);
        protected:
            TimerManager();
        private:
            static std::unique_ptr<TimerManager> instance;
            std::unordered_map<TimerHandle, Timer, TimerHandleHashFunction> _timers;
    };
}