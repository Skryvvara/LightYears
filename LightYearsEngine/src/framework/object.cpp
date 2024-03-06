#include "framework/object.h"
#include "framework/core.h"

namespace ly {
    Object::Object()
        : _is_pending_destroy{false} {

    }

    Object::~Object() {
        LOG("Object destroyed");
    }

    void Object::destroy() {
        on_destory.broadcast(this);
        _is_pending_destroy = true;
    }

    std::weak_ptr<Object> Object::get_weak_ref() {
        return shared_from_this();
    }

    std::weak_ptr<const Object> Object::get_weak_ref() const {
        return shared_from_this();
    }
}