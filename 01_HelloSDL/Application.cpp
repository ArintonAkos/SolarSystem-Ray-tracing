#include "Application.h"
#include "GLDebugMessageCallback.h"

#include <iostream>
#include <stdexcept>
#include <sstream>

#include "Sun.h"
#include "Planet.h"

Application::Application()
{
    window = nullptr;
	context = nullptr;
    camera = nullptr;
}

Application::~Application()
{
    exit_instance();
}

void Application::run() {
    std::cout << "Starting application..." << std::endl;

    handle_errors(&Application::runner);
}

void Application::runner()
{
     add_planets();

    initialize_graphical_context();
    initialize_gl_debug_context();
    initialize_window_context();

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

void Application::initialize_graphical_context()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        throw std::runtime_error("Error initializing SDL: ");
    }

    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow("Solarsys", 100, 100, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (window == nullptr)
    {
        throw std::runtime_error("Error initializing SDL window");
    }

    context = SDL_GL_CreateContext(window);
    if (context == nullptr)
    {
        throw std::runtime_error("Error initializing OpenGL context");
    }

    SDL_GL_SetSwapInterval(1);

    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
		throw std::runtime_error("Error initializing GLEW");
	}

    int gl_major_version = -1, gl_minor_version = -1;
    glGetIntegerv(GL_MAJOR_VERSION, &gl_major_version);
    glGetIntegerv(GL_MINOR_VERSION, &gl_minor_version);

    if (gl_major_version < 0 && gl_minor_version < 0) 
    {
        throw std::runtime_error("Failed to initialize OpenGL context");
    }

    std::cout << "Running OpenGL version: " << gl_major_version << "." << gl_minor_version << std::endl;

    std::stringstream window_title;
    window_title << "OpenGL " << gl_major_version << "." << gl_minor_version;
    SDL_SetWindowTitle(window, window_title.str().c_str());
}

void Application::initialize_gl_debug_context()
{
    GLint context_flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);

    if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
        glDebugMessageCallback(GLDebugMessageCallback, nullptr);
    }
}

void Application::initialize_window_context()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // initialize camera, mesh, shader, planets
    glm::vec3 eye = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 at = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    camera = new Camera(eye, at, up);
}

void Application::update(float delta_time) 
{
    camera->Update(delta_time);
}

void Application::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bind the actual vertex array that you want to draw
    // glBindVertexArray(0);

    glBindVertexArray(0);
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

        update(delta_time);

        render();

        SDL_GL_SwapWindow(window);
    }
}

void Application::draw_planets()
{
    /*for (auto planet : planets) {
        planet->move();
        planet->draw();
    }*/
}

void Application::exit_instance()
{
    std::cout << "Exiting application..." << std::endl;

    if (context != nullptr)
    {
        SDL_GL_DeleteContext(context);
        context = nullptr;
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
}