#include "core/Application.hpp"

#ifdef _WIN32
    #include <windows.h>
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
    {
        (void) hInstance;
        (void) hPrevInstance;
        (void) lpCmdLine;
        (void) nCmdShow;
        return main(__argc, __argv);
    }
#endif

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    Application app;
    app.init();
    app.run();

    return 0;
}