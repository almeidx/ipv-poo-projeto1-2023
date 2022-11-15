#ifndef FABRICA_H
#define FABRICA_H

#include <algorithm>
#include <iostream>
#include <list>
#include <map>

#include "Motor.h"
#include "Sensor.h"
#include "User.h"
#include "Uteis.h"
#include "tinyxml2.h"

using namespace std;

#define TEMPERATURA_MANUTENCAO 10

typedef struct MotorLimits {
	Pair *verde, *amarelo, *vermelho;
	int probabilidade_avaria;
} MOTOR_LIMITS;

class Fabrica {
	string nome;
	int hora_inicio;
	int hora_fecho;
	int vizinhanca_aviso;
	int dimensao_x;
	int dimensao_y;

	map<string, MOTOR_LIMITS *> limites_motores;

	list<User *> *Users;
	list<Sensor *> *Sensores;
	list<Motor *> *Motores;

	User *User_Atual;

	bool Tem_User_Atual(const string fname);
	MOTOR_LIMITS *Extrair_Limites_Motor(tinyxml2::XMLElement *root, MOTOR_LIMITS *lim);

public:
	Fabrica();
	Fabrica(User *ut);
	~Fabrica();
	bool Load(const string &ficheiro);
	bool Add(User *ut);
	bool Add(Motor *m);
	void Listar(ostream &f = cout);
	void Desligar(int id_motor);
	ESTADO_MOTOR Get_Estado(int id_motor);
	list<Motor *> Listar_Tipo(string Tipo, ostream &f = cout);
	bool Manutencao();
	list<string> Ranking_Dos_Fracos();
	list<Motor *> Ranking_Dos_Mais_Trabalhadores();
	void Relatorio(string fich_xml);
	int Aviso_Humidade(list<Motor *> &lm);
	int Aviso_Fumo(list<Motor *> &lm, string fich_video);
	int Aviso_Luz(string fich_video);
	void Aviso_Missel(string fvideo, string festado = "Estado.txt");
};

#endif // FABRICA_H
