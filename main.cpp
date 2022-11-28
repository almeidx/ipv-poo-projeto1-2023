#include "Fabrica.h"

int main(void) {
	cout << "Hello World" << endl;

	// Dar seed ao gerador de números "aleatórios"
	srand(time(NULL));

	Fabrica fabrica;

	fabrica.Load("fabrica.xml");

	fabrica.Listar_Tipo("Combustão");

	// fabrica.Listar();
	list<string> fracos = fabrica.Ranking_Dos_Fracos();

	for (list<string>::iterator it = fracos.begin(); it != fracos.end(); ++it) {
		cout << *it << endl;
	}

	return 0;
}
