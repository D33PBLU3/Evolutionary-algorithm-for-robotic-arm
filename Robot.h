#ifndef ROBOT_H
#define ROBOT_H
#include <math.h>
#include <iostream>
#define PI 3.14159265
using namespace std;
class Robot
{
    public:
        Robot();
        virtual ~Robot();
        float x,y,z;

    float ejeX(float,float,float);
    float ejeY(float,float,float);
    float ejeZ(float,float,float);
    private:
};

#endif // ROBOT_H
