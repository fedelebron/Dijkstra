#include "Grafos.h"

typedef double costo;
typedef pair<costo, nodo> eje;
typedef pair<costo, nodo> estimado;
typedef vector<costo> vcosto;
typedef list<eje> lady;
typedef vector<lady> digrafo_pesado;
typedef set<estimado> cola;
#define UPDATE(c, v, k, l) {\
    c.erase(estimado(k, v));\
    c.insert(estimado(l, v));\
}
#define PRIMERO(c) (*(c.begin()))