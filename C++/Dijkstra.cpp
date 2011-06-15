#include "Dijkstra.h"

void dijkstra(const digrafo_pesado& g, int v, vcosto& dist) {
    int n = g.size();
    cola c;
    vbool vistos(n, false);
    
    dist[v] = 0;    
    c.insert(estimado(dist[v], v));
    while(!c.empty()) {
        estimado es = PRIMERO(c); // busco al elemento más cercano a v
        c.erase(es); // lo saco de la cola
        nodo p = es.second; // p es el nodo en sí
        
        vistos[p] = true;
        forall(it, g[p]) { // por cada vecino de p
            eje e = *it;
            costo s = e.first;
            nodo w = e.second;
            
            if(vistos[w]) continue; // si ya sé la mejor distancia, no hago nada
            costo nuevo = dist[p] + s; // costo de ir hasta p, y usar e
            if(dist[w] <= nuevo) continue; // si no puedo mejorar a w con p, no hago nada
            UPDATE(c, w, dist[w], nuevo); // actualizo la cola
            dist[w] = nuevo; // actualizo el estimado del costo a w
        }
        
    }
}

int main() {
    int n, m;
    nodo v, w;
    costo c;
    
    cin >> n;
    digrafo_pesado G(n);
    vcosto dist(n, INFINITO);

    cin >> m;
    while(m--) {
        cin >> v >> w >> c;
        G[v].push_back(eje(c, w));
    }
    
    cin >> v;
    dijkstra(G, v, dist);
    while(cin >> w) cout << "Distancia de " << v << " a " << w << ": " << dist[w] << endl;
    
    return 0;
}