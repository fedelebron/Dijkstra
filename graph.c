#include "graph.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

graph* graph_make() {
    graph* g = malloc(sizeof(graph));
    g->node_space = 0;
    g->node_count = 0;
    g->nodes = NULL;
    return g;
}

/*
	El grafo está lleno cuando está usando todo el espacio que se reservó
	para él. Se puede pedir más.	
*/
bool graph_is_full(graph* g) {
    return g->node_space == g->node_count;
}


/*
	Doblamos la cantidad de memoria usada, o reservamos un lugar si el grafo
	está vacío.
*/
void graph_enlarge(graph* g) {    
    if(g->node_space == 0) { g->node_space = 1; } else { g->node_space *= 2; }
    g->nodes = realloc(g->nodes, sizeof(node) * (g->node_space));    
}

void graph_add_node(graph* g, char* c) {
    unsigned int count;
	node *n;

    if(graph_is_full(g)) {
        graph_enlarge(g);
    }

	count = g->node_count;
	n = &g->nodes[count];
    n->value = c;
	n->edges = NULL;
	n->edge_count = 0;
	n->edge_space = 0;
	n->distance = INFINITY;
	n->heap_index = -1;	
	n->previous = -1;
    
    g->node_count++;
} 


void graph_add_edge(graph* g, unsigned int i , unsigned int j, double weight) {
	edge *e;
	node *n;
	
	n = &g->nodes[i];
    if(n->edge_space == n->edge_count) {
		if(n->edge_space == 0) { 
			n->edge_space = 1; 
		} else { 
			n->edge_space *= 2; 
		} 
		n->edges = realloc(n->edges, sizeof(edge) * (n->edge_space));
    }
	e = &n->edges[n->edge_count];
	e->source = i;
	e->destination = j;
	e->weight = weight;
	g->nodes[i].edge_count++;
}


void graph_destroy(graph* g) {
	unsigned int i;
    for(i = 0; i < g->node_count; i++) {
		free(g->nodes[i].edges);
		free(g->nodes[i].value);
    }
    free(g->nodes);
    free(g);
}


void graph_dump(graph* g, int highlight_destination) {
	unsigned int j;
	int i, count;
	int index;
	int* indices;
	
	count = (int) g->node_count;
	indices = NULL;

	
	if(highlight_destination != -1) {
		indices = malloc(sizeof(int) * count);
		for(i = 0; i < count; i++)  { indices[i] = -1; }
		index = highlight_destination;
		while(g->nodes[index].previous != -1) {
			indices[index] = g->nodes[index].previous;
			index = (g->nodes[index].previous);
		}
	}
    
    printf("digraph g {\noverlap = false;\nnode [color=black,fillcolor=white,shape=ellipse,style=\"filled,bold\",width=.3, height=.3];\nedge [fontname=Helvetica,fontsize=9];\n");

	for(i = 0; i < count; i++) {
		for(j = 0; j < g->nodes[i].edge_count; j++) {
			printf("\"%s\" -> \"%s\" [label=%d%s];\n", 
				g->nodes[i].value, 
				g->nodes[g->nodes[i].edges[j].destination].value, 
				(int) g->nodes[i].edges[j].weight,
				(highlight_destination != -1) ? (indices[g->nodes[i].edges[j].destination] == i  ? ", color=red" : "") : ""
				);
		}
	}
    printf("}\n");

	if(highlight_destination != -1) {
		free(indices);
	}
}