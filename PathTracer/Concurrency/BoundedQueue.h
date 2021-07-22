//
// Created by pjper on 27/11/2020.
//

#ifndef INFORMATICAGRAFICA_BOUNDEDQUEUE_H
#define INFORMATICAGRAFICA_BOUNDEDQUEUE_H

#pragma once
#include <iostream>
#include <string>

using namespace std;

template <class T>
class BoundedQueue {
public:
    //-----------------------------------------------------
    //Pre:  0<N
    //Post: this=< > AND #this=N
    //Com:  constructor
    BoundedQueue(const int N);
    //-----------------------------------------------------
    //Pre:
    //Post:
    //Com:  destructor
    ~BoundedQueue();
    //-----------------------------------------------------
    //Pre:
    //Post: this=<>
    void empty();
    //-----------------------------------------------------
    //Pre:  this=< d_1 ... d_n > AND n<#this
    //Post: this=< d_1 ... d_n d >
    void enqueue(const T d);
    //-----------------------------------------------------
    //Pre:  this=< d_1 ... d_n > AND 0<n
    //Post: this=< d_2 ... d_n >
    void dequeue();
    //-----------------------------------------------------
    //Pre:  this=< d_1 ... d_n > AND 0<n
    //Post: first()=d_1
    T first();
    //-----------------------------------------------------
    //Pre:  this=< d_1 ... d_n >
    //Post: length()=n
    int length();
    //-----------------------------------------------------
    //Pre:
    //Post: size()=#this
    int size();
    //-----------------------------------------------------
    //Pre:
    //Post:
    //Com:  muestra la cola por la salida estándar, separando los elementos mediante comas, y salta de línea
    void print();
    //-----------------------------------------------------
    //Pre:
    //Post: copy=this
    //Com:  Clonación de la cola
    void clone(BoundedQueue<T> &copy);
    //-----------------------------------------------------
private:
    int N;
    int nEl;
    int nMaxEl; //Número máximo de elementos que ha tenido la cola
    int porcentaje;
    T *data;
    int pri, sig;
};
// Para poder trabajar con tipos genéricos, declaración y código deben estar juntos
//#include "BoundedQueue.cpp"
//-----------------------------------------------------
template <class T>
BoundedQueue<T>::BoundedQueue(const int N) {

    this->N = N;
    data = new T[N];
    empty();
};
//-----------------------------------------------------
template <class T>
void BoundedQueue<T>::empty() {

    pri = 0;
    sig = 0;
    nEl = 0;
    nMaxEl = 0;
    porcentaje = 100;
};
//-----------------------------------------------------
template <class T>
BoundedQueue<T>::~BoundedQueue() {

    delete[] data;
};
//-----------------------------------------------------
template <class T>
void BoundedQueue<T>::enqueue(const T d) {

    assert(nEl < N);
    data[sig] = d;
    sig = (sig + 1) % N;
    nEl++;
    if (nEl > nMaxEl) nMaxEl = nEl;

};
//-----------------------------------------------------
template <class T>
void BoundedQueue<T>::dequeue() {

    assert(nEl > 0);
    pri = (pri + 1) % N;
    nEl--;
    int new_porcentaje = (float)nEl / nMaxEl * 100;
    if (new_porcentaje < porcentaje) {
        porcentaje = new_porcentaje;
        cout << 100 - porcentaje << "%" << endl;
    }

};
//-----------------------------------------------------
template <class T>
T BoundedQueue<T>::first() {

    assert(nEl > 0);
    T f = data[pri];
    return f;
};
//-----------------------------------------------------
template <class T>
int BoundedQueue<T>::length() {

    return nEl;
};
//-----------------------------------------------------
template <class T>
int BoundedQueue<T>::size() {

    return N;
};
//-----------------------------------------------------
template <class T>
void BoundedQueue<T>::print() {

    if (nEl > 0) {
        for (int i = 0; i < nEl - 1; i++) {
            cout << data[(pri + i) % N] << ",";
        }
        cout << data[(pri + nEl - 1) % N];
    }
    cout << endl;
};
//-----------------------------------------------------
template <class T>
void BoundedQueue<T>::clone(BoundedQueue<T>& copy) {

    assert(N == copy.N);

    // compañeros de la misma clase pueden acceder a elementos privados
    copy.nEl = nEl;
    copy.pri = pri;
    copy.sig = sig;
    for (int i = 0; i < N; i++) {
        copy.data[i] = data[i];
    }
}
//-----------------------------------------------------
#endif //INFORMATICAGRAFICA_BOUNDEDQUEUE_H
