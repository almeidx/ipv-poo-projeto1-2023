#include "Fabrica.h"
#include "Menu.h"
#include "User.h"

int main(void) {
	srand(time(NULL));

	Fabrica fabrica;
	Menu menu(&fabrica);

	while (true) {
		menu.iniciar();
	}
}
