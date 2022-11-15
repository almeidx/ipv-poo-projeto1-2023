#ifndef UTEIS_H
#define UTEIS_H

#include <iostream>
#include <list>
#include <sstream>

using namespace std;

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

class Uteis {
public:
	// https://stackoverflow.com/a/46931770
	static list<string> Split_String(const string &s, char delim) {
		list<string> result;
		stringstream ss(s);
		string item;

		while (getline(ss, item, delim)) {
			result.push_back(item);
		}

		return result;
	}

	static int *Split_String_Coordenadas(string str) {
		list<string> coords = Uteis::Split_String(str, ',');
		int *coordenadas = new int[2];

		coordenadas[0] = stoi(coords.front());
		coordenadas[1] = stoi(coords.back());

		return coordenadas;
	}

	static Pair *Split_String_Pair(string str) {
		list<string> coords = Uteis::Split_String(str, ',');

		int x = stoi(coords.front()), y = stoi(coords.back());

		return new Pair(x, y);
	}
};

#endif // UTEIS_H
