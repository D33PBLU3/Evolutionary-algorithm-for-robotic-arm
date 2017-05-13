#include "Robot.h"

Robot::Robot()
{
    int q1,q2,q3;
  // while(1){
    cout<<"X: ";
    cin>>x;
    cout<<"Y: ";
    cin>>y;
    cout<<"Z: ";
    cin>>z;

    //}

}

Robot::~Robot()
{
    //dtor
}
float Robot::ejeX(float q1,float q2,float q3){
	float x;
	x=-(sin(q1*PI/180))*(13.5*cos(q2*PI/180)+13.5*cos((q2*PI/180)+(q3*PI/180)));

	return x;
}
float Robot::ejeY(float q1,float q2,float q3){
	float y;
	y=cos(q1*PI/180)*(13.5*cos(q2*PI/180)+13.5*cos((q2*PI/180)+(q3*PI/180)));
	return y;
}
float Robot::ejeZ(float q1,float q2,float q3){
	float z;
	z=13.5*sin(q2*PI/180)+13.5*sin((q2*PI/180)+(q3*PI/180));
    return z;
}
