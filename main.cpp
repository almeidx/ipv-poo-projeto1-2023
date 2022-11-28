#include "Fabrica.h"

int main(void) {
	// Dar seed ao gerador de números "aleatórios"
	srand(time(NULL));

	Fabrica fabrica;

	cout << string(10, '+') << "Fabrica::Load()" << string(10, '+') << endl;
	fabrica.Load("fabrica.xml");
	cout << string(10, '-') << "Fabrica::Load()" << string(10, '-') << endl;

	cout << string(10, '+') << "Fabrica::Listar()" << string(10, '+') << endl;
	fabrica.Listar();
	cout << string(10, '-') << "Fabrica::Listar()" << string(10, '-') << endl;

	cout << string(10, '+') << "Fabrica::Listar_Tipo()" << string(10, '+') << endl;
	fabrica.Listar_Tipo("MCOMBUSTAO");
	cout << string(10, '-') << "Fabrica::Listar_Tipo()" << string(10, '-') << endl;

	cout << string(10, '+') << "Fabrica::Ranking_Dos_Fracos()" << string(10, '+') << endl;
	list<string> fracos = fabrica.Ranking_Dos_Fracos();
	for (list<string>::iterator it = fracos.begin(); it != fracos.end(); ++it) {
		cout << *it << endl;
	}
	cout << string(10, '-') << "Fabrica::Ranking_Dos_Fracos()" << string(10, '-') << endl;

	cout << string(10, '+') << "Fabrica::Relatorio()" << string(10, '+') << endl;
	fabrica.Relatorio("relatorio.xml");
	cout << string(10, '-') << "Fabrica::Relatorio()" << string(10, '-') << endl;

	return 0;
}
