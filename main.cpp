
#include <iostream>
#include "Individuo.h"
#include "AG.h"
#include "Robot.h"
using namespace std;


int main()
{
    Robot robot;
    float x,y,z;

    Evolutivo ag(&robot);
    x=robot.ejeX(ag.best.cromosoma[0],ag.best.cromosoma[1],ag.best.cromosoma[2]);
    y=robot.ejeY(ag.best.cromosoma[0],ag.best.cromosoma[1],ag.best.cromosoma[2]);
    z=robot.ejeZ(ag.best.cromosoma[0],ag.best.cromosoma[1],ag.best.cromosoma[2]);
    cout<<"Cromosoma ganador"<<ag.best.cromosoma[0]<<" "<<ag.best.cromosoma[1]<<" "<<ag.best.cromosoma[2]<<endl;
    cout<<"Xp= "<<x<<endl;
    cout<<"Yp= "<<y<<endl;
    cout<<"Zp= "<<z<<endl;
    return 0;
}
