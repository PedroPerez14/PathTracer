//
// Created by pjper on 27/11/2020.
//

#ifndef INFORMATICAGRAFICA_CONCURRENTBOUNDEDQUEUE_H
#define INFORMATICAGRAFICA_CONCURRENTBOUNDEDQUEUE_H
#include "Semaphore.h"
#include "BoundedQueue.h"

using namespace std;

template <class T>
class ConcurrentBoundedQueue {
public:
    //-----------------------------------------------------
    //Pre:  0<N
    //Post: this->bq=< > AND #this=N AND this->log=nullptr
    //Com:  constructor
    ConcurrentBoundedQueue(const int N);

    //-----------------------------------------------------
    //Pre:
    //Post:
    //Com:  destructor
    ~ConcurrentBoundedQueue();

    //-----------------------------------------------------
    //Pre:
    //Post: this->bq=<>
    void empty();

    //-----------------------------------------------------
    //Pre:  this->bq=< d_1 ... d_n >
    //Post: this->bq=< d_1 ... d_n d >
    //Coms: se bloquea hasta que haya un hueco para insertar el dato
    void enqueue(const T d);

    //-----------------------------------------------------
    //Pre:  this->bq=< d_1 ... d_n >
    //Post: this->bq=< d_2 ... d_n >
    //Coms: se bloquea hasta que haya un dato para desencolar
    void dequeue();

    ///Añadido en IG para path tracer concurrente, 27/11/2020
    bool dequeue(T& t);

    //-----------------------------------------------------
    //Pre:
    //Post: f=d_1
    //Coms: se bloquea hasta que this->bq=< d_1 ... d_n > and n>0
    void first(T &f);

    //-----------------------------------------------------
    //Pre:  this->bq=< d_1 ... d_n >
    //Post: l=n
    void length(int &l);

    //-----------------------------------------------------
    //Pre:
    //Post: s=#this->bq
    void size(int &s);

    //-----------------------------------------------------
    //Pre:
    //Post:
    //Com:  muestra la cola por la salida estándar, separando los elementos mediante comas
    void print();

    //-----------------------------------------------------
    //Pre:
    //Post: f=d_1 and this->bq=< d_1 ... d_n > and n>=0
    //Coms: se bloquea hasta que this->bq=< d_1 ... d_n > and n>0
    void firstR(T &f);

    //-----------------------------------------------------
private:
    int N;
    BoundedQueue<T> *bq;    //"BoundedQueue" con los datos
    //estructura para traducir el diseño mediante <await ...>
    Semaphore mutex;       //se deberá inicializar a 1 y pasarle (log,"mutex")
    Semaphore b_hay_hueco; //se deberá inicializar a 0 y pasarle (log,"b_hay_hueco")
    Semaphore b_hay_dato;  //se deberá inicializar a 0 y pasarle (log,"b_hay_dato")
    int d_hay_hueco;       //se deberán inicializar de acuerdo a la técnica propuesta
    int d_hay_dato;
    void AVISAR();
};
// Para poder trabajar con tipos genéricos, declaración y código deben estar juntos
//#include "ConcurrentBoundedQueue.cpp"
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
    if (bq->length() == bq->size())
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
    if (l == 0)
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
    if (l == 0)
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
void ConcurrentBoundedQueue<T>::first(T& f) {
    mutex.wait();
    int l = bq->length();
    if (l == 0)
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
void ConcurrentBoundedQueue<T>::length(int& l) {
    mutex.wait();
    l = bq->length();
    AVISAR();
};
//-----------------------------------------------------
template <class T>
void ConcurrentBoundedQueue<T>::size(int& s) {
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
void ConcurrentBoundedQueue<T>::firstR(T& f)
{
    mutex.wait();
    int l = bq->length();
    if (l == 0)
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
    if (bq->length() < bq->size() && d_hay_hueco > 0)
    {
        d_hay_hueco--;
        b_hay_hueco.signal();
    }
    else if (bq->length() > 0 && d_hay_dato > 0)
    {
        d_hay_dato--;
        b_hay_dato.signal();
    }
    else {
        mutex.signal();
    }
}


#endif //INFORMATICAGRAFICA_CONCURRENTBOUNDEDQUEUE_H
