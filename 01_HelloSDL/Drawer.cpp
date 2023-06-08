#include "Drawer.h"
#include <SDL.h>

void Drawer::DrawCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;

            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void Drawer::DrawFilledRect(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color color) {
    SDL_Rect fillRect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &fillRect);
}

void Drawer::DrawEmptyRect(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color color) {
    SDL_Rect borderRect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, &borderRect);
}

void Drawer::DrawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}