#ifndef MENU_H
#define MENU_H

#include "Fabrica.h"
#include "Motor.h"
#include "Sensor.h"
#include "User.h"
#include "Uteis.h"

class Menu {
	Fabrica *ptr_fabrica;

	void fabrica_motor();
	User *utilizadores_criar(string id, string nome);
	Motor *motores_criar(int id, string marca, float consumo_hora, float temperatura_aviso, float temperatura_paragem,
						 float prob_avaria, Ponto *posicao);
	Sensor *sensores_criar(int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao);

	string ler_nome_fich();

public:
	Menu(Fabrica *f);

	void iniciar();

	void fabrica();
	void utilizadores();
	void motores();
	void sensores();

	void sair();
};

#endif // MENU_H
