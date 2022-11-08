#ifndef MOTOR_H
#define MOTOR_H

#include <iostream>
#include <string>

using namespace std;

enum ESTADO_MOTOR {
	STOP = 0,
	START,
	RUN,
	AVARIADO,
};

class Motor {
	int ID;
	string MARCA;
	float CONSUMO_HORA;
	float TEMPERATURA_AVISO;
	float TEMPERATURA_PARAGEM;
	float PROBABILIDADE_AVARIADA;

public:
	Motor();
	~Motor();
	bool RUN();
	void START();
	void RESTART();
	bool STOP();
	void ESTOU_QUENTE();

	int Get_Id() { return ID; }
};

#endif
