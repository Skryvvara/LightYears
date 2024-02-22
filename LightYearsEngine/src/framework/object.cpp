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
        _is_pending_destroy = true;
    }
}