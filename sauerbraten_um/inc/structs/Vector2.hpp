#pragma once

#include "includes.h"

class Vector2
{
public:
    float x;
    float y;

    Vector2();
    Vector2(float x, float y);

    float getDistance(Vector2* vec);

    friend std::ostream& operator<<(std::ostream& Str, Vector2 const& v);

};
