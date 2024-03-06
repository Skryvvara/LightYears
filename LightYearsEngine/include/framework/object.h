#pragma once

namespace ly {
    class Object {
        public:
            Object();
            virtual ~Object();

            virtual void destroy();
            bool is_pending_destroy() const { return _is_pending_destroy; }
        private:
            bool _is_pending_destroy;
    };
}