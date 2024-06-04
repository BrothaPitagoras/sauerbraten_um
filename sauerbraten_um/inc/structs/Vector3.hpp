#pragma once

#include "includes.h"

class Vector3
{
public:
    float x;
    float y;
    float z;

    Vector3();
    Vector3(float x, float y, float z);

    Vector3 operator-(const Vector3& other) const;
    Vector3 operator+(const Vector3& other) const;

    std::string toString();
    
    friend std::ostream& operator<<(std::ostream& Str, Vector3 const& v);

};

