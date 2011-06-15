A small implementation of Dijkstra's algorithm, for single-source shortest paths in a nonnegatively weighted directed graph.

Comments are in the header files, in Spanish. Its input is something of this form:

0) City 0 name here
1) City 1 name here
.
.
.
n) City n name here

---

i -> j k
.
.
.
i' -> j' k'

Where an arrow i -> j k means an edge from node i to node j, of weight k. The node indices come from the previous list.

main.c has the city to start the search from, and an optional city to find the shortest distance to, and color a shortest path.
