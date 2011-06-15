/****************************
 
 * 1) Tipos de datos de grafo.
 * 2) API publica de grafos.

****************************/
#ifndef GRAPH_H
#define GRAPH_H

struct node;

/* 
	Un vertice es direccional: tiene fuente, direccion, y un peso.
	Los IDs son índices al arreglo de nodos del grafo.
*/
typedef struct {
    unsigned int source;
    unsigned int destination;
    double weight;
} edge;
 

/* 	
	Un nodo tiene vertices adyacentes.
   	edge_count es la cantidad de vertices adyacentes.
	edge_space es el espacio alocado (siempre >= edge_count) para vertices.
	distance, heap_index y previous son usados por el algoritmo de Dijkstra.
*/

typedef struct node {
    edge* edges;
    unsigned int edge_count;
    unsigned int edge_space;
   	char* value;

/* 
	Distancia estimada en el algoritmo de Dijkstra.
*/
    double distance;
/* 
	Se usa para mantener ordenada la cola de prioridad en Dijkstra.
*/ 
    int heap_index;
/* 
	El nodo previo en el camino mas corto, segun Dijkstra. Es un índice al 
	arreglo de nodos del grafo.
*/ 
	int previous;
} node; 

/* 	
	Conceptualmente, un grafo es una coleccion de nodos, cada nodo teniendo 
	sus vertices. Usa el mismo tipo de reserva de espacio que un nodo - 
	node_space es la cantidad de memoria reservada para nodos, node_count es
	la cantidad	efectiva de nodos en el grafo.
*/

typedef struct {
    node* nodes;
    unsigned int node_count;
    unsigned int node_space;
} graph;

/* 
	API de un grafo.
*/

graph* graph_make();

/* 
	Agregar un nodo al grafo, con el char* siendo el nombre del nodo.
	La memoria del char* sera liberada cuando se llame a graph_destroy.
*/
void graph_add_node(graph*, char*);
/* 
	Agregar un vertice entre el i-esimo nodo y el j-esimo nodo, 
	donde i y j son los unsigned ints, y el double es el peso del vertice.
*/
void graph_add_edge(graph*, unsigned int, unsigned int, double);

/*
	Liberar la memoria ocupada por el grafo.
*/

void graph_destroy(graph*);

/*
	Imprimir el grafo a consola, en formato DOT.
	Si el segundo parametro no es -1, se colorea la ruta mas corta entre la
	fuente del algoritmo de Dijkstra, y el nodo con el índice indicado.
*/
void graph_dump(graph*, int);

#endif // GRAPH_H