/*
 * Author: Pedro Jos� P�rez Garc�a
 * Date: 16/07/2021
 * Coms: Datos que van a estar por todas partes, como epsilon, etc
 */

#pragma once
#include <iostream>
#include <string>

#define _FOV_H 45.0f												//FOV horizontal de la c�mara
#define _STOP_THRESHOLD 0.9f										//Umbral de probabilidad de parada de la ruleta rusa y otros eventos
#define _REINHARD_DELTA 0.000001f									//Necesario para que Reinhard no haga cosas raras si le llegan p�xeles negros
#define _EPSILON 0.0f												//Para las intersecciones de rayos y geometria (creo que ya no hace falta)
#define _SURFACEACNEDISPLACEMENT 0.001f								//Necesario para evitar errores graves en la intersecci�n con diel�ctricos tras refracci�n hacia el interior de la geometr�a
#define _REINHARD_a	0.02f											//Par�metro clave del operador global de reinhard

const std::string _USER_PATH = "C:/Users/Pedro/Desktop/PathTracer";	//Directorio de guardado de im�genes output. PathTracer es el nombre del archivo al que luego se a�ade "_nomap.ppm" o "_tonemapped.ppm"