#pragma once
#include <memory>
#include "framework/delegate.h"

namespace ly {
    class Object : public std::enable_shared_from_this<Object> {
        public:
            Object();
            virtual ~Object();

            virtual void destroy();
            bool is_pending_destroy() const { return _is_pending_destroy; }

            std::weak_ptr<Object> get_weak_ref();
            std::weak_ptr<const Object> get_weak_ref() const;

            Delegate<Object*> on_destory;
        private:
            bool _is_pending_destroy;
    };
}