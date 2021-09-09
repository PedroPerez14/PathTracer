/*
 * Author: Pedro José Pérez García
 * Date: 16/07/2021
 * Coms: Datos que van a estar por todas partes, como epsilon, etc
 */

#pragma once
#include <iostream>
#include <string>

#define _FOV_H 45.0f												//FOV horizontal de la cámara
#define _STOP_THRESHOLD 0.9f										//Umbral de probabilidad de parada de la ruleta rusa y otros eventos
#define _REINHARD_DELTA 0.000001f									//Necesario para que Reinhard no haga cosas raras si le llegan píxeles negros
#define _EPSILON 0.0f												//Para las intersecciones de rayos y geometria (creo que ya no hace falta)
#define _SURFACEACNEDISPLACEMENT 0.001f								//Necesario para evitar errores graves en la intersección con dieléctricos tras refracción hacia el interior de la geometría
#define _REINHARD_a	0.02f											//Parámetro clave del operador global de reinhard

const std::string _USER_PATH = "C:/Users/Pedro/Desktop/PathTracer";	//Directorio de guardado de imágenes output. PathTracer es el nombre del archivo al que luego se añade "_nomap.ppm" o "_tonemapped.ppm"