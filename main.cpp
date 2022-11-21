#include "Fabrica.h"

int main(void) {
	cout << "Hello World" << endl;

	// Dar seed ao gerador de números "aleatórios"
	srand(time(NULL));

	Fabrica f;

	f.Load("fabrica.xml");

	f.Listar_Tipo("Combustão");

	return 0;
}
