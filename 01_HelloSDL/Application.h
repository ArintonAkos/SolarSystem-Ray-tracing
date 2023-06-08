#pragma once

#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include <vector>

#include "SpaceObject.h"
#include "Camera.h"

class Application {
private:
    Camera* camera;
    // std::vector<SpaceObject*> planets;
    SDL_Window* window;
    SDL_GLContext context;

    void handle_errors(void (Application::* callback)());
    void runner();
    void add_planets();
    void draw_planets();

    void update(float delta_time);
    void render();

public:
    Application();
    ~Application();

    void run();
    void initialize_graphical_context();
    void initialize_window_context();
    void game_loop();
    void exit_instance();
};