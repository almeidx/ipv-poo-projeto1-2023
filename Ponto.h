#ifndef PONTO_H
#define PONTO_H

class Ponto {
    int x, y;

public:
    Ponto(int x, int y) {
        this->x = x;
        this->y = y;
    }

    ~Ponto() {}

    int Get_X() { return x; }
    int Get_Y() { return y; }

    float Distancia(Ponto p) { 
        // TODO: Calcular distância
    }
};


#endif // PONTO_H