#include "Application.h"
#include <iostream>
#include <SDL.h>
#include <stdexcept>
#include <vector>
#include "SpaceObject.h"
#include "Sun.h"
#include "Planet.h"

Application* Application::Instance = nullptr;

Application::Application()
{
    window = nullptr;
	renderer = nullptr;
	Instance = this;

    glm::vec3 eye = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 at = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    camera = new Camera(eye, at, up);
}

void Application::run() {
    std::cout << "Starting application..." << std::endl;

    handle_errors(&Application::runner);
}

void Application::runner()
{
    add_planets();
    init_components();

    game_loop();
}

void Application::add_planets()
{
    planets.push_back(new Sun(320, 240, 50, { 255, 255, 0, 255 }, camera));

    planets.push_back(new Planet(100, 0.01, 20, { 255, 0, 0, 255 }, camera));
    planets.push_back(new Planet(200, 0.005, 30, { 0, 255, 0, 255 }, camera));
}

void Application::handle_errors(void (Application::* callback)())
{
    try
    {
        (this->*callback)();
        return;
    }
    catch (const char* e)
    {
        std::cerr << "An error occured: " << e << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "An error occured: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown exception" << std::endl;
    }
}

void Application::init_components()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        throw std::runtime_error("Error initializing SDL: ");
    }

    window = SDL_CreateWindow("Hello SDL!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        throw std::runtime_error("Error initializing SDL window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
    {
        throw std::runtime_error("Error initializing SDL renderer");
    }

    atexit(exit);
}

void Application::game_loop() {
    bool running = true;
    SDL_Event e;

    Uint32 time_start = SDL_GetTicks();
    Uint32 time_end;
    float delta_time = 0.0f;

    while (running)
    {
        time_end = SDL_GetTicks();

        delta_time = (time_end - time_start) / 1000.0f;
        time_start = time_end;

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            } 
            else
            {
                switch (e.type)
                {
                case SDL_KEYDOWN:
                    camera->KeyboardDown(e.key);
                    break;
                case SDL_KEYUP:
                    camera->KeyboardUp(e.key);
                    break;
                case SDL_MOUSEMOTION:
                    camera->MouseMove(e.motion);
                    break;
                }
            }
        }

        camera->Update(delta_time);

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        draw_planets();

        // Update screen
        SDL_RenderPresent(renderer);
    }

    exit();
}

void Application::draw_planets()
{
    for (auto planet : planets) {
        planet->move();
        planet->draw(renderer);
    }
}

void Application::exit_instance()
{
    std::cout << "Exiting application..." << std::endl;

    if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    if (camera != nullptr)
    {
        delete camera;
    }

    SDL_Quit();

    std::cin.get();
}

void Application::exit()
{
    if (Instance != nullptr)
    {
        Instance->exit_instance();
        delete Instance;
        Instance = nullptr;
    }
}