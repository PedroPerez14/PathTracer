/*
 * Author: Pedro Jos� P�rez Garc�a
 * Date: 16/07/2021
 * Coms: x y z , r g b , etc.
 */

#pragma once

#include <memory>
#include "Vector3.h"
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
    std::shared_ptr<Texture> tex;
    float mul = 1.0f;       //in case you want to increase emitted light artificially, here's a multiplier to do so
};

//Emitting
std::shared_ptr<Material> create_emitting_material(Color color)  //Non-textured
{
    return std::make_shared<Material>(emitting, fresnel_coef[cristal_1], color, color, color, false, nullptr, 1.0f);
}

std::shared_ptr<Material> create_emitting_material(std::shared_ptr<Texture> tex, const float& multiplier = 1.0f)  //Textured
{
    return std::make_shared<Material>(emitting, fresnel_coef[cristal_1], Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, true, tex, multiplier);
}

//Diffuse
std::shared_ptr<Material> create_diffuse_material(const Color& color)   //Non-textured
{
    return std::make_shared<Material>(diffuse, fresnel_coef[cristal_1], color, color, color, false, nullptr, 1.0f);
}

std::shared_ptr<Material> create_diffuse_material(const std::shared_ptr<Texture> text)   //Textured
{
    return std::make_shared<Material>(diffuse, fresnel_coef[cristal_1], Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, true, text, 1.0f);
}

//Plastics
std::shared_ptr<Material> create_plastic_material(const Color k_d, const Color k_s)   //Non-textured
{
    return std::make_shared<Material>(dif_spec, fresnel_coef[cristal_1], k_d, k_s, Color{ 0, 0, 0 }, false, nullptr, 1.0f);
}

std::shared_ptr<Material> create_plastic_material(std::shared_ptr<Texture> text, const Color k_s)   //Textured
{
    return std::make_shared<Material>(dif_spec, fresnel_coef[cristal_1], Color{ 0, 0, 0 }, k_s, Color{ 0, 0, 0 }, true, text, 1.0f);
}

//Plastics with fresnel
std::shared_ptr<Material> create_plastic_material_fresnel(const Color k_d)   //Non-textured
{
    return std::make_shared<Material>(dif_spec_fresnel, fresnel_coef[cristal_1], k_d, Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, false, nullptr, 1.0f);
}

std::shared_ptr<Material> create_plastic_material_fresnel(std::shared_ptr<Texture> text)   //Textured
{
    return std::make_shared<Material>(dif_spec_fresnel, fresnel_coef[cristal_1], Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, true, text, 1.0f);
}

//Perfect specular
std::shared_ptr<Material> create_specular_material()   //Non-textured
{
    return std::make_shared<Material>(perfect_spec, fresnel_coef[cristal_1], Color{ 0, 0, 0 }, Color{ 255.0f, 255.0f, 255.0f }, Color{ 0, 0, 0 }, false, nullptr, 1.0f);
}

//Dielectrics
std::shared_ptr<Material> create_dielectric_material(const dielec_type& type)
{
    //We don't need k_s nor k_t, since we'll calculate them through fresnel
    return std::make_shared<Material>(dielectric, type, Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, false, nullptr, 1.0f);
}
