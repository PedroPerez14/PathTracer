//
// Created by pjper on 27/11/2020.
//

//*****************************************************************
// File:   Semaphore.cpp
// Author: PSCD-Unizar
// Date:   octubre 2016
// Coms:   Ver Semaphore.hpp
//         La implementación se entenderá cuando veamos variables
//         condición y monitores
//*****************************************************************

//Infoŕmación útil para entender la implementación en
//http://en.cppreference.com/w/cpp/thread/condition_variable
//La estudiaremos con más detalle cuando tratemos en la asignatura la parte de "monitores"

#include "Semaphore.h"

//----------------------------------------------------------
Semaphore::Semaphore(const int n):
        count(n) {
    assert(n >= 0);           //aborta si se viola la Pre

    initialized = true;       //ya está inicializado
    withLog = false;
}
//----------------------------------------------------------
Semaphore::Semaphore() {
    initialized = false;      //habrá que inicializarlo
    withLog = false;
}
//----------------------------------------------------------
Semaphore::~Semaphore() {
}
//----------------------------------------------------------
void Semaphore::setInitValue(const int n) {
    unique_lock<mutex> lck(mtx); //mutex para atomicidad de la función

    assert(!initialized && n >= 0);

    count = n;
    initialized = true;
}
//----------------------------------------------------------
void Semaphore::wait() {
    unique_lock<mutex> lck(mtx);

    assert(initialized);

    while(count == 0) {
        cv.wait(lck);
    }
    count--;
}
//----------------------------------------------------------
void Semaphore::signal() {
    unique_lock<mutex> lck(mtx);

    assert(initialized);

    count++;
    cv.notify_all(); //podemos cambiar la semántica con cv.notify_one()
}
//----------------------------------------------------------
void Semaphore::signal(const int n) {
    unique_lock<mutex> lck(mtx);

    assert(initialized && n>0);

    count = count+n;
    cv.notify_all(); //podemos cambiar la semántica con cv.notify_one()
}
//----------------------------------------------------------
void Semaphore::wait(const int n) {
    unique_lock<mutex> lck(mtx);

    assert(initialized && n>0);

    while(count < n) {
        cv.wait(lck);
    }
    count = count-n;
}

