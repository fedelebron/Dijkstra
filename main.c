#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "graph.h"
#include "dijkstra.h"
#include "heap.h"

int main() {
	
    graph* g;

	FILE *f;
	char buffer[100], ciudad[100], *ciudad_tmp;
	bool started_vertices;
	int src, dest;
	double distance;
	
	started_vertices = false;
	g = graph_make();
	f = fopen("grafo.txt", "r");

	while(fgets(buffer, 100, f) != NULL) {
		if(!started_vertices) {
			if(*buffer == '\n') { continue; }
			if(strcmp(buffer, "---\n") == 0) { 
				started_vertices = true;
				continue;
			}
			sscanf(buffer, "%d) %[^\n]", &src, ciudad);
			ciudad_tmp = malloc(strlen(ciudad)+1);
			strcpy(ciudad_tmp, ciudad);
			graph_add_node(g, ciudad_tmp);
		} else {
			if(*buffer == '\n') { continue; }
			sscanf(buffer, "%d -> %d %lf\n", &src, &dest, &distance);
			graph_add_edge(g, src, dest, distance);			
		}
		
	}

    dijkstra(g, 0); /* buscar partiendo de Buenos Aires */
    graph_dump(g, 3); /* colorear el camino a Roma. Sabemos que existe pues todos los caminos llevan a Roma. */
    graph_destroy(g);

    return 0;
}
