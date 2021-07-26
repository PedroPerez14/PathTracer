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
#define _REINHARD_DELTA 0.001f										//Necesario para que Reinhard no haga cosas raras
#define _EPSILON 0.0f												//Para las intersecciones de rayos y geometria (creo que ya no hace falta)
#define _SURFACEACNEDISPLACEMENT 0.001f

const std::string _USER_PATH = "C:/Users/Pedro/Desktop/PathTracer";	//Save dir and name for output