#ifndef MOTOR_H
#define MOTOR_H

#include "Uteis.h"
#include <iostream>
#include <string>

using namespace std;

enum ESTADO_MOTOR { STOP = 0, START, RUN, AVARIADO };

class LimitesMotor {
	Pair verde, amarelo, vermelho;
	int prob_avaria;

public:
	LimitesMotor() {
		verde = Pair();
		amarelo = Pair();
		vermelho = Pair();
		prob_avaria = 0;
	}

	LimitesMotor(Pair v, Pair a, Pair r, int p) {
		verde = v;
		amarelo = a;
		vermelho = r;
		prob_avaria = p;
	}

	~LimitesMotor() {}

	Pair Get_Verde() {
		return verde;
	}
	Pair Get_Amarelo() {
		return amarelo;
	}
	Pair Get_Vermelho() {
		return vermelho;
	}
	int Get_Prob_Avaria() {
		return prob_avaria;
	}
};

class Fabrica;

class Motor {
	int id;
	string marca;
	float consumo_hora, consumo_atual, temperatura_aviso, temperatura_paragem, prob_avaria, temperatura;
	ESTADO_MOTOR estado;
	Ponto *posicao;
	int avarias, horas_trabalho;
	time_t ultima_hora_registada;
	Fabrica *ptr_fabrica;

	bool Esta_Avariado(const string fname);

public:
	Motor(Fabrica *fabrica, int id, string marca, float consumo_hora, float temperatura_aviso,
		  float temperatura_paragem, float prob_avaria, Ponto *posicao);
	~Motor();
	bool RUN();
	void START();
	void RESTART();
	bool STOP(bool warn = true);
	void ESTOU_QUENTE();

	string Get_Estado_String();
	void Print();

	int Get_Avarias() {
		return avarias;
	}
	float Get_Consumo_Atual() {
		return consumo_atual;
	}
	float Get_Consumo_Hora() {
		return consumo_hora;
	}
	int Get_Id() {
		return id;
	}
	ESTADO_MOTOR Get_Estado() {
		return estado;
	}
	int Get_Horas_Trabalho() {
		return horas_trabalho;
	}
	string Get_Marca() {
		return marca;
	}
	Ponto *Get_Posicao() {
		return posicao;
	}
	float Get_Prob_Avaria() {
		return prob_avaria;
	}
	float Get_Temperatura() {
		return temperatura;
	}

	void Set_Estado(ESTADO_MOTOR estado) {
		this->estado = estado;
	}
	void Set_Temperatura(float temperatura) {
		this->temperatura = temperatura;
	}
	void Inc_Avarias() {
		avarias++;
	}
	void Inc_Horas_Trabalho() {
		horas_trabalho++;
	}
	void Inc_Consumo_Atual() {
		consumo_atual = Uteis::Generate_Random_Float(10.0, 20.0);
	}

	virtual string Get_Tipo() {
		return "???";
	}
};

class MCombostao : public Motor {
public:
	MCombostao(Fabrica *fabrica, int id, string marca, float consumo_hora, float temperatura_aviso,
			   float temperatura_paragem, float prob_avaria, Ponto *posicao)
		: Motor(fabrica, id, marca, consumo_hora, temperatura_aviso, temperatura_paragem, prob_avaria, posicao) {}
	~MCombostao() {}

	string Get_Tipo() {
		return "MCOMBUSTAO";
	}
};

class MEletrico : public Motor {
public:
	MEletrico(Fabrica *fabrica, int id, string marca, float consumo_hora, float temperatura_aviso,
			  float temperatura_paragem, float prob_avaria, Ponto *posicao)
		: Motor(fabrica, id, marca, consumo_hora, temperatura_aviso, temperatura_paragem, prob_avaria, posicao) {}
	~MEletrico() {}

	string Get_Tipo() {
		return "MELETRICO";
	}
};

class MInducao : public Motor {
public:
	MInducao(Fabrica *fabrica, int id, string marca, float consumo_hora, float temperatura_aviso,
			 float temperatura_paragem, float prob_avaria, Ponto *posicao)
		: Motor(fabrica, id, marca, consumo_hora, temperatura_aviso, temperatura_paragem, prob_avaria, posicao) {}
	~MInducao() {}

	string Get_Tipo() {
		return "MINDUCAO";
	}
};

#endif // MOTOR_H
