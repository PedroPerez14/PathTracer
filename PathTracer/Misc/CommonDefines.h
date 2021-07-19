/*
 * Author: Pedro José Pérez García
 * Date: 16/07/2021
 * Coms: Datos que van a estar por todas partes, como epsilon, etc
 */

#pragma once

#define _FOV_H 60				//FOV horizontal de la cámara
#define _STOP_THRESHOLD 0.9f	//Umbral de probabilidad de parada de la ruleta rusa y otros eventos
#define _REINHARD_DELTA 0.001f	//Necesario para que Reinhard no haga cosas raras
#define _EPSILON 0.001			//Para las intersecciones de rayos y geometria
