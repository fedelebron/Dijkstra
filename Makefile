CC = gcc
CFLAGS = -ansi -pedantic -Wall -Wextra -Wfatal-errors -O3
RM = rm
COMPILE = ${CC} ${CFLAGS}

all: dijkstra

dijkstra: graph.o heap.o dijkstra.o main.c
	${COMPILE} graph.o heap.o dijkstra.o main.c -o dijkstra

heap.o: heap.h heap.c graph.h
	${COMPILE} -c heap.c

graph.o: graph.c graph.h
	${COMPILE} -c graph.c

dijkstra.o: graph.h dijkstra.h dijkstra.c
	${COMPILE} -c dijkstra.c
clean: 
	${RM} -f dijkstra.o heap.o graph.o dijkstra

