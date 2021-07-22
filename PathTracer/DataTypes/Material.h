/*
 * Author: Pedro José Pérez García
 * Date: 16/07/2021
 * Coms: x y z , r g b , etc.
 */

#pragma once

#include <memory>
#include "Vector3.h"
#include "Texture.h"
//#include "Texture.h"

const float fresnel_coef[] =
{
    1.00029,            //[0] = air
    1.0,                //[1] = void
    1.31,               //[2] = ice
    1.33,               //[3] = water
    1.52,               //[4] = cristal_1
    1.65,               //[5] = cristal_2
    2.417               //[6] = diamond
};

enum dielec_type{ air = 0, vacuum = 1, ice = 2, water = 3, cristal_1 = 4, cristal_2 = 5, diamond = 6 };
enum mat_type{emitting, diffuse, dif_spec, dif_spec_fresnel, perfect_spec, phong, dielectric, remix};

struct Material
{
    mat_type type = diffuse;
    float n_fresnel = fresnel_coef[air];
    Color k_d = Color{ 0, 0, 0};
    Color k_s = Color{ 0, 0, 0 };
    Color k_t = Color{ 0, 0, 0 };
    bool has_texture = false;
    std::shared_ptr<Texture> tex = nullptr;
    float mul = 1.0f;       //in case you want to increase emitted light artificially, here's a multiplier to do so
};

//Emitting
std::shared_ptr<Material> create_emitting_material(Color color);

std::shared_ptr<Material> create_emitting_material(std::shared_ptr<Texture> tex, const float& multiplier);

//Diffuse
std::shared_ptr<Material> create_diffuse_material(const Color& color);

std::shared_ptr<Material> create_diffuse_material(const std::shared_ptr<Texture> text);

//Plastics
std::shared_ptr<Material> create_plastic_material(const Color k_d, const Color k_s);

std::shared_ptr<Material> create_plastic_material(std::shared_ptr<Texture> text, const Color k_s);

//Plastics with fresnel
std::shared_ptr<Material> create_plastic_material_fresnel(const Color k_d);

std::shared_ptr<Material> create_plastic_material_fresnel(std::shared_ptr<Texture> text);

//Perfect specular
std::shared_ptr<Material> create_specular_material();

//Dielectrics
std::shared_ptr<Material> create_dielectric_material(const enum dielec_type& type);
