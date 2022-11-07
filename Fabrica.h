#ifndef MOTOR_H
#define MOTOR_H

#include <iostream>
#include <string>
#include <list>

#include "User.h"
#include "Motor.h"
#include "Sensor.h"

using namespace std;

class Fabrica
{

    list<User *> ListUsers;
    list<Sensor *> ListSensor;
    list<Motor *> ListMotor;

public:
    Fabrica();
    ~Fabrica();
    void LOAD();
    void ADD();
};

#endif