#include "core/Application.hpp"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    Application app;
    app.init();
    app.run();

    return 0;
}