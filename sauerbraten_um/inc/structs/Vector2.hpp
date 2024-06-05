#pragma once

#include "includes.h"

class Vector2
{

public:
    float x;
    float y;

    Vector2();
    Vector2(float x, float y);

    float getDistance(const Vector2* vec) const;
};
