#ifndef INDIVIDUO_H
#define INDIVIDUO_H
#define TAM_CROMOSOMA 3

class Individuo
{
    public:
        Individuo();
        virtual ~Individuo();
        float cromosoma[TAM_CROMOSOMA];
        float fitness;
        float probSeleccion;
        float x,y,z;
    protected:

    private:
};

#endif // INDIVIDUO_H
