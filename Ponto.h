#ifndef PONTO_H
#define PONTO_H

#include <cmath>

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

	float Distancia(Ponto p) { return sqrt(pow(p.Get_X() - Get_X(), 2) + pow(p.Get_Y() - Get_Y(), 2)); }
};

#endif // PONTO_H
