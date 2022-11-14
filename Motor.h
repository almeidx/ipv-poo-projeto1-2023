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
	int id;
	string marca;
	float consumo_hora;
	float temperatura_aviso;
	float temperatura_paragem;
		float probabilidade_avariada;

	float temperatura;
	ESTADO_MOTOR estado;
	int x,y;

	bool Esta_Avariado(const string fname);

public:
	Motor(int id, string marca, float consumo_hora, float temperatura_aviso, float temperatura_paragem,
		  float probabilidade_avariada,int x ,int y);
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
	void Set_Temperatura(float temperatura) { this->temperatura = temperatura; }
};

class MCombostao :  public Motor {

public:
	MCombostao(int id, string marca, float consumo_hora, float temperatura_aviso, float temperatura_paragem,
		  float probabilidade_avariada, int x ,int y) : Motor(id, marca, consumo_hora, temperatura_aviso ,temperatura_paragem, probabilidade_avariada, x ,y) {}
	~MCombostao();
};

class MEletrico : public Motor {

public:
	MEletrico(int id, string marca, float consumo_hora, float temperatura_aviso, float temperatura_paragem,
		  float probabilidade_avariada, int x , int y) : Motor(id, marca, consumo_hora, temperatura_aviso ,temperatura_paragem, probabilidade_avariada,x,y) {}
	~MEletrico();
};

#endif // MOTOR_H
