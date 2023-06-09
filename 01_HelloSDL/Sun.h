#pragma once

#include "SpaceObject.h"
#include "Drawable.h"

class Sun : public SpaceObject, public Drawable
{
public:
    Sun();
    ~Sun();
};