/*
 * Author: Pedro José Pérez García
 * Date: 22/07/2021
 * Coms: Tengo que separar declaraciones e implementaciones
 */
#pragma once
#include "Camera.h"
#include <iostream>

using namespace std;

std::shared_ptr<Camera> create_camera(Vector3 o, int w, int h, const float& fov_h)
{
    Vector3 f{ 1.0f, 0.0f, 0.0f };
    Vector3 l{ 0.0f, 0.0f, abs(tanf((float)fov_h * ((float)M_PI / 180.0f))) };
    Vector3 u{ 0.0f, l.mod() * ((float)h / (float)w), 0.0f };

    cout << "F vale: " << f.to_string() << endl;
    cout << "U vale: " << u.to_string() << endl;
    cout << "L vale: " << l.to_string() << endl;

    Camera cam{ o, f, l, u };
    return std::make_shared<Camera>(cam);
}

float random_float(float a, float b)        //Should change this to mersenne twister
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}