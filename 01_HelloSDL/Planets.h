#pragma once

#include "Planet.h"

const float sizeScaleFactor = 5.0f;
const float speedScaleFactor = 0.01f;

class Mercury : public Planet {
public:
    Mercury(int materialIndex = 0) : Planet(0.383f * sizeScaleFactor, 0.330f, 47.87f * speedScaleFactor, 0.0f, 57.9f, materialIndex) {}
    ~Mercury() {}
};

class Venus : public Planet {
public:
    Venus(int materialIndex = 0) : Planet(0.949f * sizeScaleFactor, 4.867f, 35.02f * speedScaleFactor, 0.0f, 108.2f, materialIndex) {}
    ~Venus() {}
};

class Earth : public Planet {
public:
    Earth(int materialIndex = 0) : Planet(1.0f * sizeScaleFactor, 5.972f, 29.78f * speedScaleFactor, 0.0f, 149.6f, materialIndex) {
        this->add_moon(new Moon(0.2724f, 1.022f, 0.0f, 384.4f, this, 0.0549f));
    }

    ~Earth() {}
};
class Mars : public Planet {
public:
    Mars(int materialIndex = 0) : Planet(0.532f * sizeScaleFactor, 0.641f, 24.07f * speedScaleFactor, 0.0f, 227.9f, materialIndex) {
        moons.push_back(new Moon(0.0124f, 24.08f, 0.0f, 9.378f, this, 0.015f)); // Phobos
        moons.push_back(new Moon(0.0062f, 7.67f, 0.0f, 23.458f, this, 0.002f)); // Deimos
    }

    ~Mars() {}
};

class Jupiter : public Planet {
public:
    Jupiter(int materialIndex = 0) : Planet(7.21f * sizeScaleFactor, 1898.0f, 13.07f * speedScaleFactor, 0.0f, 321.5f, materialIndex) {}
    ~Jupiter() {}
};

class Saturn : public Planet {
public:
    Saturn(int materialIndex = 0) : Planet(6.45f * sizeScaleFactor, 568.0f, 9.68f * speedScaleFactor, 0.0f, 456.5f, materialIndex) {}
    ~Saturn() {}
};

class Uranus : public Planet {
public:
    Uranus(int materialIndex = 0) : Planet(3.01f * sizeScaleFactor, 86.8f, 6.8f * speedScaleFactor, 0.0f, 652.5f, materialIndex) {}
    ~Uranus() {}
};

class Neptune : public Planet {
public:
    Neptune(int materialIndex = 0) : Planet(1.88f * sizeScaleFactor, 102.0f, 5.43f * speedScaleFactor, 0.0f, 891.1f, materialIndex) {}
    ~Neptune() {}
};