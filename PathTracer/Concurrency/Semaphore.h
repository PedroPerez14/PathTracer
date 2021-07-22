//
// Created by pjper on 27/11/2020.
//

#pragma once


#include <mutex>
#include <condition_variable>

#include <assert.h>
#include <fstream>

using namespace std; //mutex, condition_variable, etc.

class Semaphore {
private:
    mutex mtx;                    //los dos primeros atributos se entenderán al estudiar los monitores
    condition_variable_any cv;
    int count;                    //natural asociado al semáforo
    bool initialized;             //para manejar constructor genérico: ¿está inicializado?
    //si vamos a querer trabajar con información en un log
    string name;                  //nombre que se asociará al semáforo para la información del "logger"
    bool withLog;                 //¿se ha ejecutado el constructor log?

public:
    //------------------------- constructores
    //Pre: n>=0
    //Post: count=n AND initialized AND NOT withLog
    //Coms: constructor "estándar", tal y como se ha contado en clases de teoría
    //      Ejemplo: "Semaphore s(2);"
    Semaphore(const int n);

    //Pre:
    //Post: NOT initialized AND NOT withLog
    //Coms: este constructor es no estándar. Se usará para los casos en que declaremos
    //      un array de semáforos, debiendo posteriormente ejecutar un "setInitiValue"
    //      Un intento de acceso a "wait" o "signal" sin ejecutar "setInitiValue" dará
    //      un error
    //      Ejemplo: "Semaphore s; s.setInitValue(2);" es equivalente a "Semaphore s(2);"
    Semaphore();

    //------------------------- destructor
    //Pre:
    //Post:
    //Coms: se invoca de manera automática al cerrarse el bloque donde ha sido declarado
    ~Semaphore();
    //-------------------------
    //Pre:  n>=0 AND NOT initialized
    //Post: initialized AND count=n
    //Coms: Semáforos declarados con los constructores "Semaphore()" y "Semaphore(Logger &logger, string name)"
    //      requieren que se asigne, mediante este procedimiento, el valor inicial asociado al natural del semáforo
    void setInitValue(const int n);
    //------------------------- operaciones estándar
    //Pre: initialized
    //Post: <count++>
    //Coms: en el caso de semáforos con información de log, genera un evento en el fichero
    void signal();

    //Pre: initialized
    //Post: <await count>0
    //          count--
    //      >
    //Coms: en el caso de semáforos con información de log, genera un evento en el fichero
    void wait();

    //------------------------- operaciones extendidas
    //Pre: n>0 AND initialized
    //Post: <count=count+n>
    //Coms: en el caso de semáforos con información de log, genera un evento en el fichero
    void signal(int n);

    //Pre: n>0 AND initialized
    //Post: <await count>=n
    //          count = count-n
    //      >
    //Coms: en el caso de semáforos con información de log, genera un evento en el fichero
    void wait(const int n);

    //------------------------- operaciones extendidas
    //Pre:
    //Post: this->logger=logger AND this->name=name AND withLog
};
