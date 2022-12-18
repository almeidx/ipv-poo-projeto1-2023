#include "Fabrica.h"
#include "Menu.h"

// #include "User.h"

int main(void) {
	srand(time(NULL));

	// Admin *adm = new Admin("1", "abc");
	// Fabrica fabrica(adm);

	Fabrica fabrica;

	Menu menu(&fabrica);

	while (true) {
		if (menu.loop()) {
			break;
		}
	}
}
