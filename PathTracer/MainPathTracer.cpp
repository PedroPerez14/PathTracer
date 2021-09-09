/*
 * Author: Pedro José Pérez García
 * Date: 16/07/2021
 * Coms: Punto de entrada de la aplicación
 */

#pragma once
#include "MainPathTracer.h"

using namespace std;


/* Recibe 4 parámetros:
*  Primero: ancho de la imagen (1920)
*  Segundo: alto de la imagen (1080)
*  Tercero: Número de paths por píxel (4 por ejemplo)
*  Cuarto: Número de threads para paralelizar
*/
int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        cout << "Params: <im_width> <im_height> <paths_per_pixel> <n_threads>" << endl;
        return 1;
    }
    else
    {
        PathTracer* pt;
        
        int w = 1920;
        int h = 1080;
        int paths_per_pixel = 20;
        int n_threads = 11;

        w = std::stoi(argv[1]);
        h = std::stoi(argv[2]);
        paths_per_pixel = std::stoi(argv[3]);
        n_threads = std::stoi(argv[4]);

        pt = new PathTracer(w, h, paths_per_pixel, n_threads);
        
        ///------------CHOOSE A CORNELL BOX SCENE TO RENDER-------///
        //                            UNUSED
        //cornell_box_morada(rt);
        //cornell_box_plano(rt);
        //cornell_box_rv(rt);
        //cornell_box_tierra_emisora(rt);
        //cornell_box_cuadrado(rt);
        //espacio(rt);
        //  ------------------------------------------------------//
        //standard_cornell_box(pt);             
        //white_cornell_box(pt);
        //specular_cornell_box(pt);
        //mario_cornell_box(pt);
        doom_cornell_box(pt);
        ///-------------------------------------------------------///

        auto start = chrono::system_clock::now();
        std::shared_ptr<Image> result = pt->trace();
        auto end = chrono::system_clock::now();
        chrono::duration<float, std::milli> duration = end - start;
        cout << "Generating image file..." << endl;
        //Prepare image for tone mapping (c = 2^15)
        result->initialize_from_vector();
        //Save image twice, before and after applying tone mapping operators
        result->save_output(_USER_PATH + "_nomap", "ppm");

        result->c = 255.0f;
        result->tone_map("reinhard_g_pt");
        result->save_output(_USER_PATH + "_tonemapped", "ppm");

        cout << "Image generated succesfully." << std::endl;
        cout << "Total elapsed time: " << duration.count() << " ms" << endl;
        cout << "Output can be found at: " + _USER_PATH << endl;
    }
	return 0;
}
