/*
 * Author: Pedro José Pérez García
 * Date: 20/07/2021
 * Coms: Escenas prefabricadas en funciones facilitas de llamar
 */

#pragma once
#include "../Tracer/PathTracer.h"
#include "../Geometry/Shape.h"
#include "../Geometry/Cylinder.h"
#include "../Geometry/Quad.h"
#include "../Geometry/Plane.h"
#include "../Geometry/Sphere.h"

void mario_cornell_box(PathTracer* im)
{
    im->set_fov(60.0f);
    ///Luces puntuales
    shared_ptr<PointLight> lp_amarilla(new PointLight{ Color{ 10.0f, 10.0f, 1.0f }, Vector3{ 60, -24.5, 24.5 } });  //POINT LIGHT
    shared_ptr<PointLight> lp_central(new PointLight{ Color{ 2.0f, 2.0f, 2.0f }, Color{ 75.0f, 0.0f, 0.0f } });     //POINT LIGHT
    shared_ptr<Texture> flag_tex = read_tex_from_file("../../../../PathTracer/Textures/mario_flag.ppm", 0, 8.0f, 0.0f, 8.0f);

    ///Textures

    ///Materials
    shared_ptr<Material> mat_pared_tex = create_diffuse_material(Color{ 0.8f, 0.8f, 0.8f });
    shared_ptr<Material> mat_pared_der = create_diffuse_material(Color{ 0.039f, 1.0f, 0.039f });
    shared_ptr<Material> mat_pared_izq = create_diffuse_material(Color{ 1.0f, 0.039f, 0.039f });
    shared_ptr<Material> mat_bandera = create_diffuse_material(Color{ 0.43f, 0.330f, 0.055f });
    shared_ptr<Material> mat_Sphere1_b = create_specular_material(); //Color(20, 20, 20)
    shared_ptr<Material> mat_techo_emisor = create_emitting_material(Color{ 1.0f, 1.0f, 1.0f });                            //AREA LIGHT
    shared_ptr<Material> mat_techo_oscuro = create_diffuse_material(Color{ 0.294f, 0.294f, 0.294f });
    shared_ptr<Material> flag_mat = create_diffuse_material(flag_tex);
    shared_ptr<Material> mat_amarillo_dif = create_diffuse_material(Color{ 0.784f, 0.705f, 0.078f });
    shared_ptr<Material> mat_Sphere3 = create_dielectric_material(cristal_1);
    shared_ptr<Material> mat_Cylinder = create_dielectric_material(cristal_1);

    shared_ptr<Material> mat_chicle = create_plastic_material(Color{ 1.0f, 0.450f, 0.862f }, Color{ 0.5f, 0.5f, 0.5f });
    shared_ptr<Material> mat_chicle_fresnel = create_plastic_material_fresnel(Color{ 1.0f, 0.450f, 0.862f });
    shared_ptr<Material> mat_chicle_semidif = create_plastic_material(Color{ 1.0f, 0.450f, 0.862f }, Color{ 0.039f, 0.039f, 0.039f });
    shared_ptr<Material> mat_chicle_dif = create_diffuse_material(Color{ 0.109f, 0.737f, 0.929f });
    shared_ptr<Material> mat_chicle_reflejo_azul = create_plastic_material(Color{ 1.0f, 0.450f, 0.862f }, Color{ 0.784f, 0.784f, 0.004f });


    ///Shapes
    //Cornell Box
    shared_ptr<Shape> pared(new Plane(Vector3{ 85, 0, 0 }, Vector3{ 0, -1, 0 }, Vector3{ 0, 0, 1 }, mat_pared_tex));
    shared_ptr<Shape> pared_izq(new Plane(Vector3{ 0, 0, -25 }, Vector3{ 1, 0, 0 }, Vector3{ 0, 1, 0 }, mat_pared_izq));
    shared_ptr<Shape> pared_der(new Plane(Vector3{ 0, 0, 25 }, Vector3{ -1, 0, 0 }, Vector3{ 0, 1, 0 }, mat_pared_der));
    shared_ptr<Shape> suelo(new Plane(Vector3{ 0, -25, 0 }, Vector3{ 0, 0, 1 }, Vector3{ 1, 0, 0 }, mat_pared_tex));
    shared_ptr<Shape> techo(new Plane(Vector3{ 0, 25.5, 0 }, Vector3{ -1, 0, 0 }, Vector3{ 0, 0, -1 }, mat_techo_emisor));
    shared_ptr<Shape> pared_detras(new Plane(Vector3{ -0.1f, 0, 0 }, Vector3{ 0, 0, 1 }, Vector3{ 0, -1, 0 }, mat_pared_tex));
    //Quads
    shared_ptr<Shape> techo_iz(new Quad(Vector3{ 85, 25, -25 }, Vector3{ 85, 25, -10 }, Vector3{ 0, 25, -25 }, Vector3{ 0, 25, -10 }, mat_pared_tex));
    shared_ptr<Shape> techo_der(new Quad(Vector3{ 85, 25, 10 }, Vector3{ 85, 25, 25 }, Vector3{ 0, 25, 10 }, Vector3{ 0, 25, 25 }, mat_pared_tex));
    shared_ptr<Shape> techo_cerca(new Quad(Vector3{ 15, 25, -10 }, Vector3{ 15, 25, 10 }, Vector3{ 0, 25, -10 }, Vector3{ 0, 25, 10 }, mat_pared_tex));
    shared_ptr<Shape> techo_fondo(new Quad(Vector3{ 85, 25, -10 }, Vector3{ 85, 25, 10 }, Vector3{ 70, 25, -10 }, Vector3{ 70, 25, 10 }, mat_pared_tex));
    shared_ptr<Shape> quad_bandera(new Quad(Vector3{ 65, 18, 16 }, Vector3{ 65, 18, 24 }, Vector3{ 65, 10, 16 }, Vector3{ 65, 10, 24 }, flag_mat));

    //Spheres
    shared_ptr<Shape> esf1(new Sphere(Vector3{ 60, 10, -15 }, 7.5, mat_chicle_semidif));
    shared_ptr<Shape> esf2(new Sphere(Vector3{ 60, 10, 0 }, 7.5, mat_chicle_dif));
    shared_ptr<Shape> esf3(new Sphere(Vector3{ 60, 10, 15 }, 7.5, mat_chicle_reflejo_azul));
    shared_ptr<Shape> esf4(new Sphere(Vector3{ 60, -5, -7.5 }, 7.5, mat_chicle));
    shared_ptr<Shape> esf5(new Sphere(Vector3{ 60, -5, 7.5 }, 7.5, mat_chicle_fresnel));
    shared_ptr<Shape> esf_meta(new Sphere(Vector3{ 65, 20, 15 }, 2.0f, mat_amarillo_dif));
    //Cylinder de prueba
    shared_ptr<Shape> cil1(new Cylinder(Vector3{ 65, -27, -17 }, Vector3{ 0.0f, 1.0f, 0.6f }, 5.0f, 11.0f, mat_pared_der));
    shared_ptr<Shape> cil2(new Cylinder(Vector3{ 65, -17, -11 }, Vector3{ 0.0f, 1.0f, 0.6f }, 6.0f, 2.5f, mat_pared_der));
    shared_ptr<Shape> cil3(new Cylinder(Vector3{ 65, -17, -11 }, Vector3{ 0.0f, 1.0f, 0.6f }, 4.5f, 2.51f, create_diffuse_material(Color{0.01f,0.01f,0.01f })));
    shared_ptr<Shape> cil4(new Cylinder(Vector3{ 65, -25, 15 }, Vector3{ 0.0f, 1.0f, 0.0f }, 8.0f, 4.0f, mat_bandera));
    shared_ptr<Shape> cil5(new Cylinder(Vector3{ 65, -25, 15 }, Vector3{ 0.0f, 1.0f, 0.0f }, 0.75f, 45.0f, mat_techo_oscuro));
    shared_ptr<Shape> cil6(new Cylinder(Vector3{ 80, 15, -7.5f }, Vector3{ 0.0f, 0.0f, 1.0f }, 5.0f, 15.0f, mat_chicle_dif));

    //shared_ptr<Shape> cil2(new Cylinder{ Vector3{ 65, -25.0, 0.5 }, Vector3{ 0.5f, 1.0f, 1.0f}, 5.0, 25.0f, mat_Sphere1 });

    ///Añadir Shapes a la escena
    //im->add_shape(esf1);
    //im->add_shape(esf2);
    //im->add_shape(esf3);
    //im->add_shape(esf4);
    //im->add_shape(esf5);
    im->add_shape(pared_izq);
    im->add_shape(pared_der);
    im->add_shape(pared);
    //im->add_shape(pared_detras);
    im->add_shape(suelo);
    im->add_shape(techo);
    
    im->add_shape(cil1);
    im->add_shape(cil2);
    im->add_shape(cil3);
    im->add_shape(cil4);
    im->add_shape(cil5);
    im->add_shape(cil6);

    //im->add_shape(techo_iz);
    //im->add_shape(techo_der);
    //im->add_shape(techo_fondo);
    //im->add_shape(techo_cerca);

    im->add_shape(esf_meta);
    im->add_shape(quad_bandera);

    ///Añadir luces puntuales a la escena
    im->add_point_light(lp_central);
    //im->add_point_light(lp_amarilla);
}

void white_cornell_box(PathTracer* im)
{
    im->set_fov(60.0f);
    ///Luces puntuales
    shared_ptr<PointLight> lp_amarilla(new PointLight{ Color{ 10.0f, 10.0f, 1.0f }, Vector3{ 60, -24.5, 24.5 } });         //POINT LIGHT
    shared_ptr<PointLight> lp_central(new PointLight{ Vector3{ 42.5, 15.0f, 0 }, Color{ 19.607f, 19.607f, 19.607f } });     //POINT LIGHT

    ///Textures

    ///Materials
    shared_ptr<Material> mat_pared_tex = create_diffuse_material(Color{ 0.8f, 0.8f, 0.8f });
    shared_ptr<Material> mat_pared_der = create_diffuse_material(Color{ 0.039f, 1.0f, 0.039f });
    shared_ptr<Material> mat_pared_izq = create_diffuse_material(Color{ 1.0f, 0.039f, 0.039f });
    shared_ptr<Material> mat_Sphere1 = create_diffuse_material(Color{ 0.784f, 0.490f, 0.490f });
    shared_ptr<Material> mat_Sphere1_b = create_specular_material(); //Color(20, 20, 20)
    shared_ptr<Material> mat_techo_emisor = create_emitting_material(Color{ 3.0f, 3.0f, 3.0f });                            //AREA LIGHT
    shared_ptr<Material> mat_techo_oscuro = create_diffuse_material(Color{ 0.294f, 0.294f, 0.294f });
    shared_ptr<Material> mat_amarillo_dif = create_diffuse_material(Color{ 0.784f, 0.705f, 0.078f });
    shared_ptr<Material> mat_Sphere3 = create_dielectric_material(cristal_1);
    shared_ptr<Material> mat_Cylinder = create_dielectric_material(cristal_1);

    shared_ptr<Material> mat_chicle = create_plastic_material(Color{ 1.0f, 0.450f, 0.862f }, Color{ 0.5f, 0.5f, 0.5f });
    shared_ptr<Material> mat_chicle_fresnel = create_plastic_material_fresnel(Color{ 1.0f, 0.450f, 0.862f });
    shared_ptr<Material> mat_chicle_semidif = create_plastic_material(Color{ 1.0f, 0.450f, 0.862f }, Color{ 0.039f, 0.039f, 0.039f });
    shared_ptr<Material> mat_chicle_dif = create_diffuse_material(Color{ 1.0f, 0.450f, 0.862f });
    shared_ptr<Material> mat_chicle_reflejo_azul = create_plastic_material(Color{ 1.0f, 0.450f, 0.862f }, Color{ 0.784f, 0.784f, 0.004f });

    ///Shapes
    //Cornell Box
    shared_ptr<Shape> pared(new Plane(Vector3{ 85, 0, 0 }, Vector3{ 0, -1, 0 }, Vector3{ 0, 0, 1 }, mat_pared_tex));
    shared_ptr<Shape> pared_izq(new Plane(Vector3{ 0, 0, -25 }, Vector3{ 1, 0, 0 }, Vector3{ 0, 1, 0 }, mat_pared_izq));
    shared_ptr<Shape> pared_der(new Plane(Vector3{ 0, 0, 25 }, Vector3{ -1, 0, 0 }, Vector3{0, 1, 0}, mat_pared_der));
    shared_ptr<Shape> suelo(new Plane(Vector3{ 0, -25, 0 }, Vector3{ 0, 0, 1 }, Vector3{1, 0, 0}, mat_pared_tex));
    shared_ptr<Shape> techo(new Plane(Vector3{ 0, 25.5, 0 }, Vector3{ -1, 0, 0 }, Vector3{ 0, 0, -1 }, mat_techo_emisor));
    shared_ptr<Shape> pared_detras(new Plane(Vector3{ -0.1f, 0, 0 }, Vector3{0, 0, 1}, Vector3{0, -1, 0}, mat_pared_tex));
    //Quads
    shared_ptr<Shape> techo_iz(new Quad(Vector3{ 85, 25, -25 }, Vector3{ 85, 25, -10 }, Vector3{ 0, 25, -25 }, Vector3{ 0, 25, -10 }, mat_pared_tex));
    shared_ptr<Shape> techo_der(new Quad(Vector3{ 85, 25, 10 }, Vector3{ 85, 25, 25 }, Vector3{ 0, 25, 10 }, Vector3{ 0, 25, 25 }, mat_pared_tex));
    shared_ptr<Shape> techo_cerca(new Quad(Vector3{ 15, 25, -10 }, Vector3{ 15, 25, 10 }, Vector3{ 0, 25, -10 }, Vector3{ 0, 25, 10 }, mat_pared_tex));
    shared_ptr<Shape> techo_fondo(new Quad(Vector3{ 85, 25, -10 }, Vector3{ 85, 25, 10 }, Vector3{ 70, 25, -10 }, Vector3{ 70, 25, 10 }, mat_pared_tex));
    //Spheres
    shared_ptr<Shape> esf1(new Sphere(Vector3{ 60, 10, -15 }, 7.5, mat_chicle_semidif));
    shared_ptr<Shape> esf2(new Sphere(Vector3{ 60, 10, 0 }, 7.5, mat_chicle_dif));
    shared_ptr<Shape> esf3(new Sphere(Vector3{ 60, 10, 15 }, 7.5, mat_chicle_reflejo_azul));
    shared_ptr<Shape> esf4(new Sphere(Vector3{ 60, -5, -7.5 }, 7.5, mat_chicle));
    shared_ptr<Shape> esf5(new Sphere(Vector3{ 60, -5, 7.5 }, 7.5, mat_chicle_fresnel));
    //Cylinder de prueba
    shared_ptr<Shape> cil_finito(new Cylinder(Vector3{ 50, -25, -20 }, Vector3{ 0, 1, 0 }, 7.5, 50.0f, mat_Cylinder));

    shared_ptr<Shape> cil1(new Cylinder( Vector3{ 65, -25, 0 }, Vector3{ 0.0f, 1.0f, 0.0f }, 15.0f, 6.0f, mat_Sphere3 ) );
    shared_ptr<Shape> cil2(new Cylinder{ Vector3{ 65, -25.0, 0.5 }, Vector3{ 0.5f, 1.0f, 1.0f}, 5.0, 25.0f, mat_Sphere1 });

    ///Añadir Shapes a la escena
    //im->add_shape(esf1);
    //im->add_shape(esf2);
    //im->add_shape(esf3);
    //im->add_shape(esf4);
    //im->add_shape(esf5);
    im->add_shape(pared_izq);
    im->add_shape(pared_der);
    im->add_shape(pared);
    im->add_shape(pared_detras);
    im->add_shape(suelo);
    im->add_shape(techo);
    im->add_shape(techo_iz);
    im->add_shape(techo_der);
    im->add_shape(techo_fondo);
    im->add_shape(techo_cerca);
    im->add_shape(cil_finito);

    im->add_shape(cil1);
    im->add_shape(cil2);

    ///Añadir luces puntuales a la escena
    //im->add_point_light(lp_central);
    //im->add_point_light(lp_amarilla);
}

void standard_cornell_box(PathTracer* im)
{
    im->set_fov(60.0f);
    shared_ptr<Texture> pared_doom = read_tex_from_file("../../../../PathTracer/Textures/pared_doom.ppm", 0.0f, 63.0f, 0.0f, 63.0f);
    shared_ptr<Material> mat_pared_doom = create_emitting_material(pared_doom, 0.75f);

    ///Luces puntuales
    shared_ptr<PointLight> lp_amarilla(new PointLight{ Color{ 10.0f, 10.0f, 1.0f }, Vector3{ 60, -24.5, 24.5 } });         //POINT LIGHT
    shared_ptr<PointLight> lp_central(new PointLight{ Vector3{ 42.5, 15.0f, 0 }, Color{ 19.607f, 19.607f, 19.607f } });     //POINT LIGHT

    ///Textures

    ///Materials
    shared_ptr<Material> mat_pared_tex = create_diffuse_material(Color{ 0.8f, 0.8f, 0.8f });
    shared_ptr<Material> mat_pared_der = create_diffuse_material(Color{ 0.039f, 1.0f, 0.039f });
    shared_ptr<Material> mat_pared_izq = create_diffuse_material(Color{ 1.0f, 0.039f, 0.039f });
    shared_ptr<Material> mat_mirror = create_specular_material(); //Color(20, 20, 20)
    shared_ptr<Material> mat_techo_emisor = create_emitting_material(Color{ 2.0f, 2.0f, 2.0f });                            //AREA LIGHT
    shared_ptr<Material> mat_techo_oscuro = create_diffuse_material(Color{ 0.294f, 0.294f, 0.294f });
    shared_ptr<Material> mat_amarillo_dif = create_diffuse_material(Color{ 0.784f, 0.705f, 0.078f });
    shared_ptr<Material> mat_cristal = create_dielectric_material(cristal_1);
    shared_ptr<Material> mat_chicle_fresnel = create_plastic_material_fresnel(Color{ 1.0f, 0.450f, 0.862f });

    shared_ptr<Material> mirror_magenta = create_plastic_material(Color{ 0.25f, 0.0f, 0.25f }, Color{ 0.75f, 0.0f, 0.75f });
    shared_ptr<Material> mirror_yellow = create_plastic_material(Color{ 0.25f, 0.25f, 0.0f }, Color{0.75f, 0.75f, 0.0f});
    shared_ptr<Material> mirror_cyan = create_plastic_material(Color{ 0.0f, 0.25f, 0.25f }, Color{ 0.0f, 0.75f, 0.75f });


    ///Shapes
    //Cornell Box
    shared_ptr<Shape> pared(new Plane(Vector3{ 85, 0, 0 }, Vector3{ 0, 0, 1 }, Vector3{ 0, 1, 0 }, mat_pared_tex));
    shared_ptr<Shape> pared_detras(new Plane(Vector3{ -0.1f, 0, 0 }, Vector3{ 0, 0, 1 }, Vector3{ 0, -1, 0 }, mat_pared_tex));
    shared_ptr<Shape> pared_izq(new Plane(Vector3{ 0, 0, -25 }, Vector3{ 1, 0, 0 }, Vector3{ 0, 1, 0 }, mat_pared_tex));
    shared_ptr<Shape> pared_der(new Plane(Vector3{ 0, 0, 25 }, Vector3{ -1, 0, 0 }, Vector3{ 0, 1, 0 }, mat_pared_tex));
    shared_ptr<Shape> suelo(new Plane(Vector3{ 0, -25, 0 }, Vector3{ 0, 0, 1 }, Vector3{ 1, 0, 0 }, mat_pared_tex));
    shared_ptr<Shape> techo(new Plane(Vector3{ 0, 25.5, 0 }, Vector3{ -1, 0, 0 }, Vector3{ 0, 0, -1 }, mat_pared_tex));

    //Quads
    shared_ptr<Shape> techo_iz(new Quad(Vector3{ 85, 25, -25 }, Vector3{ 85, 25, -10 }, Vector3{ 0, 25, -25 }, Vector3{ 0, 25, -10 }, mat_pared_tex));
    shared_ptr<Shape> techo_der(new Quad(Vector3{ 85, 25, 10 }, Vector3{ 85, 25, 25 }, Vector3{ 0, 25, 10 }, Vector3{ 0, 25, 25 }, mat_techo_emisor));
    shared_ptr<Shape> techo_cerca(new Quad(Vector3{ 15, 25, -10 }, Vector3{ 15, 25, 10 }, Vector3{ 0, 25, -10 }, Vector3{ 0, 25, 10 }, mat_pared_tex));
    shared_ptr<Shape> techo_fondo(new Quad(Vector3{ 85, 25, -10 }, Vector3{ 85, 25, 10 }, Vector3{ 70, 25, -10 }, Vector3{ 70, 25, 10 }, mat_pared_tex));

    shared_ptr<Shape> quad(new Quad(Vector3{ 85, -15, 25 }, Vector3{ 85, -25, 10 }, Vector3{ 0, -15, 25 }, Vector3{ 0, -25, 10 }, mirror_magenta));
    shared_ptr<Shape> quad2(new Quad(Vector3{ 85, -25, -10 }, Vector3{ 85, -15, -25 }, Vector3{ 0, -25, -10 }, Vector3{ 0, -15, -25 }, mirror_yellow));
    shared_ptr<Shape> quad3(new Quad(Vector3{ 85, 10, -25 }, Vector3{ 85, 25, -10 }, Vector3{ 0, 10, -25 }, Vector3{ 0, 25, -10 }, mirror_cyan));
    shared_ptr<Shape> quad4(new Quad(Vector3{ 84.9f, 25, -25 }, Vector3{ 84.9f, 25, 0 }, Vector3{ 84.9f, 0, -25 }, Vector3{ 84.9f, 0, 0 }, mat_mirror));
    shared_ptr<Shape> quad5(new Quad(Vector3{ 84.9f, 0, 0 }, Vector3{ 84.9f, 0, 25 }, Vector3{ 84.9f, -25, 0 }, Vector3{ 84.9f, -25, 25 }, mat_mirror));


    //Spheres
    shared_ptr<Shape> esf1(new Sphere(Vector3{ 60, 10, -15 }, 7.5, mat_mirror));
    shared_ptr<Shape> esf2(new Sphere(Vector3{ 60, -15.0f, 0 }, 10.0f, mat_cristal));

    //Cylinder de prueba
    shared_ptr<Shape> cil_finito(new Cylinder(Vector3{ 50, -25, -20 }, Vector3{ 0, 1, 0 }, 7.5, 50.0, mat_cristal));

    shared_ptr<Shape> cil1(new Cylinder(Vector3{ 65, -25, 0 }, Vector3{ 0.0f, 1.0f, 0.0f }, 15.0f, 6.0f, mat_cristal));
    shared_ptr<Shape> cil2(new Cylinder{ Vector3{ 65, -25.0, 0.5 }, Vector3{ 0.5f, 1.0f, 1.0f}, 5.0, 25.0f, mat_amarillo_dif });

    ///Añadir Shapes a la escena
    //im->add_shape(esf1);
    //im->add_shape(esf2);

    im->add_shape(pared_izq);
    im->add_shape(pared_der);
    im->add_shape(pared);
    im->add_shape(pared_detras);
    im->add_shape(suelo);
    im->add_shape(techo);
    im->add_shape(techo_iz);
    im->add_shape(techo_der);
    im->add_shape(techo_fondo);
    im->add_shape(techo_cerca);

    im->add_shape(quad);
    im->add_shape(quad2);
    im->add_shape(quad3);
    im->add_shape(quad4);
    im->add_shape(quad5);

    //im->add_shape(cil_finito);
    //im->add_shape(cil1);
    //im->add_shape(cil2);

    ///Añadir luces puntuales a la escena
    //im->add_point_light(lp_central);
    //im->add_point_light(lp_amarilla);
}

void doom_cornell_box(PathTracer* im)
{
    im->set_fov(45.0f);
    ///Luces puntuales
    shared_ptr<PointLight> lp_amarilla(new PointLight{ Vector3{ 60, -24.5, 24.5 }, Color{ 1.0f, 1.0f, 1.0f } });                 //POINT LIGHT
    shared_ptr<PointLight> lp_central(new PointLight{ Color{ 1.0f, 1.0, 1.0 },  Vector3{ 268.0f, 30.0f, 0.0f } });               //POINT LIGHT

    ///Textures
    shared_ptr<Texture> comp_doom = read_tex_from_file("../../../../PathTracer/Textures/comp_doom.ppm", -25.0f, 25.0f, 25.5f, -25.0f);
    shared_ptr<Texture> columna_doom = read_tex_from_file("../../../../PathTracer/Textures/columna_doom.ppm", -25.0f, 25.0f, 25.5f, -25.0f);
    shared_ptr<Texture> pared_doom = read_tex_from_file("../../../../PathTracer/Textures/pared_doom.ppm", -25.0f, 25.0f, 25.5f, -25.0f);
    shared_ptr<Texture> suelo_doom = read_tex_from_file("../../../../PathTracer/Textures/suelo_doom.ppm", -25.0f, 25.0f, 25.5f, -25.0f);
    shared_ptr<Texture> techo_doom = read_tex_from_file("../../../../PathTracer/Textures/techo_doom.ppm", -25.0f, 25.0f, 25.5f, -25.0f);
    shared_ptr<Texture> blue_flat_doom = read_tex_from_file("../../../../PathTracer/Textures/flat_blue.ppm", 0.0f, 63.0f, 0.0f, 63.0f);
    shared_ptr<Texture> cucuesquela_tex = read_tex_from_file("../../../../PathTracer/Textures/cucuesquela.ppm", -25.0f, 25.0f, 25.5f, -25.0f);
    shared_ptr<Texture> earth_tex = read_tex_from_file("../../../../PathTracer/Textures/Tierra_Tex.ppm", -M_PI, M_PI, 0, M_PI);
    shared_ptr<Texture> cacodemon_tex = read_tex_from_file("../../../../PathTracer/Textures/cc.ppm", -M_PI, M_PI, 0, M_PI);
    shared_ptr<Texture> earth_wall = read_tex_from_file("../../../../PathTracer/Textures/Tierra_Tex.ppm", -63.0f, 63.0f, -63.0f, 63.0f);
    
    ///Materials
    shared_ptr<Material> mat_comp_doom = create_diffuse_material(comp_doom);
    shared_ptr<Material> mat_pared_doom = create_emitting_material(pared_doom, 0.8f);
    shared_ptr<Material> mat_columna_doom = create_diffuse_material(columna_doom);
    shared_ptr<Material> mat_suelo_doom = create_diffuse_material(blue_flat_doom);
    shared_ptr<Material> mat_suelo_doom2 = create_diffuse_material(suelo_doom);
    shared_ptr<Material> mat_techo_doom = create_diffuse_material(techo_doom);
    shared_ptr<Material> mat_cucuesquela = create_diffuse_material(cucuesquela_tex);
    shared_ptr<Material> mat_earth = create_diffuse_material(earth_tex);
    shared_ptr<Material> mat_cacodemon = create_diffuse_material(cacodemon_tex);
    shared_ptr<Material> mat_earth_wall = create_diffuse_material(earth_wall);

    shared_ptr<Material> mat_pared_tex = create_diffuse_material(Color{ 0.8f, 0.8f, 0.8f });
    shared_ptr<Material> mat_pared_der = create_diffuse_material(Color{ 0.039f, 1.0f, 0.039f });
    shared_ptr<Material> mat_pared_izq = create_diffuse_material(Color{ 1.0f, 0.039f, 0.039f });
    shared_ptr<Material> mat_Sphere1 = create_diffuse_material(Color{ 0.784f, 0.490f, 0.490f });
    shared_ptr<Material> mat_Sphere1_b = create_specular_material(); //Color(20, 20, 20)
    shared_ptr<Material> mat_techo_emisor = create_emitting_material(Color{ 1.75f, 1.75f, 1.0f });                            //AREA LIGHT
    shared_ptr<Material> mat_techo_oscuro = create_diffuse_material(Color{ 0.294f, 0.294f, 0.294f });
    shared_ptr<Material> mat_amarillo_dif = create_diffuse_material(Color{ 0.784f, 0.705f, 0.078f });
    shared_ptr<Material> mat_Sphere3 = create_dielectric_material(cristal_1);
    shared_ptr<Material> mat_Cylinder = create_dielectric_material(cristal_1);

    shared_ptr<Material> mat_chicle = create_plastic_material(Color{ 1.0f, 0.450f, 0.862f }, Color{ 0.5f, 0.5f, 0.5f });
    shared_ptr<Material> mat_chicle_fresnel = create_plastic_material_fresnel(Color{ 1.0f, 0.450f, 0.862f });
    shared_ptr<Material> mat_chicle_semidif = create_plastic_material(Color{ 1.0f, 0.450f, 0.862f }, Color{ 0.039f, 0.039f, 0.039f });
    shared_ptr<Material> mat_chicle_dif = create_diffuse_material(Color{ 1.0f, 0.450f, 0.862f });
    shared_ptr<Material> mat_chicle_reflejo_azul = create_plastic_material(Color{ 1.0f, 0.450f, 0.862f }, Color{ 0.784f, 0.784f, 0.004f });

    ///Shapes
    //Cornell Box
    shared_ptr<Shape> pared(new Plane(Vector3{ 868, 0, 0 }, Vector3{ 0, 0, 1 }, Vector3{ 0, 1, 0 }, mat_pared_doom));
    shared_ptr<Shape> pared_izq(new Plane(Vector3{ 0, 0, -320 }, Vector3{ 0, 1, 0 }, Vector3{ 1, 0, 0 }, mat_pared_doom, true));
    shared_ptr<Shape> pared_der(new Plane(Vector3{ 0, 0, 320 }, Vector3{ -1, 0, 0 }, Vector3{ 0, 1, 0 }, mat_pared_doom));
    shared_ptr<Shape> suelo(new Plane(Vector3{ 0, -51, 0 }, Vector3{ 0, 0, 1 }, Vector3{ 1, 0, 0 }, mat_suelo_doom));
    shared_ptr<Shape> techo(new Plane(Vector3{ 0, 165.0f, 0 }, Vector3{ -1, 0, 0 }, Vector3{ 0, 0, -1 }, mat_techo_emisor));
    shared_ptr<Shape> pared_detras(new Plane(Vector3{ -1.0f, 0, 0 }, Vector3{ 0, 0, 1 }, Vector3{ 0, -1, 0 }, mat_pared_doom));
    
    //Quads
    shared_ptr<Shape> luz_area_ventana_der(new Quad(Vector3{ 500.0f, 155.0f, 319.5f }, Vector3{ 300.0f, 155.0f, 319.5f }, Vector3{ 500.0f, -30.0f, 319.5f }, Vector3{ 300.0f, -30.0f, 319.5f }, mat_techo_emisor));    //AREA LIGHT
    shared_ptr<Shape> pared_fondo_izq(new Quad(Vector3{ 708, 31, -320 }, Vector3{ 708, 31, -192 }, Vector3{ 708, -41, -320 }, Vector3{ 708, -41, -192 }, mat_pared_doom));
    shared_ptr<Shape> pared_fondo_diag(new Quad(Vector3{ 708, 31, -192 }, Vector3{ 868, 31, -56 }, Vector3{ 708, -41, -192 }, Vector3{ 868, -41, -56 }, mat_pared_doom));
    shared_ptr<Shape> techo_cerca_doom(new Quad(Vector3{ 268, 30.9f, -320 }, Vector3{ 268, 30.9f, 320 }, Vector3{ -1, 30.9f, -320 }, Vector3{ -1, 30.9f, 320 }, mat_techo_doom, true));
    shared_ptr<Shape> suelo_cerca_doom(new Quad(Vector3{ 268, -41.0f, -320 }, Vector3{ 268, -41.0f, 320 }, Vector3{ -1, -41.0f, -320 }, Vector3{ -1, -41.0f, 320 }, mat_suelo_doom2));
    shared_ptr<Shape> suelo_izq_doom(new Quad(Vector3{ 708.0f, -41.0f, -320.0f }, Vector3{ 708.0f, -41.0f, -128.0f }, Vector3{ 268, -41.0f, -320 }, Vector3{ 268, -41.0f, -128 }, mat_suelo_doom2));
    shared_ptr<Shape> suelo_fondo_doom(new Quad(Vector3{ 868.0f, -41.0f, -128.0f }, Vector3{ 868.0f, -41.0f, 320.0f }, Vector3{ 556.0f, -41.0f, -128.0f }, Vector3{ 556.0f, -41.0f, 320.0f }, mat_suelo_doom2));
    shared_ptr<Shape> techo_izq_doom(new Quad(Vector3{ 708.0f, 31.0f, -320.0f }, Vector3{ 708.0f, 31.0f, -128.0f }, Vector3{ 268, 31.0f, -320 }, Vector3{ 268, 31.0f, -128 }, mat_techo_doom, true));
    shared_ptr<Shape> techo_fondo_doom(new Quad(Vector3{ 868.0f, 31.0f, -128.0f }, Vector3{ 868.0f, 31.0f, 320.0f }, Vector3{ 556.0f, 31.0f, -128.0f }, Vector3{ 556.0f, 31.0f, 320.0f }, mat_techo_doom, true));
    shared_ptr<Shape> suelo_aux_doom(new Quad(Vector3{ 868.0f, -41.0f, -320.0f }, Vector3{ 868.0f, -41.0f, -128.0f }, Vector3{ 708.0f, -41.0f, -320.0f }, Vector3{ 708.0f, -41.0f, -128.0f }, mat_suelo_doom2));
    shared_ptr<Shape> techo_aux_doom(new Quad(Vector3{ 868.0f, 31.0f, -320.0f }, Vector3{ 868.0f, 31.0f, -128.0f }, Vector3{ 708.0f, 31.0f, -320.0f }, Vector3{ 708.0f, 31.0f, -128.0f }, mat_techo_doom, true));

    shared_ptr<Shape> col_cerca_iz_1(new Quad(Vector3{ 268.0f, 165.0f, -128.0f }, Vector3{ 268.0f, 165.0f, -96.0f }, Vector3{ 268.0f, -51.0f, -128.0f }, Vector3{ 268.0f, -51.0f, -96.0f }, mat_columna_doom));
    shared_ptr<Shape> col_cerca_iz_2(new Quad(Vector3{ 268.0f, 165.0f, -128.0f }, Vector3{ 300.0f, 165.0f, -128.0f }, Vector3{ 268.0f, -51.0f, -128.0f }, Vector3{ 300.0f, -51.0f, -128.0f }, mat_columna_doom));
    shared_ptr<Shape> col_cerca_iz_3(new Quad(Vector3{ 300.0f, 165.0f, -96.0f }, Vector3{ 300.0f, 165.0f, -128.0f }, Vector3{ 300.0f, -51.0f, -96.0f }, Vector3{ 300.0f, -51.0f, -128.0f }, mat_columna_doom));
    shared_ptr<Shape> col_cerca_iz_4(new Quad(Vector3{ 268.0f, 165.0f, -96.0f }, Vector3{ 300.0f, 165.0f, -96.0f }, Vector3{ 268.0f, -51.0f, -96.0f }, Vector3{ 300.0f, -51.0f, -96.0f }, mat_columna_doom));

    shared_ptr<Shape> col_lejos_iz_1(new Quad(Vector3{ 524.0f, 165.0f, -128.0f }, Vector3{ 524.0f, 165.0f, -96.0f }, Vector3{ 524.0f, -51.0f, -128.0f }, Vector3{ 524.0f, -51.0f, -96.0f }, mat_columna_doom));
    shared_ptr<Shape> col_lejos_iz_2(new Quad(Vector3{ 524.0f, 165.0f, -128.0f }, Vector3{ 556.0f, 165.0f, -128.0f }, Vector3{ 524.0f, -51.0f, -128.0f }, Vector3{ 556.0f, -51.0f, -128.0f }, mat_columna_doom));
    shared_ptr<Shape> col_lejos_iz_3(new Quad(Vector3{ 556.0f, 165.0f, -96.0f }, Vector3{ 556.0f, 165.0f, -128.0f }, Vector3{ 556.0f, -51.0f, -96.0f }, Vector3{ 556.0f, -51.0f, -128.0f }, mat_columna_doom));
    shared_ptr<Shape> col_lejos_iz_4(new Quad(Vector3{ 524.0f, 165.0f, -96.0f }, Vector3{ 556.0f, 165.0f, -96.0f }, Vector3{ 524.0f, -51.0f, -96.0f }, Vector3{ 556.0f, -51.0f, -96.0f }, mat_columna_doom));

    shared_ptr<Shape> col_cerca_der_1(new Quad(Vector3{ 268.0f, 165.0f, 128.0f }, Vector3{ 268.0f, 165.0f, 160.0f }, Vector3{ 268.0f, -51.0f, 128.0f }, Vector3{ 268.0f, -51.0f, 160.0f }, mat_columna_doom));
    shared_ptr<Shape> col_cerca_der_2(new Quad(Vector3{ 268.0f, 165.0f, 128.0f }, Vector3{ 300.0f, 165.0f, 128.0f }, Vector3{ 268.0f, -51.0f, 128.0f }, Vector3{ 300.0f, -51.0f, 128.0f }, mat_columna_doom));
    shared_ptr<Shape> col_cerca_der_3(new Quad(Vector3{ 300.0f, 165.0f, 160.0f }, Vector3{ 300.0f, 165.0f, 128.0f }, Vector3{ 300.0f, -51.0f, 160.0f }, Vector3{ 300.0f, -51.0f, 128.0f }, mat_columna_doom));
    shared_ptr<Shape> col_cerca_der_4(new Quad(Vector3{ 268.0f, 165.0f, 160.0f }, Vector3{ 300.0f, 165.0f, 160.0f }, Vector3{ 268.0f, -51.0f, 160.0f }, Vector3{ 300.0f, -51.0f, 160.0f }, mat_columna_doom));

    shared_ptr<Shape> col_lejos_der_1(new Quad(Vector3{ 524.0f, 165.0f, 128.0f }, Vector3{ 524.0f, 165.0f, 160.0f }, Vector3{ 524.0f, -51.0f, 128.0f }, Vector3{ 524.0f, -51.0f, 160.0f }, mat_columna_doom));
    shared_ptr<Shape> col_lejos_der_2(new Quad(Vector3{ 524.0f, 165.0f, 128.0f }, Vector3{ 556.0f, 165.0f, 128.0f }, Vector3{ 524.0f, -51.0f, 128.0f }, Vector3{ 556.0f, -51.0f, 128.0f }, mat_columna_doom));
    shared_ptr<Shape> col_lejos_der_3(new Quad(Vector3{ 556.0f, 165.0f, 160.0f }, Vector3{ 556.0f, 165.0f, 128.0f }, Vector3{ 556.0f, -51.0f, 160.0f }, Vector3{ 556.0f, -51.0f, 128.0f }, mat_columna_doom));
    shared_ptr<Shape> col_lejos_der_4(new Quad(Vector3{ 524.0f, 165.0f, 160.0f }, Vector3{ 556.0f, 165.0f, 160.0f }, Vector3{ 524.0f, -51.0f, 160.0f }, Vector3{ 556.0f, -51.0f, 160.0f }, mat_columna_doom));

    shared_ptr<Shape> pared1_escalon_iz(new Quad(Vector3{ 300.0f, -41.0f, -128.0f }, Vector3{ 524.0f, -41.0f, -128.0f }, Vector3{ 300.0f, -46.0f, -128.0f }, Vector3{ 524.0f, -46.0f, -128.0f }, mat_columna_doom));
    shared_ptr<Shape> suelo_escalon_iz(new Quad(Vector3{ 524.0f, -46.0f, -128.0f }, Vector3{ 524.0f, -46.0f, -96.0f }, Vector3{ 300.0f, -46.0f, -128.0f }, Vector3{ 300.0f, -46.0f, -96.0f }, mat_suelo_doom));
    shared_ptr<Shape> pared2_escalon_iz(new Quad(Vector3{ 300.0f, -46.0f, -96.0f }, Vector3{ 524.0f, -46.0f, -96.0f }, Vector3{ 300.0f, -51.0f, -96.0f }, Vector3{ 524.0f, -51.0f, -96.0f }, mat_columna_doom));

    shared_ptr<Shape> pared1_escalon_lejos(new Quad(Vector3{ 556.0f, -41.0f, -96.0f }, Vector3{ 556.0f, -41.0f, 128.0f }, Vector3{ 556.0f, -46.0f, -96.0f }, Vector3{ 556.0f, -46.0f, 128.0f }, mat_columna_doom));
    shared_ptr<Shape> suelo_escalon_lejos(new Quad(Vector3{ 556.0f, -46.0f, -96.0f }, Vector3{ 556.0f, -46.0f, 128.0f }, Vector3{ 524.0f, -46.0f, -96.0f }, Vector3{ 524.0f, -46.0f, 128.0f }, mat_suelo_doom));
    shared_ptr<Shape> pared2_escalon_lejos(new Quad(Vector3{ 524.0f, -46.0f, -96.0f }, Vector3{ 524.0f, -46.0f, 128.0f }, Vector3{ 524.0f, -51.0f, -96.0f }, Vector3{ 524.0f, -51.0f, 128.0f }, mat_columna_doom));

    shared_ptr<Shape> pared1_escalon_cerca(new Quad(Vector3{ 268.0f, -41.0f, 128.0f }, Vector3{ 268.0f, -41.0f, -96.0f }, Vector3{ 268.0f, -46.0f, 128.0f }, Vector3{ 268.0f, -46.0f, -96.0f }, mat_columna_doom));
    shared_ptr<Shape> suelo_escalon_cerca(new Quad(Vector3{ 300.0f, -46.0f, -96.0f }, Vector3{ 300.0f, -46.0f, 128.0f }, Vector3{ 268.0f, -46.0f, -96.0f }, Vector3{ 268.0f, -46.0f, 128.0f }, mat_suelo_doom));
    shared_ptr<Shape> pared2_escalon_cerca(new Quad(Vector3{ 300.0f, -46.0f, 128.0f }, Vector3{ 300.0f, -46.0f, -96.0f }, Vector3{ 300.0f, -51.0f, 128.0f }, Vector3{ 300.0f, -51.0f, -96.0f }, mat_columna_doom));

    shared_ptr<Shape> suelo_der_lejos(new Quad(Vector3{ 556.0f, -41.0f, 160.0f }, Vector3{ 556.0f, -41.0f, 320.0f }, Vector3{ 524.0f, -41.0f, 160.0f }, Vector3{ 524.0f, -41.0f, 320.0f }, mat_suelo_doom2));
    shared_ptr<Shape> techo_der_lejos(new Quad(Vector3{ 556.0f, 31.0f, 160.0f }, Vector3{ 556.0f, 31.0f, 320.0f }, Vector3{ 524.0f, 31.0f, 160.0f }, Vector3{ 524.0f, 31.0f, 320.0f }, mat_techo_doom, true));
    shared_ptr<Shape> pared_suelo_lejos(new Quad(Vector3{ 524.0f, -41.0f, 160.0f }, Vector3{ 524.0f, -41.0f, 320.0f }, Vector3{ 524.0f, -51.0f, 160.0f }, Vector3{ 524.0f, -51.0f, 320.0f }, mat_columna_doom));
    shared_ptr<Shape> suelo_der_cerca(new Quad(Vector3{ 300.0f, -41.0f, 160.0f }, Vector3{ 300.0f, -41.0f, 320.0f }, Vector3{ 268.0f, -41.0f, 160.0f }, Vector3{ 268.0f, -41.0f, 320.0f }, mat_suelo_doom2));
    shared_ptr<Shape> techo_der_cerca(new Quad(Vector3{ 300.0f, 31.0f, 160.0f }, Vector3{ 300.0f, 31.0f, 320.0f }, Vector3{ 268.0f, 31.0f, 160.0f }, Vector3{ 268.0f, 31.0f, 320.0f }, mat_techo_doom, true));
    shared_ptr<Shape> pared_suelo_cerca(new Quad(Vector3{ 300.0f, -41.0f, 320.0f }, Vector3{ 300.0f, -41.0f, 160.0f }, Vector3{ 300.0f, -51.0f, 320.0f }, Vector3{ 300.0f, -51.0f, 160.0f }, mat_columna_doom));

    shared_ptr<Shape> pared_techo_iz(new Quad(Vector3{ 300.0f, 165.0f, -128.0f }, Vector3{ 524.0f, 165.0f, -128.0f }, Vector3{ 300.0f, 31.0f, -128.0f }, Vector3{ 524.0f, 31.0f, -128.0f }, mat_comp_doom));
    shared_ptr<Shape> pared_techo_lejos(new Quad(Vector3{ 556.0f, 165.0f, -96.0f }, Vector3{ 556.0f, 165.0f, 128.0f }, Vector3{ 556.0f, 31.0f, -96.0f }, Vector3{ 556.0f, 31.0f, 128.0f }, mat_comp_doom));
    shared_ptr<Shape> pared_techo_cerca(new Quad(Vector3{ 268.0f, 165.0f, 128.0f }, Vector3{ 268.0f, 165.0f, -96.0f }, Vector3{ 268.0f, 31.0f, 128.0f }, Vector3{ 268.0f, 31.0f, -96.0f }, mat_comp_doom));
    shared_ptr<Shape> pared_techo_lejos_der(new Quad(Vector3{ 524.0f, 165.0f, 160.0f }, Vector3{ 524.0f, 165.0f, 320.0f }, Vector3{ 524.0f, 31.0f, 160.0f }, Vector3{ 524.0f, 31.0f, 320.0f }, mat_comp_doom));
    shared_ptr<Shape> pared_techo_cerca_der(new Quad(Vector3{ 300.0f, 165.0f, 320.0f }, Vector3{ 300.0f, 165.0f, 160.0f }, Vector3{ 300.0f, 31.0f, 320.0f }, Vector3{ 300.0f, 31.0f, 160.0f }, mat_comp_doom));


    //Spheres
    shared_ptr<Shape> esf1(new Sphere(Vector3{ 60, 10, -15 }, 7.5, mat_chicle_semidif));
    shared_ptr<Shape> esf2(new Sphere(Vector3{ 60, 10, 0 }, 7.5, mat_chicle_dif));
    shared_ptr<Shape> esf3(new Sphere(Vector3{ 60, 10, 15 }, 7.5, mat_chicle_reflejo_azul));
    shared_ptr<Shape> esf4(new Sphere(Vector3{ 260, -5, -7.5 }, 7.5, mat_cacodemon));
    shared_ptr<Shape> esf5(new Sphere(Vector3{ 60, -5, 7.5 }, 7.5, mat_chicle_fresnel));
    //Cylinder de prueba
    shared_ptr<Shape> cil_finito(new Cylinder(Vector3{ 50, -25, -20 }, Vector3{ 0, 1, 0 }, 7.5, 50.0, mat_Cylinder));

    shared_ptr<Shape> cil1(new Cylinder(Vector3{ 65, -25, 0 }, Vector3{ 0.0f, 1.0f, 0.0f }, 15.0f, 6.0f, mat_Sphere3));
    shared_ptr<Shape> cil2(new Cylinder{ Vector3{ 65, -25.0, 0.5 }, Vector3{ 0.5f, 1.0f, 1.0f}, 5.0, 25.0f, mat_Sphere1 });

    ///Añadir Shapes a la escena
    //im->add_shape(esf1);
    //im->add_shape(esf2);
    //im->add_shape(esf3);
    //im->add_shape(esf4);
    //im->add_shape(esf5);
    im->add_shape(luz_area_ventana_der);
    im->add_shape(pared_fondo_izq);
    im->add_shape(pared_fondo_diag);
    im->add_shape(techo_cerca_doom);
    im->add_shape(techo_izq_doom);
    im->add_shape(techo_fondo_doom);
    im->add_shape(suelo_cerca_doom);
    im->add_shape(suelo_izq_doom);
    im->add_shape(suelo_fondo_doom);
    im->add_shape(suelo_aux_doom);
    im->add_shape(techo_aux_doom);

    im->add_shape(col_cerca_iz_1);
    im->add_shape(col_cerca_iz_2);
    im->add_shape(col_cerca_iz_3);
    im->add_shape(col_cerca_iz_4);

    im->add_shape(col_lejos_iz_1);
    im->add_shape(col_lejos_iz_2);
    im->add_shape(col_lejos_iz_3);
    im->add_shape(col_lejos_iz_4);

    im->add_shape(col_cerca_der_1);
    im->add_shape(col_cerca_der_2);
    im->add_shape(col_cerca_der_3);
    im->add_shape(col_cerca_der_4);

    im->add_shape(col_lejos_der_1);
    im->add_shape(col_lejos_der_2);
    im->add_shape(col_lejos_der_3);
    im->add_shape(col_lejos_der_4);

    im->add_shape(pared1_escalon_iz);
    im->add_shape(suelo_escalon_iz);
    im->add_shape(pared2_escalon_iz);
    
    im->add_shape(pared1_escalon_lejos);
    im->add_shape(suelo_escalon_lejos);
    im->add_shape(pared2_escalon_lejos);

    im->add_shape(pared1_escalon_cerca);
    im->add_shape(suelo_escalon_cerca);
    im->add_shape(pared2_escalon_cerca);

    im->add_shape(suelo_der_lejos);
    im->add_shape(techo_der_lejos);
    im->add_shape(pared_suelo_lejos);
    im->add_shape(suelo_der_cerca);
    im->add_shape(techo_der_cerca);
    im->add_shape(pared_suelo_cerca);
    
    im->add_shape(pared_techo_iz);
    im->add_shape(pared_techo_cerca);
    im->add_shape(pared_techo_lejos);
    im->add_shape(pared_techo_lejos_der);
    im->add_shape(pared_techo_cerca_der);

    im->add_shape(pared_izq);
    im->add_shape(pared_der);
    im->add_shape(pared);
    im->add_shape(pared_detras);
    im->add_shape(techo);
    im->add_shape(suelo);

    //im->add_shape(cil_finito);
    //im->add_shape(cil1);
    //im->add_shape(cil2);

    ///Añadir luces puntuales a la escena
    im->add_point_light(lp_central);
    //im->add_point_light(lp_amarilla);
}