#ifndef UTEIS_H
#define UTEIS_H

#include <iostream>
#include <list>
#include <sstream>

using namespace std;

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
};

#endif // UTEIS_H
