/*
 * Author: Pedro José Pérez García
 * Date: 17/07/2021
 * Coms: Data type for the camera, storing its position and rendering plane.
 */

#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include "Vector3.h"

float random_float(float a, float b);

struct Camera
{
    Vector3 o;
    Vector3 f;
    Vector3 l;
    Vector3 u;

    Vector3 generate_path_direction(const int& w, const int& h, const int& i, const int& j) const
    {
        Vector3 dir{};
        float dir_y = random_float((u.mod() / 2.0) - ((i + 1) * u.mod() / h), (u.mod() / 2.0) - (i * u.mod() / h));
        float dir_z = random_float((l.mod() / -2.0) + (j * l.mod() / w), (l.mod() / -2.0) + ((j + 1) * l.mod() / w));
        dir = Vector3{ f.x, dir_y, dir_z} - o;
        dir.normalize();
        return dir;
    }
};

std::shared_ptr<Camera> create_camera(Vector3 o, int w, int h, const float& fov_h);
