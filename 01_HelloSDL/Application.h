#pragma once

#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include <vector>

#include "Camera.h"
#include "SolarSystem.h"

class Application {
private:
    Camera* camera;
    SDL_Window* window;
    SDL_GLContext context;
    SolarSystem* solarSystem;

    void handle_errors(void (Application::* callback)());
    void runner();

    void initialize_graphical_context();
    void initialize_gl_debug_context();
    void initialize_window_context();
    
    void game_loop();
    
    void exit_instance();

    void update(float delta_time);
    void render();

public:
    Application();
    ~Application();

    void run();
};