#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

heap* heap_make(heap_compare* cmp, graph* g) {
	unsigned int i;
    heap* h = malloc(sizeof(heap));
    h->nodes = malloc(sizeof(node) * (g->node_count) * 2);
    h->compare = cmp;
    h->space = g->node_count * 2; /* allocated */
    h->count = 0; /* used */
	h->g = g;
	for(i = 0; i < g->node_count; i++) {
		heap_insert(h, i);
	}
    return h;
}

bool heap_is_full(const heap* h) {
    return h->count == h->space;
}

void heap_enlarge(heap* h) {
    if(h->space) { h->space *= 2; } else { h->space = 1; }
    h->nodes = realloc(h->nodes, sizeof(unsigned int) * (h->space)); 
}

void heap_heapify_up(heap* h, unsigned int key) {
    unsigned int value = h->nodes[key],
                 temp;
    while(key != 0 && (*h->compare)(h->g, value, h->nodes[HEAP_PARENT(key)]) < 0) {
        temp = h->nodes[HEAP_PARENT(key)];
        h->nodes[HEAP_PARENT(key)] = value;
		h->g->nodes[temp].heap_index = key;
		
        h->nodes[key] = temp;    
		h->g->nodes[value].heap_index = HEAP_PARENT(key);
        key = HEAP_PARENT(key); 
        value = h->nodes[key];		
		
    } 
}

void heap_heapify_down(heap* h) {
    unsigned int pos = 0, 
                 newpos,
                 temp;
	node** graph_nodes;

	graph_nodes = &h->g->nodes;
	
    while(1) {
        if(HEAP_LEFT(pos) <= h->count) { 
            if(HEAP_RIGHT(pos) <= h->count) {
                newpos = (*h->compare)(h->g, h->nodes[HEAP_RIGHT(pos)], h->nodes[HEAP_LEFT(pos)]) < 0 ? HEAP_RIGHT(pos) : HEAP_LEFT(pos);
            } else {
                newpos = HEAP_LEFT(pos);
            }
        } else {
            break; /* es una hoja, nada que hacer */
        }
        
        if((*h->compare)(h->g, h->nodes[pos], h->nodes[newpos]) > 0) {
            temp = h->nodes[pos];
			(*graph_nodes)[temp].heap_index = newpos;
			(*graph_nodes)[h->nodes[newpos]].heap_index = pos;
            h->nodes[pos] = h->nodes[newpos];
            h->nodes[newpos] = temp;
        } else {
            break; /* la posicion es correcta */
        }
    }
}

void heap_insert(heap* h, const unsigned int key) {
    if(heap_is_full(h)) { 
        heap_enlarge(h); 
    }
    h->nodes[h->count] = key;
	h->g->nodes[key].heap_index = h->count;
    h->count++;
    heap_heapify_up(h, h->count-1);
}

unsigned int heap_find_min(const heap* h) {
    return h->nodes[0];
}


unsigned int heap_delete_min(heap* h) {
    unsigned int retval = h->nodes[0];
    
    h->nodes[0] = h->nodes[h->count-1];
    h->count--;
    if(heap_is_empty(h)) {
        free(h->nodes);
    } else {
        heap_heapify_down(h);
    }
    return retval;
}

void heap_dump(const heap* h, const unsigned int from) {
    if(from == 0) {
        printf("digraph g {\nnode [shape = record,height=.1];\n");
    }
    if(from < h->count) {
        printf("node%d[ label = \"<f0> | <f1> %s | <f2>\"];\n", from, h->g->nodes[h->nodes[from]].value);

        if(HEAP_LEFT(from) < h->count) {
            printf("\"node%d\":f0 -> \"node%d\":f1\n", from, HEAP_LEFT(from));
            heap_dump(h, HEAP_LEFT(from));
        }
    
        if(HEAP_RIGHT(from) < h->count) {
            printf("\"node%d\":f2 -> \"node%d\":f1\n", from, HEAP_RIGHT(from));
            heap_dump(h, HEAP_RIGHT(from));
        }
    }
    
    if(from == 0) { 
        printf("}\n");
    }
}

void heap_destroy(heap* h) {
    if(!heap_is_empty(h)) {
        free(h->nodes);
    }
    free(h);
}

bool heap_is_empty(const heap* h) {
    return h->count == 0;
}
