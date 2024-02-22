#include "entrypoint.h"
#include "framework/application.h"

int main() {
    ly::Application* app = get_application();
    app->run();
    delete app;

    return 0;
}
