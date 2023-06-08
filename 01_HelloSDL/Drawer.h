#pragma once
#include <SDL.h>

class Drawer {
public:
    static void DrawCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color);

    static void DrawFilledRect(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color color);

    static void DrawEmptyRect(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color color);

    static void DrawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, SDL_Color color);
};