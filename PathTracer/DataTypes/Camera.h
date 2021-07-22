/*
 * Author: Pedro José Pérez García
 * Date: 17/07/2021
 * Coms: Data type for the camera, storing its position and rendering plane.
 */

#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector3.h"

float random_float(float a, float b)        //Should change this to mersenne twister
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

struct Camera
{
    Vector3 o;
    Vector3 f;
    Vector3 l;
    Vector3 u;

    Vector3 generate_path_direction(const int& w, const int& h, const int& i, const int& j) const
    {
        Vector3 dir{f.x, 0.0f, 0.0f};
        dir.y = random_float((u.mod() / 2.0) - ((i + 1) * u.mod() / h), (u.mod() / 2.0) - (i * u.mod() / h));
        dir.z = random_float((l.mod() / -2.0) + (j * l.mod() / w), (l.mod() / -2.0) + ((j + 1) * l.mod() / w));
        dir = dir - o;
        dir.normalize();
        return dir;
    }
};

std::shared_ptr<Camera> create_camera(Vector3 o, int w, int h, const float& fov_h)
{
    Vector3 f{ 1.0f, 0.0f, 0.0f };
    Vector3 l{ 0.0f, 0.0f, abs(tanf((float)fov_h * ((float)M_PI / 180.0f))) };
    Vector3 u{ 0.0f, l.mod() * ((float)h / (float)w), 0.0f };

    Camera cam{ o, f, l, u };
    return std::make_shared<Camera>(cam);
}
