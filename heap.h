/**************************************
 
	Un heap diseñado para ser una cola
	de prioridad para el algoritmo de 
	Dijkstra.
	
	El heap guarda índices para el 
	arreglo de nodos del grafo. La
	prioridad es la distancia al nodo
	de origen.

***************************************/

#ifndef HEAP_H
#define HEAP_H
#include <stdbool.h>
#include "graph.h"

/*
	Una función que compara nodos de un grafo, y me dice cual está mas cerca
	de el nodo de origen. Los enteros son índices para el arreglo de nodos
	del grafo del primer parámetro.
*/
typedef int (heap_compare)(graph*, unsigned int, unsigned int);

#define HEAP_LEFT(nodo) ((nodo)+(nodo)+1)
#define HEAP_RIGHT(nodo) ((nodo)+(nodo)+2)
#define HEAP_PARENT(nodo) (((nodo)-1)>>1)

typedef struct {
    unsigned int* nodes;
    unsigned int space;
    unsigned int count;
    heap_compare* compare;
	graph* g; /* this heap holds indices into the graph's nodes array */
} heap; 

/*
	Pone en el heap todos los elementos del grafo, en orden de distancia
	al origen, según Dijkstra.
	
	O(|V| log|V|)
*/	

heap* heap_make(heap_compare*, graph*);

void heap_insert(heap*, const unsigned int);

/*
	Busca el elemento con la máxima prioridad, o sea el mínimo índice.
	O(1)
*/

unsigned int heap_find_min(const heap*);

/*
	Busca el elemento con la máxima prioridad, o sea el mínimo índice, y lo
	saca del heap, reestructurando el montículo.
	O(log n)
*/

unsigned int heap_delete_min(heap*);

/*
	Imprime a consola el heap, en formato DOT.
*/
void heap_dump(const heap*, const unsigned int);

/*
	Libera la memoria ocupada por el heap.
*/
void heap_destroy(heap*);

bool heap_is_empty(const heap*);

/*
	Reestructura el heap luego de haber cambiado alguna prioridad, pasando a
	prioridad mas alta (índice mas bajo).
	El parámetro es el índice del arreglo interno del heap por donde se desea
	arreglar las posibles violaciones de la propiedad min-heap.
	Ver node.heap_index.
	
*/
void heap_heapify_up(heap*, unsigned int);
										
#endif HEAP_H