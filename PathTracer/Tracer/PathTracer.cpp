/*
 * Author: Pedro José Pérez García
 * Date: 16/07/2021
 * Coms: Path tracer como tal
 */

#include "PathTracer.h"

PathTracer::PathTracer(int width, int height, int paths_per_pixel, int n_threads)
{
    this->width = width;
    this->height = height;
    this->paths_per_pixel = paths_per_pixel;
    this->n_threads = n_threads;

    cam = std::make_shared<Camera>(Vector3{ 0.001f, 0.0f, 0.0f }, width, height, 60.0f);
    workQueue = new ConcurrentBoundedQueue<int>(w * h);

    mt = std::mt19937(std::random_device()());
    dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
}

PathTracer::PathTracer(int width, int height, int paths_per_pixel, Vector3& cam_pos, int n_threads, dielec_type env)
{
    this->width = width;
    this->height = height;
    this->paths_per_pixel = paths_per_pixel;
    this->n_threads = n_threads;
    this->n_environment = fresnel_coef[env];

    cam = create_camera(cam_pos, width, height, _FOV_H);
    workQueue = new ConcurrentBoundedQueue<int>(w * h);

    mt = std::mt19937(std::random_device()());
    dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
}

void PathTracer::add_shape(std::shared_ptr<Shape> s)
{
    scene.push_back(s);
}

void PathTracer::add_point_light(std::shared_ptr<PointLight> pl)
{
    point_lights.push_back(pl);
}
