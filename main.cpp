#include "Fabrica.h"
#include "User.h"
#include <functional>

void fn_wrapper(const string fname, function<void()> fn) {
	cout << string(10, '+') << "Fabrica::" << fname << "()" << string(10, '+') << endl;
	fn();
	cout << string(10, '-') << "Fabrica::" << fname << "()" << string(10, '-') << endl;
}

int main(void) {
	// Dar seed ao gerador de números "aleatórios"
	srand(time(NULL));

	Fabrica fabrica;
	Admin admin("123", "Toze");

	fn_wrapper("Add(User)", [&] { fabrica.Add(&admin); });

	fn_wrapper("Load", [&] { fabrica.Load("fabrica.xml"); });

	fn_wrapper("Listar", [&] { fabrica.Listar(); });

	fn_wrapper("Listar_Tipo", [&] { fabrica.Listar_Tipo("MCOMBUSTAO"); });

	fn_wrapper("Ranking_Dos_Fracos", [&] {
		list<string> fracos = fabrica.Ranking_Dos_Fracos();
		for (list<string>::iterator it = fracos.begin(); it != fracos.end(); ++it) {
			cout << *it << endl;
		}
	});

	fn_wrapper("Ranking_Dos_Mais_Trabalhadores", [&] {
		list<Motor *> mais_trabalhadores = fabrica.Ranking_Dos_Mais_Trabalhadores();
		for (list<Motor *>::iterator it = mais_trabalhadores.begin(); it != mais_trabalhadores.end(); ++it) {
			cout << (*it)->Get_Id() << " - " << (*it)->Get_Marca() << endl;
		}
	});

	fn_wrapper("Relatorio", [&] { fabrica.Relatorio("relatorio.xml"); });

	fn_wrapper("Aviso_Temperatura", [&] {
		list<Motor *> motores_desligados;

		cout << "nº de motores desligados: " << fabrica.Aviso_Humidade(motores_desligados) << endl;
	});

	fn_wrapper("Aviso_Fumo", [&] {
		list<Motor *> motores_desligados;

		cout << "nº de motores desligados: " << fabrica.Aviso_Fumo(motores_desligados, "./video.mp4") << endl;
	});

	fn_wrapper("Aviso_Luz", [&] { cout << "return: " << fabrica.Aviso_Luz("./video.mp4") << endl; });

	fn_wrapper("Aviso_Missel", [&] { fabrica.Aviso_Missel("./video.mp4", "festado.xml"); });

	while (true) {
		time_t Simulada = fabrica.Get_Time();
		cout << "A executar RUN() nos motores = " << asctime(localtime(&Simulada));

		list<Motor *> *m = fabrica.Get_Motores();

		for (list<Motor *>::iterator it = m->begin(); it != m->end(); ++it) {
			(*it)->RUN();
		}

		RelogioFabrica::Wait(1);
	}

	return 0;
}
