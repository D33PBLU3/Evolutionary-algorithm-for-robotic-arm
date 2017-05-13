#ifndef AG_H
#define AG_H
#include <math.h>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Individuo.h"
#include "Robot.h"
#define TAM_POBLACION 20
#define GENERACIONES 200
#define PROB_MUTACION .04
#define PROB_CRUCE .6
#define LIM_SUP 360
#define LIM_INF 0


using namespace std;

class Evolutivo
{
    public:
        Evolutivo(Robot*);
        virtual ~Evolutivo();
        Individuo* poblacion;
        Individuo* seleccion;
        Robot *robot;

        Individuo best;
        ofstream log;
    protected:

    private:

    void generaPoblacion();
    void seleccionCandidatos();
    void evaluacion();
    void asignaProbabilidad();
    void ordenaPoblacion();
    void cruzar();
    Individuo elite();
    float funcionObjetivo(float*);
    void mutacion(int);
    void resultados();
    int rdtsc();
    float aleloAleatorio();
    void imprimePoblacion();

};

#endif // AG_H
