#include "Game.hpp"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>

#include "constants.hpp"
#include "util/load_save_png.hpp"

bool Game::init() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    // Ask for an OpenGL context version 3.3, core profile, enable debug:
    SDL_GL_ResetAttributes();
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Create window:
    window_ = SDL_CreateWindow(
        "Hookline", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        hookline::default_window_width, hookline::default_window_height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_SetWindowMinimumSize(window_, hookline::minimum_window_width,
                             hookline::minimum_window_height);

    if (!window_) {
        std::cerr << "Error creating SDL window: " << SDL_GetError()
                  << std::endl;
        return false;
    }

    // Create OpenGL context:
    context_ = SDL_GL_CreateContext(window_);

    if (!context_) {
        SDL_DestroyWindow(window_);
        std::cerr << "Error creating OpenGL context: " << SDL_GetError()
                  << std::endl;
        return 1;
    }

    // On windows, load OpenGL entrypoints: (does nothing on other platforms)
    //  init_GL();

    // Set VSYNC + Late Swap (prevents crazy FPS):
    if (SDL_GL_SetSwapInterval(-1) != 0) {
        std::cerr << "NOTE: couldn't set vsync + late swap tearing ("
                  << SDL_GetError() << ")." << std::endl;
        if (SDL_GL_SetSwapInterval(1) != 0) {
            std::cerr << "NOTE: couldn't set vsync (" << SDL_GetError() << ")."
                      << std::endl;
        }
    }

    // Set automatic SRGB encoding if framebuffer needs it:
    glEnable(GL_FRAMEBUFFER_SRGB);

    // Hide mouse cursor (note: showing can be useful for debugging):
    // SDL_ShowCursor(SDL_DISABLE);

    // Init Sound
    // --- TODO ---

    return true;
}

void Game::run() {
    // this inline function will be called whenever the window is resized,
    //  and will update the window_size and drawable_size variables:
    glm::uvec2 window_size;    // size of window (layout pixels)
    glm::uvec2 drawable_size;  // size of drawable (physical pixels)
    // On non-highDPI displays, window_size will always equal drawable_size.
    auto on_resize = [&]() {
        int w, h;
        SDL_GetWindowSize(window_, &w, &h);
        window_size = glm::uvec2(w, h);
        SDL_GL_GetDrawableSize(window_, &w, &h);
        drawable_size = glm::uvec2(w, h);
        glViewport(0, 0, drawable_size.x, drawable_size.y);
    };
    on_resize();

    // This will loop until the current mode is set to null:
    bool quit = false;
    while (!quit) {
        // every pass through the game loop creates one frame of output
        //   by performing three steps:

        {  //(1) process any events that are pending
            static SDL_Event evt;
            while (SDL_PollEvent(&evt) == 1) {
                // handle resizing:
                if (evt.type == SDL_WINDOWEVENT &&
                    evt.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    on_resize();
                }
                // handle input:
                if (/* TODO */ false) {
                    // mode handled it; great
                } else if (evt.type == SDL_QUIT) {
                    quit = true;
                    break;
                } else if (evt.type == SDL_KEYDOWN &&
                           evt.key.keysym.sym == SDLK_PRINTSCREEN) {
                    // --- screenshot key ---
                    std::string filename = "screenshot.png";
                    std::cout << "Saving screenshot to '" << filename << "'."
                              << std::endl;
                    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
                    glReadBuffer(GL_FRONT);
                    int w, h;
                    SDL_GL_GetDrawableSize(window_, &w, &h);
                    std::vector<glm::u8vec4> data(w * h);
                    glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE,
                                 data.data());
                    for (auto &px : data) {
                        px.a = 0xff;
                    }
                    save_png(filename, glm::uvec2(w, h), data.data(),
                             LowerLeftOrigin);
                }
            }
            if (quit) break;
        }

        // TODO: Update
        // TODO: Draw
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Wait until the recently-drawn frame is shown before doing it all
        // again:
        SDL_GL_SwapWindow(window_);
    }

    //------------  teardown ------------
    SDL_GL_DeleteContext(context_);
    context_ = 0;

    SDL_DestroyWindow(window_);
    window_ = NULL;
}