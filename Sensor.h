#ifndef SENSOR_H
#define SENSOR_H

#include "Motor.h"
#include "Uteis.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

#define ALERTA_LUZ_FICHEIRO_VIDEO "video.mp4"
#define ALERTA_FUMO_FICHEIRO_VIDEO "video.mp4"
#define ALERTA_MISSEL_FICHEIRO_VIDEO "video.mp4"
#define ALERTA_MISSEL_FICHEIRO_ESTADO "festado-missel.mp4"

class Fabrica;

class Sensor {
	int id;
	string marca;
	float valor, valor_aviso, prob_avaria;
	Ponto *posicao;
	Fabrica *ptr_fabrica;

public:
	Sensor(Fabrica *fabrica, int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao);
	~Sensor();

	int Get_Id() {
		return id;
	}
	string Get_Marca() {
		return marca;
	}
	float Get_Prob_Avaria() {
		return prob_avaria;
	}
	void Set_Valor_Atual(float valor) {
		this->valor = valor;
	}
	float Get_Valor_Atual() {
		return valor;
	}
	Ponto *Get_Posicao() {
		return posicao;
	}
	float Get_Valor_Aviso() {
		return valor_aviso;
	}
	Fabrica *Get_Fabrica() {
		return ptr_fabrica;
	}

	virtual bool Em_Alerta() {
		return false;
	}

	virtual string Get_Tipo() {
		return "???";
	}

	float Ler_Valor();
	void Print();
};

class SLuz : public Sensor {
	void Avisar_Fabrica();

public:
	SLuz(Fabrica *fabrica, int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao)
		: Sensor(fabrica, id, marca, valor_aviso, prob_avaria, posicao) {}

	bool Em_Alerta() {
		if (Get_Valor_Atual() >= Get_Valor_Aviso()) {
			Avisar_Fabrica();
			return true;
		}

		return false;
	}

	string Get_Tipo() {
		return "SLUZ";
	}
};

class SHumidade : public Sensor {
	list<Motor *> Avisar_Fabrica();

public:
	SHumidade(Fabrica *fabrica, int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao)
		: Sensor(fabrica, id, marca, valor_aviso, prob_avaria, posicao) {}

	bool Em_Alerta() {
		if (Get_Valor_Atual() >= Get_Valor_Aviso()) {
			list<Motor *> motores_desligados = Avisar_Fabrica();

			cout << "[" << __FUNCTION__ << "] Número de motores desligados: " << motores_desligados.size() << endl;

			return true;
		}

		return false;
	}

	string Get_Tipo() {
		return "SHUMIDADE";
	}
};

class SFumo : public Sensor {
	list<Motor *> Avisar_Fabrica();

public:
	SFumo(Fabrica *fabrica, int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao)
		: Sensor(fabrica, id, marca, valor_aviso, prob_avaria, posicao) {}

	bool Em_Alerta() {
		if (Get_Valor_Atual() >= Get_Valor_Aviso()) {
			list<Motor *> motores_desligados = Avisar_Fabrica();

			cout << "[" << __FUNCTION__ << "] Número de motores desligados: " << motores_desligados.size() << endl;

			return true;
		}

		return false;
	}

	string Get_Tipo() {
		return "SFUMO";
	}
};

class SMissel : public Sensor {
	void Avisar_Fabrica();

public:
	SMissel(Fabrica *fabrica, int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao)
		: Sensor(fabrica, id, marca, valor_aviso, prob_avaria, posicao) {}

	bool Em_Alerta() {
		if (Get_Valor_Atual() >= Get_Valor_Aviso()) {
			Avisar_Fabrica();
			return true;
		}

		return false;
	}

	string Get_Tipo() {
		return "SMISSEL";
	}
};

class SFogo : public Sensor {
public:
	SFogo(Fabrica *fabrica, int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao)
		: Sensor(fabrica, id, marca, valor_aviso, prob_avaria, posicao) {}

	bool Em_Alerta() {
		if (Get_Valor_Atual() >= Get_Valor_Aviso()) {
			return true;
		}

		return false;
	}

	string Get_Tipo() {
		return "SFOGO";
	}
};

class STemperatura : public Sensor {
public:
	STemperatura(Fabrica *fabrica, int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao)
		: Sensor(fabrica, id, marca, valor_aviso, prob_avaria, posicao) {}

	bool Em_Alerta() {
		if (Get_Valor_Atual() >= Get_Valor_Aviso()) {
			return true;
		}

		return false;
	}

	string Get_Tipo() {
		return "STEMPERATURA";
	}
};

#endif // SENSOR_H
