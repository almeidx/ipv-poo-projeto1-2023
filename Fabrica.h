#ifndef FABRICA_H
#define FABRICA_H

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

#include "Motor.h"
#include "Relogio.h"
#include "Sensor.h"
#include "User.h"
#include "Uteis.h"
#include "XMLWriter.h"
#include "tinyxml2.h"

using namespace std;

#define MULTIPLICADOR_RELOGIO 500
#define DISTANCIA_MAXIMA_SENSOR_FUMO 10

// #define PLAYER_VIDEO "vlc"
#define PLAYER_VIDEO ""

class Fabrica {
	string nome;
	int hora_inicio, hora_fecho, vizinhanca_aviso, dimensao_x, dimensao_y;

	map<string, LimitesMotor> limites_motores;

	list<User *> *Users;
	list<Sensor *> *Sensores;
	list<Motor *> *Motores;

	User *User_Atual;
	RelogioFabrica *Relogio;

	bool Tem_User_Atual(const string fname);
	LimitesMotor *Extrair_Limites_Motor(tinyxml2::XMLElement *root);

	static bool Sort_Motores(Motor *m1, Motor *m2);
	static bool Sort_Marcas(pair<string, int> a, pair<string, int> b);

public:
	Fabrica();
	Fabrica(User *ut);
	~Fabrica();
	bool Load(const string &ficheiro);
	bool Add(User *ut);
	bool Add(Motor *m);
	bool Add(Sensor *s);
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
	string Get_Estado_Cor(Motor *motor);

	clock_t Get_Time() {
		return Relogio->GetTime();
	}

	time_t Get_Horas() {
		return Relogio->GetTimeHours();
	}

	list<Motor *> *Get_Motores() {
		return Motores;
	}
	list<Sensor *> *Get_Sensores() {
		return Sensores;
	}
	list<User *> *Get_Users() {
		return Users;
	}

	User *Get_User_Atual() {
		return User_Atual;
	}
};

#endif // FABRICA_H
