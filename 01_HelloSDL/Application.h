#pragma once

#include <SDL.h>
#include <vector>
#include "SpaceObject.h"
#include "Camera.h"

class Application {
private:
    Camera* camera;
    std::vector<SpaceObject*> planets;
    SDL_Window* window;
    SDL_Renderer* renderer;

    void handle_errors(void (Application::* callback)());

    void runner();

    void add_planets();

    void draw_planets();

public:
    static Application* Instance;

    Application();

    void run();

    void init_components();

    void game_loop();

    void exit_instance();

    static void exit();
};