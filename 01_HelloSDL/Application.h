#pragma once

#include <SDL.h>
#include <vector>
#include "SpaceObject.h"

class Application {
private:
    std::vector<SpaceObject*> planets;
    SDL_Window* window;
    SDL_Renderer* renderer;

    void handle_errors(void (Application::* callback)());

    void runner();

    void add_planets();

    void draw_planets();

public:
    static Application* Instance;

    Application() : window(nullptr), renderer(nullptr)
    {
        Instance = this;
    };

    void run();

    void init_components();

    void game_loop();

    void exit_instance();

    static void exit();
};