/*
 * Author: Pedro José Pérez García
 * Date: 22/07/2021
 * Coms: Tengo que separar declaraciones e implementaciones
 */
#pragma once
#include "Material.h"

std::shared_ptr<Material> create_emitting_material(Color color)  //Non-textured
{
    Material mat{ emitting, fresnel_coef[cristal_1], color, color, color, false, nullptr, 1.0f };
    return std::make_shared<Material>(mat);
}

std::shared_ptr<Material> create_emitting_material(std::shared_ptr<Texture> tex, const float& multiplier = 1.0f)  //Textured
{
    Material mat{ emitting, fresnel_coef[cristal_1], Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, true, tex, multiplier };
    return std::make_shared<Material>(mat);
}

//Diffuse
std::shared_ptr<Material> create_diffuse_material(const Color& color)   //Non-textured
{
    Material mat{ diffuse, fresnel_coef[cristal_1], color, color, color, false, nullptr, 1.0f };
    return std::make_shared<Material>(mat);
}

std::shared_ptr<Material> create_diffuse_material(const std::shared_ptr<Texture> text)   //Textured
{
    Material mat{ diffuse, fresnel_coef[cristal_1], Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, true, text, 1.0f };
    return std::make_shared<Material>(mat);
}

//Plastics
std::shared_ptr<Material> create_plastic_material(const Color k_d, const Color k_s)   //Non-textured
{
    Material mat{ dif_spec, fresnel_coef[cristal_1], k_d, k_s, Color{ 0, 0, 0 }, false, nullptr, 1.0f };
    return std::make_shared<Material>(mat);
}

std::shared_ptr<Material> create_plastic_material(std::shared_ptr<Texture> text, const Color k_s)   //Textured
{
    Material mat{ dif_spec, fresnel_coef[cristal_1], Color{ 0, 0, 0 }, k_s, Color{ 0, 0, 0 }, true, text, 1.0f };
    return std::make_shared<Material>(mat);
}

//Plastics with fresnel
std::shared_ptr<Material> create_plastic_material_fresnel(const Color k_d)   //Non-textured
{
    Material mat{ dif_spec_fresnel, fresnel_coef[cristal_1], k_d, Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, false, nullptr, 1.0f };
    return std::make_shared<Material>(mat);
}

std::shared_ptr<Material> create_plastic_material_fresnel(std::shared_ptr<Texture> text)   //Textured
{
    Material mat{ dif_spec_fresnel, fresnel_coef[cristal_1], Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, true, text, 1.0f };
    return std::make_shared<Material>(mat);
}

//Perfect specular
std::shared_ptr<Material> create_specular_material()   //Non-textured
{
    Material mat{ perfect_spec, fresnel_coef[cristal_1], Color{ 0, 0, 0 }, Color{ 1.0f, 1.0f, 1.0f }, Color{ 0, 0, 0 }, false, nullptr, 1.0f };
    return std::make_shared<Material>(mat);
}

//Dielectrics
std::shared_ptr<Material> create_dielectric_material(const enum dielec_type& type)
{
    //We don't need k_s nor k_t, since we'll calculate them through fresnel
    Material mat{ dielectric, type, Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, Color{ 0, 0, 0 }, false, nullptr, 1.0f };
    return std::make_shared<Material>(mat);
}
