#include "AG.h"

Evolutivo::Evolutivo(Robot* r)
{
    log.open("log.txt",ios::out|ios::trunc);

    robot=r;
    //CUERPO DEL ALGORITMO
    generaPoblacion();//POBLACION INICIAL
    int j=0;
    while(1)
    {
        evaluacion();
        log<<"GENERACION "<<j<<endl;
        imprimePoblacion();
        seleccionCandidatos();
        cruzar();
        best=elite();
        seleccion[TAM_POBLACION-1]=best;
        poblacion=seleccion;
        if(best.fitness<1)//EL ALGORITMO TERMINA CUANDO EL ERROR ESTA POR DEBAJO DE 1
            break;
        j++;
    }
    log<<"GENERACION "<<j<<endl;
    imprimePoblacion();

}

Evolutivo::~Evolutivo()
{
    //dtor
}

//GENERACION DE POBLACION ALEATORIA
void Evolutivo::generaPoblacion()
{
    poblacion=new Individuo[TAM_POBLACION];
    for(int j=0; j<TAM_POBLACION; j++)
    {
        for(int i=0; i<TAM_CROMOSOMA; i++)
            poblacion[j].cromosoma[i]=aleloAleatorio();
    }
}
//OBTENER LOS FITNESS DE LOS INDIVIDUOS DE LA POBLACION
void Evolutivo::evaluacion()
{
    for(int j=0; j<TAM_POBLACION; j++)
        poblacion[j].fitness=funcionObjetivo(poblacion[j].cromosoma);
}
//FUNCION PARA EVALUAR FITNESS
float Evolutivo::funcionObjetivo(float * cromosoma)
{
    float x,y,z;
    x=robot->ejeX(cromosoma[0],cromosoma[1],cromosoma[2]);
    y=robot->ejeY(cromosoma[0],cromosoma[1],cromosoma[2]);
    z=robot->ejeZ(cromosoma[0],cromosoma[1],cromosoma[2]);
    return fabs((x-robot->x)*2)+fabs((y-robot->y)*2)+fabs((z-robot->z)*2);

}
//SELECCION DE PADRES
void Evolutivo::seleccionCandidatos()
{
    int num;
    float prob=0;
    seleccion=new Individuo[TAM_POBLACION];
    srand(rdtsc());
    asignaProbabilidad();
    ordenaPoblacion();
    //SELECCION DE TODA UNA POBLACION DE PADRES
    for(int i=0; i<TAM_POBLACION; i=i+2)
    {
        prob=0;
        num=rand()%100;
        //SELECCION PADRE 1
        for(int j=0; j<TAM_POBLACION; j++)
        {
            prob=prob+poblacion[j].probSeleccion;
            if(prob>num)
            {
                seleccion[i]=poblacion[j];
                break;
            }

        }
        prob=0;
        num=rand()%100;
        //SELECCION PADRE 2
        for(int j=0; j<TAM_POBLACION; j++)
        {
            prob=prob+poblacion[j].probSeleccion;
            if(prob>num)
            {
                seleccion[i+1]=poblacion[j];
                if(seleccion[i+1].fitness==seleccion[i].fitness)
                {
                    prob=0;
                    num=rand()%100;
                    j=-1;
                }
                else
                    break;
            }
        }
    }
}
//ORDENAR POBLACION POR PROBABILIDAD DE SELECCION DE MENOR A MAYOR
void Evolutivo::ordenaPoblacion()
{
    Individuo tmp;
    for(int i=0; i<TAM_POBLACION; i++)
    {
        for(int j=0; j<TAM_POBLACION-1; j++)
        {
            if(poblacion[j].probSeleccion<poblacion[j+1].probSeleccion)
            {
                tmp=poblacion[j];
                poblacion[j]=poblacion[j+1];
                poblacion[j+1]=tmp;
            }
        }
    }
}
//CRUZE DE CANDIDATOS
void Evolutivo::cruzar()
{
    int num;
    float tmp;
    srand(rdtsc());
    for(int j=0; j<TAM_POBLACION; j=j+2)
    {

        if((double) rand()/(RAND_MAX+1.0) < PROB_CRUCE)
        {
            num=1+rand()%((TAM_CROMOSOMA)-1);
            //LOS PADRES ESTAN EN PARES EN SELECCION
            for(int i=0; i<num; i++)
            {
                tmp=seleccion[j].cromosoma[i];
                seleccion[j].cromosoma[i]=seleccion[j+1].cromosoma[i];
                seleccion[j+1].cromosoma[i]=tmp;
            }
            //SE SOMETEN A MUTACION LOS DOS HIJOS
            mutacion(j);
        }

    }
}
//OBTENEMOS AL MEJOR INDIVIDUO DE LA POBLACION
Individuo Evolutivo::elite()
{
    Individuo elite=poblacion[0];
    for(int j=1; j<TAM_POBLACION; j++)
    {
        if(fabs(poblacion[j].fitness)<fabs(elite.fitness))
            elite=poblacion[j];
    }
    return elite;
}
//MUTACION DE DOS HIJOS
void Evolutivo::mutacion(int i)
{

    for(int j=0; j<TAM_CROMOSOMA; j++)
    {
        if ((double) rand()/(RAND_MAX+1.0) < PROB_MUTACION)
            seleccion[i].cromosoma[j]=aleloAleatorio();
    }
    for(int j=0; j<TAM_CROMOSOMA; j++)
    {
        if ((double) rand()/(RAND_MAX+1.0) < PROB_MUTACION)
            seleccion[i+1].cromosoma[j]=aleloAleatorio();
    }

}
//FUNCION PARA PLANTAR UNA MEJOR SEMILLA EN RANDS, OBTIENE LOS CICLOS DEL PROCESADOR
int Evolutivo::rdtsc()
{
    __asm__ __volatile__("rdtsc");
}
//OBTIENE EL VALOR PARA UN ALELO ALEATORIO
float Evolutivo::aleloAleatorio()
{
    srand(rdtsc());
    return LIM_INF+rand()%LIM_SUP+1;
}
//OBTIENE LAS PROBABILIDADES DE TODA LA POBLACION DANDO MAYOR PROBABILIDAD A MENOR FITNESS
void Evolutivo::asignaProbabilidad()
{
    float totalFitness=0;
    float totalDif=0;
    float probs[TAM_POBLACION];
    for(int j=0; j<TAM_POBLACION; j++)
        totalFitness=totalFitness+poblacion[j].fitness;
    for(int j=0; j<TAM_POBLACION; j++)
    {
        probs[j]=(totalFitness-poblacion[j].fitness);
        totalDif=totalDif+probs[j];
    }
    for(int j=0; j<TAM_POBLACION; j++)
        poblacion[j].probSeleccion=(probs[j]*100.0)/totalDif;
}
//FUNCION PARA IMPRIMIR LA POBLACION ACTUAL, EL ULTIMO MIEMBRO SERA EL MEJOR INDIVIDUO
void Evolutivo::imprimePoblacion()
{

    for(int j=0; j<TAM_POBLACION; j++)
    {
        for(int i=0; i<TAM_CROMOSOMA; i++)
            log<<poblacion[j].cromosoma[i]<<" ";
        log<<"--"<<poblacion[j].fitness;
        log<<"\n";

    }
}
