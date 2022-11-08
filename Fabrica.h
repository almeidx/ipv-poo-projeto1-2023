#ifndef FABRICA_H
#define FABRICA_H

#include <iostream>
#include <list>
#include <algorithm>

#include "EstadoMotor.h"
#include "Motor.h"
#include "Sensor.h"
#include "User.h"

using namespace std;

#define TEMPERATURA_MANUTENCAO 10

class Fabrica {
	list<User *> Users;
	list<Sensor *> Sensores;
	list<Motor *> Motores;

	User *Ut_Atual;

public:
	Fabrica();
	~Fabrica();
	Fabrica(User *ut);
    bool Load(const string &ficheiro); 
	bool Add(User *ut); 
    bool Load(const string &ficheiro);
	void Listar(ostream &f = cout);
	void Desligar(int id_motor);
	ESTADO_MOTOR Get_Estado(int id_motor);
	list<Motor *> Listar_Tipo(string Tipo, ostream &f = cout);
    bool Manutencao();
	list<string> Ranking_Dos_Fracos();
	list<Motor *> Ranking_Dos_Mais_Trabalhadores();
	int Aviso_Luz(string fich_video);
	void Aviso_Missel(string fvideo, string festado = "Estado.txt");


	
};

#endif // FABRICA_H
