#ifndef MOTOR_H
#define MOTOR_H

#include "Uteis.h"
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
	int id;
	string marca;
	float consumo_hora, temperatura_aviso, temperatura_paragem, probabilidade_avariada, temperatura;
	ESTADO_MOTOR estado;
	Ponto *posicao;
	int avarias;

	bool Esta_Avariado(const string fname);

public:
	Motor(int id, string marca, float consumo_hora, float temperatura_aviso, float temperatura_paragem,
		  float probabilidade_avariada, Ponto *posicao);
	~Motor();
	bool RUN();
	void START();
	void RESTART();
	bool STOP();
	void ESTOU_QUENTE();
	int Get_Id() { return id; }
	ESTADO_MOTOR Get_Estado() { return estado; }
	void Set_Estado(ESTADO_MOTOR estado) { this->estado = estado; }
	float Get_Temperatura() { return temperatura; }
	float Get_ProbAvar() { return probabilidade_avariada; }
	int Get_Avarias() { return avarias; }
	void Inc_Avarias() { avarias++; }
	string Get_Marca() { return marca; }
	void Set_Temperatura(float temperatura) { this->temperatura = temperatura; }
	Ponto *Get_Posicao() { return posicao; }

	virtual string Get_Tipo() { return "???"; }
};

class MCombostao : public Motor {
public:
	MCombostao(int id, string marca, float consumo_hora, float temperatura_aviso, float temperatura_paragem,
			   float probabilidade_avariada, Ponto *posicao)
		: Motor(id, marca, consumo_hora, temperatura_aviso, temperatura_paragem, probabilidade_avariada, posicao) {}
	~MCombostao() {}

	string Get_Tipo() { return "Combustão"; }
};

class MEletrico : public Motor {
public:
	MEletrico(int id, string marca, float consumo_hora, float temperatura_aviso, float temperatura_paragem,
			  float probabilidade_avariada, Ponto *posicao)
		: Motor(id, marca, consumo_hora, temperatura_aviso, temperatura_paragem, probabilidade_avariada, posicao) {}
	~MEletrico() {}

	string Get_Tipo() { return "Elétrico"; }
};

class MInducao : public Motor {
public:
	MInducao(int id, string marca, float consumo_hora, float temperatura_aviso, float temperatura_paragem,
			 float probabilidade_avariada, Ponto *posicao)
		: Motor(id, marca, consumo_hora, temperatura_aviso, temperatura_paragem, probabilidade_avariada, posicao) {}
	~MInducao() {}

	string Get_Tipo() { return "Indução"; }
};

#endif // MOTOR_H
