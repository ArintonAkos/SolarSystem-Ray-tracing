#pragma once

#include "Sun.h"
#include "Planet.h"

const float actualSizeScaleFactor = 0.75f; // scale sizes relative to Jupiter
const float actualDistanceScaleFactor = 1.0f; // scale distances relative to Mercury
const float speedScaleFactor = 0.005f;

class Sun : public cSun {
public:
    Sun(int materialIndex = 0, int textureIndex = -1) : cSun(50 * actualSizeScaleFactor, 3000.0f, materialIndex, textureIndex) {}
    ~Sun() {}
};

class Mercury : public Planet {
public:
    Mercury(int materialIndex = 0, int textureIndex = -1) : Planet(2.439f * actualSizeScaleFactor, 0.330f, 47.87f * speedScaleFactor, 0.0f, 57.909f * actualDistanceScaleFactor, 0.5f, materialIndex, textureIndex) {}
    ~Mercury() {}
};

class Venus : public Planet {
public:
    Venus(int materialIndex = 0, int textureIndex = -1) : Planet(6.052f * actualSizeScaleFactor, 4.867f, 35.02f * speedScaleFactor, 0.0f, 108.209f * actualDistanceScaleFactor, 0.5f, materialIndex, textureIndex) {}
    ~Venus() {}
};

class Earth : public Planet {
public:
    Earth(int materialIndex = 0, int textureIndex = -1) : Planet(6.371f * actualSizeScaleFactor, 5.972f, 29.78f * speedScaleFactor, 0.0f, 149.60f * actualDistanceScaleFactor, 0.5f, materialIndex, textureIndex) {
        this->add_moon(new Moon(0.737f * actualSizeScaleFactor, 102.2f * speedScaleFactor, 0.1f, 15.84f * actualDistanceScaleFactor, this, 0.3f));
    }
    ~Earth() {}
};

class Mars : public Planet {
public:
    Mars(int materialIndex = 0, int textureIndex = -1) : Planet(3.389f * actualSizeScaleFactor, 0.641f, 24.07f * speedScaleFactor, 0.0f, 227.92f * actualDistanceScaleFactor, 0.5f, materialIndex, textureIndex) {
        moons.push_back(new Moon(0.911f * actualSizeScaleFactor, 240.08f * speedScaleFactor, 0.0f, 12.938f * actualDistanceScaleFactor, this, 0.3f)); // Phobos radius is 11 km, distance is 9380 km
        moons.push_back(new Moon(0.646f * actualSizeScaleFactor, 76.67f * speedScaleFactor, 0.0f, 27.02346f * actualDistanceScaleFactor, this, 0.4f)); // Deimos radius is 6 km, distance is 23,460 km
    }
    ~Mars() {}
};

class Jupiter : public Planet {
public:
    Jupiter(int materialIndex = 0, int textureIndex = -1) : Planet(69.911f * actualSizeScaleFactor, 1898.0f, 13.07f * speedScaleFactor, 0.0f, 778.57f * actualDistanceScaleFactor, 0.5f, materialIndex, textureIndex) {}
    ~Jupiter() {}
};

class Saturn : public Planet {
public:
    Saturn(int materialIndex = 0, int textureIndex = -1) : Planet(58.232f * actualSizeScaleFactor, 568.0f, 9.68f * speedScaleFactor, 0.0f, 1433.53f * actualDistanceScaleFactor, 0.5f, materialIndex, textureIndex) {}
    ~Saturn() {}
};

class Uranus : public Planet {
public:
    Uranus(int materialIndex = 0, int textureIndex = -1) : Planet(25.362f * actualSizeScaleFactor, 86.8f, 6.8f * speedScaleFactor, 0.0f, 2872.46f * actualDistanceScaleFactor, 0.5f, materialIndex, textureIndex) {}
    ~Uranus() {}
};

class Neptune : public Planet {
public:
    Neptune(int materialIndex = 0, int textureIndex = -1) : Planet(24.622f * actualSizeScaleFactor, 102.0f, 5.43f * speedScaleFactor, 0.0f, 4495.06f * actualDistanceScaleFactor, 0.5f, materialIndex, textureIndex) {}
    ~Neptune() {}
};