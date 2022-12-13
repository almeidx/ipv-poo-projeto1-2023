#ifndef MENU_H
#define MENU_H

#include "Fabrica.h"
#include "Motor.h"
#include "Sensor.h"
#include "User.h"
#include "Uteis.h"

class Menu {
public:
	static void iniciar(Fabrica *f);

	static void fabrica(Fabrica *fab);
	static void utilizadores(Fabrica *fab);
	static void motores(Fabrica *fab);
	static void sensores(Fabrica *fab);
	static void sair();

	static void fabrica_motor(Fabrica *fab);
	static User *utilizadores_criar(string id, string nome);
	static Motor *motores_criar(Fabrica *fab, int id, string marca, float consumo_hora, float temperatura_aviso,
								float temperatura_paragem, float prob_avaria, Ponto *posicao);
	static Sensor *sensores_criar(int id, string marca, float valor_aviso, float prob_avaria, Ponto *posicao);

	static string ler_nome_fich();
};

#endif // MENU_H
