#ifndef FABRICA_H
#define FABRICA_H

#include <iostream>
#include <list>

#include "Motor.h"
#include "Sensor.h"
#include "User.h"

using namespace std;

class Fabrica {
	list<User *> Users;
	list<Sensor *> Sensores;
	list<Motor *> Motores;

public:
	Fabrica();
	~Fabrica();
	void LOAD();
	void ADD();
};

#endif // FABRICA_H
