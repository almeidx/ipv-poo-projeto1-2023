#include "Fabrica.h"

int main(void) {
	cout << "Hello World" << endl;

	// Dar seed ao gerador de números "aleatórios"
	srand(time(NULL));

	Fabrica fabrica;

	fabrica.Load("fabrica.xml");

	fabrica.Listar_Tipo("Combustão");

	fabrica.Listar();

	return 0;
}
