#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "graph.h"

/*
	Implementación del algoritmo de Dijkstra para el problema de una sola
	fuente. El entero pasado es el índice en el arreglo de nodos del grafo 
	en donde se encuentra la fuente.
*/

void dijkstra(graph*, unsigned int);

#endif