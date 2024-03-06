#pragma once
#include <memory>
#include <functional>

namespace ly {
    class Object;
    
    template<typename... Args>
    class Delegate {
        public:
            template<typename ClassName>
            void bind_action(std::weak_ptr<Object> object, void(ClassName::*callback)(Args...)) {
                std::function<bool(Args...)> callback_func = [object, callback](Args... args) -> bool {
                    if (!object.expired()) {
                        (static_cast<ClassName*>(object.lock().get())->*callback)(args...);
                        return true;
                    }
                    return false;
                };

                callbacks.push_back(callback_func);
            }

            void broadcast(Args... args) {
                for (auto iter = callbacks.begin(); iter != callbacks.end();) {
                    if ((*iter)(args...)) {
                        ++iter;
                    } else {
                        iter = callbacks.erase(iter);
                    }
                }
            }
        private:
            std::vector<std::function<bool(Args...)>> callbacks; 
    };
}