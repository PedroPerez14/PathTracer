//
// Created by pjper on 27/11/2020.
//

//*****************************************************************
// File:   ConcurrentConcurrentBoundedQueue.cpp
// Author: PSCD-Unizar
// Date:   Octubre 2018
// Coms:   Especificación de una clase cd cola limitada con gestión de acceso concurrente
//*****************************************************************
/*
#include "Semaphore.cpp"
//#include "ConcurrentBoundedQueue.h"
#include <cassert>


//-----------------------------------------------------
template <class T>
ConcurrentBoundedQueue<T>::ConcurrentBoundedQueue(const int N) {
    mutex.setInitValue(1);
    b_hay_hueco.setInitValue(0);
    b_hay_dato.setInitValue(0);
    d_hay_hueco = 0;
    d_hay_dato = 0;
    bq = new typename BoundedQueue<T>::BoundedQueue(N);
    this->N = N;
};
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::empty() {
    bq->empty();
};
//-----------------------------------------------------
template <class T>
ConcurrentBoundedQueue<T>::~ConcurrentBoundedQueue() {
    bq->~BoundedQueue();
};
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::enqueue(const T d) {
    mutex.wait();
    if(bq->length() == bq->size())
    {
        d_hay_hueco++;
        mutex.signal();
        b_hay_hueco.wait();
    }
    bq->enqueue(d);
    AVISAR();
};
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::dequeue() {
    mutex.wait();
    int l = bq->length();
    if(l == 0)
    {
        d_hay_dato++;
        mutex.signal();
        b_hay_dato.wait();
    }
    bq->dequeue();
    AVISAR();
};
//-----------------------------------------------------
template <class T>
bool ConcurrentBoundedQueue<T>::dequeue(T& t) {
    mutex.wait();
    bool retVal;
    int l = bq->length();
    if(l == 0)
    {
        retVal = false;
    }
    else
    {
        retVal = true;
        t = bq->first();
        bq->dequeue();
    }
    AVISAR();
    return retVal;
};
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::first(T &f) {
    mutex.wait();
    int l = bq->length();
    if(l == 0)
    {
        d_hay_dato++;
        mutex.signal();
        b_hay_dato.wait();
    }
    bq->first(f);
    AVISAR();
};
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::length(int &l) {
    mutex.wait();
    l = bq->length();
    AVISAR();
};
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::size(int &s) {
    s = bq->size();
};
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::print() {
    mutex.wait();
    BoundedQueue<T> aux(N);
    bq->clone(aux);
    aux.print();
    AVISAR();
};
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::firstR(T &f)
{
    mutex.wait();
    int l = bq->length();
    if(l == 0)
    {
        d_hay_dato++;
        mutex.signal();
        b_hay_dato.wait();
    }
    bq->first(f);
    bq->dequeue();
    AVISAR();
}
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::AVISAR() {
    if(bq->length() < bq->size() && d_hay_hueco > 0)
    {
        d_hay_hueco--;
        b_hay_hueco.signal();
    }
    else if(bq->length() > 0 && d_hay_dato > 0)
    {
        d_hay_dato--;
        b_hay_dato.signal();
    }
    else{
        mutex.signal();
    }
}
*/
