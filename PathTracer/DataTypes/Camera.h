/*
 * Author: Pedro José Pérez García
 * Date: 17/07/2021
 * Coms: Data type for the camera, storing its position and rendering plane.
 */

#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

struct Camera
{
    Vector3 o;
    Vector3 f;
    Vector3 l;
    Vector3 u;
};

std::shared_ptr<Camera> create_camera(Vector3 o, int w, int h, const float& fov_h)
{
    Vector3 f{ 1.0f, 0.0f, 0.0f };
    Vector3 l{ 0.0f, 0.0f, abs(tanf((float)fov_h * ((float)M_PI / 180.0f))) };
    Vector3 u{ 0.0f, l.mod() * ((float)h / (float)w), 0.0f };

    return std::make_shared<Camera>(o, f, l, u);
}