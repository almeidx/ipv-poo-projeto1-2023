#ifndef RELOGIO_H
#define RELOGIO_H

#include <iostream>
#include <time.h>

using namespace std;

class RelogioFabrica {
	time_t START;
	int VELOCIDADE;

public:
	RelogioFabrica(int Vel = 1) {
		VELOCIDADE = Vel;
		START = time(0);
		cout << "Hora de Arranque = " << asctime(localtime(&START));
	};

	time_t GetTime() {
		time_t NOW = time(0);
		time_t Simulada = START + (NOW - START) * VELOCIDADE;
		return Simulada;
	}

	static void Wait(int s) {
		clock_t T0 = clock();
		clock_t T1 = T0 + s * CLOCKS_PER_SEC;
		while (clock() < T1)
			;
	}
};

#endif // RELOGIO_H
