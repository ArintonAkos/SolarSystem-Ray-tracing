#pragma once
#include <SDL.h>
#include "Drawable.h"

class Movable : public Drawable {
public:
    virtual void move() = 0;
};