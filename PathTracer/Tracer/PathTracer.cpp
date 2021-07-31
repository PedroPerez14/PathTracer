/*
 * Author: Pedro José Pérez García
 * Date: 16/07/2021
 * Coms: Path tracer como tal
 */

#include "PathTracer.h"
#include "../Misc/Transform.h"

PathTracer::PathTracer(int width, int height, int paths_per_pixel, int n_threads)
{
    this->width = width;
    this->height = height;
    this->paths_per_pixel = paths_per_pixel;
    this->n_threads = n_threads;
    n_environment = fresnel_coef[air];

    cam = create_camera(Vector3{ 0.001f, 0.0f, 0.0f }, width, height, (float)_FOV_H);
    workQueue = new ConcurrentBoundedQueue<int>(width * height);

    mt = std::mt19937(std::random_device()());
    dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
}

PathTracer::PathTracer(int width, int height, int paths_per_pixel, Vector3& cam_pos, int n_threads, enum dielec_type env)
{
    this->width = width;
    this->height = height;
    this->paths_per_pixel = paths_per_pixel;
    this->n_threads = n_threads;
    this->n_environment = fresnel_coef[env];

    cam = create_camera(cam_pos, width, height, (float)_FOV_H);
    workQueue = new ConcurrentBoundedQueue<int>(width * height);

    mt = std::mt19937(std::random_device()());
    dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
}

void PathTracer::set_fov(float fov)
{
    cam = create_camera(Vector3{ 0.001f, 0.0f, 0.0f }, width, height, fov);
}

void PathTracer::add_shape(std::shared_ptr<Shape> s)
{
    scene.push_back(s);
}

void PathTracer::add_point_light(std::shared_ptr<PointLight> pl)
{
    float lum_tot = 0.0f;
    point_lights.push_back(pl);

    for (shared_ptr<PointLight> pl : point_lights)
    {
        lum_tot += pl->color.mod(); //La idea original era usar la potencia, pero a ver que pasa con luminancia
    }
    for (shared_ptr<PointLight> lp : point_lights)
    {
        lp->prob = (lp->color.mod() / (float)lum_tot);
        cout << "La luz puntual " << lp->color.to_string() << " tiene Prob. " << lp->prob << endl;
    }
}

std::shared_ptr<Image> PathTracer::trace()
{
    std::vector<thread> P = std::vector<thread>(n_threads);
    shared_ptr<Image> image(new Image{});
    image->width = width;
    image->height = height;
    image->pixels = std::vector<Color>((size_t)width * height);
    cout << "Queuing work and creating worker threads..." << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            workQueue->enqueue(i * width + j);
        }
    }
    for (int i = 0; i < n_threads; i++)
    {
        P[i] = thread(&PathTracer::trace_pixel, this, ref(image), i);
    }
    for (int i = 0; i < n_threads; i++)
    {
        P[i].join();
    }
    
    cout << "Workers have finished." << endl;

    return image;
}

void PathTracer::trace_pixel(std::shared_ptr<Image>& img, int nworker)
{
    thread_local bool ray_on_air;  //Indica si el rayo está en aire o el otro medio, para calcular "bien" fresnel y refr.
    thread_local int pixel_to_trace, i, j, n_bounces;
    thread_local Color color;
    thread_local bool stop, absorb;
    thread_local Color throughput;
    thread_local Color contr_lp;
    thread_local Vector3 w_i, w_o;
    shared_ptr<Shape> closest_shape;
    thread_local Vector3 closest_intersect_point;
    thread_local Vector3 intersect_point;
    thread_local Vector3 path_point; //El punto por el que pasa el path cuando sale o cuando rebota en algo
    thread_local bool inter;
    thread_local float d;
    thread_local Color acum;
    thread_local Vector3 offset;
    thread_local RR_event rr_event;
    shared_ptr<Shape> last_shape_hit;
    //----------------------------------//
    inter = false;
    cout << "WORKER " << nworker << " starting queued tasks" << endl;
    while (workQueue->dequeue(pixel_to_trace))
    {
        i = pixel_to_trace / width;
        j = pixel_to_trace % width;
        color = Color{0.0f, 0.0f, 0.0f};
        //<paths_per_pixel> paths will be generated and calculated to get average color of a pixel
        for (int k = 0; k < paths_per_pixel; k++)
        {
            ray_on_air = true;      //Start assuming the camera isn't inside a shape
            stop = false;
            throughput = Color{ 1.0f, 1.0f, 1.0f };
            contr_lp = Color{ 0.0f, 0.0f, 0.0f };
            w_o = cam->generate_path_direction(width, height, i, j);
            path_point = cam->o;
            last_shape_hit = nullptr;
            n_bounces = 0;
            rr_event = RR_event::dif;
            //cout << "---------------------" << endl;
            //Start bouncing the path
            while (!stop && rr_event != RR_event::absorb)
            {
                float min_distance = std::numeric_limits<float>::max();
                closest_shape = nullptr;
                closest_intersect_point = Vector3{ 0.0f, 0.0f, 0.0f };
                for (const shared_ptr<Shape>& s : scene)    //Intersect path with all the geometry
                {
                    if (s != last_shape_hit || !ray_on_air) //If we're not hitting the same shape or it´s bouncing inside it
                    {
                        if (ray_on_air)
                        {
                            intersect_point = s->intersect(path_point, w_o, inter);
                        }
                        else    //Avoid surface acne in case the ray is bouncing inside a shape
                        {
                            intersect_point = s->intersect(path_point + (w_o * _SURFACEACNEDISPLACEMENT), w_o, inter);
                        }
                        if (inter)
                        {
                            d = abs((intersect_point - path_point).mod());
                            if (d < min_distance)
                            {
                                closest_shape = s;
                                min_distance = d;
                                closest_intersect_point = intersect_point;
                            }
                        }
                    }
                    /*
                    if (s != last_shape_hit)
                    {
                        intersect_point = s->intersect(path_point, w_o, inter);
                    }
                    else
                    {
                        if (!ray_on_air)
                        {
                            intersect_point = s->intersect(path_point + (w_o * _surfaceacne), w_o, inter);
                        }
                    }
                    if (inter)
                    {
                        d = abs((intersect_point - path_point).mod());
                        if (d < min_distance)
                        {
                            closest_shape = s;
                            min_distance = d;
                            closest_intersect_point = intersect_point;
                        }
                    }*/
                }
                acum = Color{0.0f, 0.0f, 0.0f};
                if (closest_shape)
                {
                    if (closest_shape->get_mat()->type == emitting)
                    {
                        acum = closest_shape->get_color(closest_intersect_point);
                        stop = true;
                    }
                    else
                    {
                        rr_event = russian_roulette(closest_shape, closest_intersect_point, w_o, acum, w_i, ray_on_air);
                        contr_lp = contr_lp + (get_point_lights(closest_intersect_point, closest_shape, rr_event, w_o) * throughput * acum);
                    }
                }
                else    //Path gets lost into the void
                {
                    acum = Color{ 0.0f, 0.0f, 0.0f };
                    contr_lp = Color{ 0.0f, 0.0f, 0.0f };
                    stop = true;
                }

                throughput = throughput * acum;
                w_o = w_i;
                w_o.normalize();
                path_point = closest_intersect_point;
                last_shape_hit = closest_shape;
                n_bounces++;    //Unused... yet (?) //TODO
            }
            color = color + throughput + contr_lp;
        }
        color = color / (float)paths_per_pixel;
        img->pixels.at((size_t)i * width + j) = color;
    }
    cout << "WORKER " << nworker << " finished its assigned work" << endl;
}

RR_event PathTracer::russian_roulette(const std::shared_ptr<Shape>& closest, const Vector3& intersect_point, const Vector3& w_o, Color& acum, Vector3& w_i, bool& on_air)
{
    thread_local float pd, ps, pt, roulette;
    thread_local Vector3 u;
    thread_local Vector3 v;
    thread_local Vector3 n;
    thread_local RR_event rr;
    thread_local Color k_d;
    thread_local Color k_s;
    thread_local Color k_t;
    thread_local mat_type type;

    u = closest->long_tan(intersect_point);
    v = closest->lat_tan(intersect_point);
    n = closest->normal_at_point(intersect_point);
    u.normalize();
    v.normalize();
    n.normalize();

    type = closest->get_mat()->type;
    switch (type)
    {
    case diffuse:
        if (dot(w_o, n) > 0.0f)
        {
            n = n * -1.0f;
        }
        k_d = closest->get_color(intersect_point);
        roulette = randomfloat(0.0f, 1.0f);
        if (roulette < (float)_STOP_THRESHOLD) {
            w_i = cosine_sampling(u, v, n, intersect_point);
            acum = k_d;
            rr = dif;
        }
        else {
            rr = absorb;
            acum = Color{ 0.0f, 0.0f, 0.0f };
        }
        break;
    case dif_spec:
        k_d = closest->get_color(intersect_point);
        k_s = closest->get_mat()->k_s;
        pd = (max_px(k_d) / (max_px(k_d) + max_px(k_s))) * (float)_STOP_THRESHOLD;
        ps = (float)_STOP_THRESHOLD - pd;
        roulette = randomfloat(0.0f, 1.0f);
        if (roulette <= pd)
        {
            if (dot(w_o, n) > 0.0f)
            {
                n = n * -1.0f;
            }
            w_i = cosine_sampling(u, v, n, intersect_point);
            acum = (k_d / (pd / (float)_STOP_THRESHOLD));
            rr = dif;
        }
        else if (roulette < (pd + ps))
        {
            if (dot(w_o, n) > 0.0f && on_air)
            {
                n = n * -1.0f;
            }
            w_i = specular_sampling(n, w_o, on_air);
            acum = (k_s / (ps / (float)_STOP_THRESHOLD));
            rr = spec;
        }
        else
        {
            rr = absorb;
            acum = Color{ 0.0f, 0.0f, 0.0f };
        }
        break;
    case dif_spec_fresnel:
        k_d = closest->get_color(intersect_point);  //Coef. difuso
        closest->fresnel(w_o, n, k_s, k_t, n_environment, on_air);
        pd = (max_px(k_d) / (max_px(k_d) + max_px(k_s))) * (float)_STOP_THRESHOLD;
        ps = (float)_STOP_THRESHOLD - pd;
        roulette = randomfloat(0.0f, 1.0f);
        if (roulette <= pd)
        {
            if (dot(w_o, n) > 0.0f)
            {
                n = n * -1.0f;
            }
            w_i = cosine_sampling(u, v, n, intersect_point);
            acum = (k_d / (pd / (float)_STOP_THRESHOLD));
            rr = dif;
        }
        else if (roulette < (pd + ps))
        {
            if (dot(w_o, n) > 0.0f && on_air)
            {
                n = n * -1.0f;
            }
            w_i = specular_sampling(n, w_o, on_air);
            acum = (k_s / (ps / (float)_STOP_THRESHOLD));
            rr = spec;
        }
        else    //Matar este path, contribución {0,0,0}
        {
            rr = absorb;
            acum = Color{ 0.0f, 0.0f, 0.0f };
        }
        break;
    case perfect_spec:
        k_s = closest->get_mat()->k_s;
        roulette = randomfloat(0.0f, 1.0f);
        if (roulette < (float)_STOP_THRESHOLD) {
            if (dot(w_o, n) > 0.0f && on_air)
            {
                n = n * -1.0f;
            }
            w_i = specular_sampling(n, w_o, on_air);
            acum = k_s;
            rr = spec;
        }
        else {
            rr = absorb;
            acum = Color{ 0.0f, 0.0f, 0.0f };
        }
        break;
    case dielectric:
        //cout << "Viene en dir: " << w_o.to_string() << endl;
        //cout << "Toca en: " << intersect_point.to_string() << endl;
        if (dot(w_o, n) > 0 && on_air)
        {
            n = n * -1.0f;
        }
        closest->fresnel(w_o, n, k_s, k_t, n_environment, on_air);
        ps = (max_px(k_s) / (max_px(k_s) + max_px(k_t))) * (float)_STOP_THRESHOLD;
        pt = (float)_STOP_THRESHOLD - ps;
        //cout << "KS: " << k_s.to_string() << endl;
        //cout << "KT: " << k_t.to_string() << endl;
        //cout << "probs: " << ps << " " << pt << endl;
        roulette = randomfloat(0.0f, 1.0f);
        if (roulette <= ps)
        {
            w_i = specular_sampling(n, w_o, on_air);
            acum = (k_s / (ps / (float)_STOP_THRESHOLD));
            rr = spec;
            //cout << "Reflejado a: " << w_i.to_string() << endl;
        }
        else if (roulette < (ps + pt))
        {
            w_i = closest->refract_ray(n, w_o, n_environment, on_air);
            acum = (k_t / (pt / (float)_STOP_THRESHOLD));
            rr = refract;
            //cout << "Refractado a: " << w_i.to_string() << endl;
        }
        else    //Matar este path, contribución {0,0,0}
        {
            rr = absorb;
            acum = Color{ 0.0f, 0.0f, 0.0f };
            //cout << "Absorbido" << endl;
        }
        break;
    case remix: //not implemented
        break;
    default:
        break;
    }
    return rr;
}

Color PathTracer::get_point_lights(Vector3 p, std::shared_ptr<Shape> shape, const RR_event& event, Vector3 w_o)
{
    thread_local Vector3 dir, p_inter, pos_lp, n, p_aux, dir_aux;
    thread_local bool inter, aux, sampled;
    thread_local Color retval;
    thread_local float dist, dist_aux, roulette, roulette_selector;
    if (event == dif)
    {
        retval = Color{ 0.0f, 0.0f, 0.0f };
        roulette = randomfloat(0.0f, 1.0f);
        roulette_selector = 0.0f;
        sampled = false;
        for (const shared_ptr<PointLight>& lp : point_lights)
        {
            roulette_selector += lp->prob;
            if ((roulette <= roulette_selector) && !sampled)
            {
                sampled = true;
                inter = false;
                pos_lp = lp->position;
                dir = pos_lp - p;
                dist = abs(dir.mod());
                Vector3 dir_norm = dir;
                p_aux = p - (w_o * (float)_SURFACEACNEDISPLACEMENT);
                dir_aux = pos_lp - p_aux;
                dir_aux.normalize();
                dir_norm.normalize();
                for (const shared_ptr<Shape>& s : scene)
                {
                    aux = false;
                    //if (s != shape)
                    //{
                        
                        p_inter = s->intersect(p, dir_norm, aux);
                        if (aux && (abs((p_inter - p).mod()) <= dist))
                        {
                            inter = true;
                        }
                        else
                        {
                            p_inter = shape->intersect(p_aux, dir_aux, aux);
                            inter = aux;
                        }
                        
                    //}
                }
                if (!inter)
                {
                    n = shape->normal_at_point(p);
                    return (lp->color * fabs(dot(n, dir_norm)) / (dist * dist));
                }
            }
        }
    }
    return retval;
}

Vector3 PathTracer::specular_sampling(Vector3 n, Vector3 w_i, const bool& on_air)
{
    if (!on_air)
    {
        n = n * -1.0f;
    }
    w_i.normalize();
    return w_i - (n * 2.0f * dot(n, w_i));
}

Vector3 PathTracer::cosine_sampling(const Vector3& u, const Vector3& v, const Vector3& n, const Vector3& origin)
{
    float theta = acos(sqrt(1.0f - randomfloat(0.0f, 1.0f)));
    float phi = 2.0f * M_PI * randomfloat(0.0f, 1.0f);
    Matrix T = base_change_matrix(u, v, n, origin);
    Vector3 w_i = mult_dir(T, Vector3{ sinf(theta) * cosf(phi), sinf(theta) * sinf(phi), cosf(theta) });
    return w_i;
}

float PathTracer::randomfloat(float a, float b)
{
    return (b - a) * dist(mt) + a;
}
