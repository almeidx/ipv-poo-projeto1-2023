#ifndef PONTO_H
#define PONTO_H

class Pair {
	int x, y;

public:
	Pair(int x, int y) {
		this->x = x;
		this->y = y;
	}

	~Pair() {}

	int Get_X() { return x; }
	int Get_Y() { return y; }
};

class Ponto : public Pair {
public:
	Ponto(int x, int y) : Pair(x, y) {}
	~Ponto() {}

	float Distancia(Ponto p) {
		// TODO: Calcular distância
	}
};

#endif // PONTO_H
