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
        int w = std::stoi(argv[1]);
        int h = std::stoi(argv[2]);
        int paths_per_pixel = std::stoi(argv[3]);
        int n_threads = std::stoi(argv[4]);
        pt = new PathTracer(w, h, paths_per_pixel, n_threads);

        ///------------CHOOSE A CORNELL BOX SCENE TO RENDER-------///
        //TODO definir las funciones en PathTracer.h
        //cornell_box_morada(rt);
        //cornell_box_plano(rt);
        //cornell_box_rv(rt);
        white_cornell_box(pt);
        //cornell_box_tierra_emisora(rt);
        //cornell_box_cuadrado(rt);
        //espacio(rt);
        ///--------------------------------------------------------///

        auto start = chrono::system_clock::now();
        std::shared_ptr<Image> result = pt->trace();
        auto end = chrono::system_clock::now();
        chrono::duration<float, std::milli> duration = end - start;
        cout << "Generating image file..." << endl;
        //Save image twice, before tone mapping and after
        result->save_output(USER_PATH + "_nomap", "ppm");

        result->c = 255.0f;
        result->tone_map("reinhard_g_pt");
        result->save_output(USER_PATH + "_tonemapped", "ppm");

        cout << "Image generated succesfully." << std::endl;
        cout << "Total elapsed time: " << duration.count() << " ms" << endl;
        cout << "Output can be found at: " + USER_PATH << endl;
    }
    //test
	return 0;
}
