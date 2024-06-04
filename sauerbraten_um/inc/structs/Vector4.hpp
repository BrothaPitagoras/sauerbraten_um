#pragma once

#include "includes.h"

class Vector4
{
public:
    float x;
    float y;
    float z;
    float w;

    Vector4();
    Vector4(float x, float y, float z, float w);

    friend std::ostream& operator<<(std::ostream& Str, Vector4 const& v);

};

