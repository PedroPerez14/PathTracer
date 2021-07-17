/*
 * Author: Pedro José Pérez García
 * Date: 16/07/2021
 * Coms: Declaraciones del path tracer
 */

#pragma once
#include <stdlib.h>
#include <random>
#include <vector>
#include <memory>
#include "../DataTypes/Vector3.h"
#include "../DataTypes/Material.h"
#include "../Misc/CommonDefines.h"
#include "../DataTypes/Camera.h"

enum RR_event{ dif, spec, refract, absorb };

struct image_region
{
    int row_0;
    int col_0;
    int width;
    int height;
};

class PathTracer
{
public:
    PathTracer(int width, int height, int paths_per_pixel, int n_threads = 8);
    PathTracer(int width, int height, int paths_per_pixel, Vector3& cam_pos, int n_threads = 0, dielec_type env = air);

    void add_shape(std::shared_ptr<Shape> s);
    void add_point_light(std::shared_ptr<PointLight> pl);
    std::shared_ptr<Image> trace();

private:
    mt19937 mt;
    uniform_real_distribution<float>dist;

    const float stop_threshold = _STOP_THRESHOLD;
    float n_environment = fresnel_coef[air];  //Can be changed using 2nd constructor

    //Basic elements of a scene: camera, shapes and lights
    std::shared_ptr<struct Camera> cam;
    std::vector<shared_ptr<Shape>> scene;
    std::vector<shared_ptr<PointLight>> point_lights;

    //Basic rendering info
    int width;
    int height;
    int paths_per_pixel;
    int n_threads;

    ConcurrentBoundedQueue<int>* workQueue;

    void trace_pixel(std::shared_ptr<std::vector<Color>>& img, int nworker);
    RR_event russian_roulette(const std::shared_ptr<Shape>& closest, const Vector3& intersect_point, const Vector3& w_o, Color& accum, Vector3& w_i, bool& on_air);
    Color get_point_lights(Vector3 p, std::shared_ptr<Shape> shape, const RR_event& event);

    Vector3 specular_sampling(Vector3 n, Vector3 w_i, const bool& on_air);
    Vector3 cosine_sampling(const Vector3& u, const Vector3& v, const Vector3& n, const Vector3& origin);
    
    float randomfloat(float a, float b);
};
