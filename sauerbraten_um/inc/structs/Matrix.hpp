#pragma once

#include "includes.h"
#include "structs/Vector2.hpp"
#include "structs/Vector3.hpp"

class Matrix
{
public:
    //Memory layout of data will affect order of matrix. 
        //DirectX: Usualy Row-Major
        //OpenGL: Usualy Column-Major

    //      X,   Y,   Z,   W
    float m11, m12, m13, m14; //00, 01, 02, 03
    float m21, m22, m23, m24; //04, 05, 06, 07
    float m31, m32, m33, m34; //08, 09, 10, 11
    float m41, m42, m43, m44; //12, 13, 14, 15

    bool WorldToScreen(Vector3 worldPos, int width, int height, Vector2& screenPos);

    friend std::ostream& operator<<(std::ostream& Str, Matrix const& v);

};

