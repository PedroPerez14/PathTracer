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

void white_cornell_box(PathTracer* im)
{
    ///Luces puntuales
    shared_ptr<PointLight> lp_amarilla(new PointLight{ Vector3{ 60, -24.5, 24.5 }, Color{ 1.0f, 1.0f, 1.0f } });            //POINT LIGHT
    shared_ptr<PointLight> lp_central(new PointLight{ Vector3{ 42.5, 15.0f, 0 }, Color{ 19.607f, 19.607f, 19.607f } });     //POINT LIGHT

    ///Textures

    ///Materials
    shared_ptr<Material> mat_pared_tex = create_diffuse_material(Color{ 0.8f, 0.8f, 0.8f });
    shared_ptr<Material> mat_pared_der = create_diffuse_material(Color{ 0.039f, 1.0f, 0.039f });
    shared_ptr<Material> mat_pared_izq = create_diffuse_material(Color{ 1.0f, 0.039f, 0.039f });
    shared_ptr<Material> mat_Sphere1 = create_diffuse_material(Color{ 0.784f, 0.490f, 0.490f });
    shared_ptr<Material> mat_Sphere1_b = create_specular_material(); //Color(20, 20, 20)
    shared_ptr<Material> mat_techo_emisor = create_emitting_material(Color{ 2.0f, 2.0f, 2.0f });                            //AREA LIGHT
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
    shared_ptr<Shape> cil_finito(new Cylinder(Vector3{ 50, -25, -20 }, Vector3{ 0, 1, 0 }, 7.5, 50.0, mat_Cylinder));

    shared_ptr<Shape> cil1(new Cylinder( Vector3{ 65, -25, 0 }, Vector3{ 0.0f, 1.0f, 0.0f }, 15.0f, 6.0f, mat_Sphere3 ) );
    shared_ptr<Shape> cil2(new Cylinder{ Vector3{ 65, -25.0, 0.5 }, Vector3{ 0.5f, 1.0f, 1.0f}, 5.0, 25.0f, mat_Sphere1 });

    ///Añadir Shapes a la escena
    //im->add_shape(esf1);
    //im->add_shape(esf2);
    //im->add_shape(esf3);
    im->add_shape(esf4);
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