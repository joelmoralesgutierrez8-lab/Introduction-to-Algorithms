/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           3.2.2 - Búsqueda en amplitud (BFS — Breadth-First Search)
 * Caso Práctico:     Búsqueda en amplitud BFS (Distancias mínimas en aristas y reconstrucción de ruta)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Invariante de monotonicidad en la cola FIFO: En todo instante, la cola contiene vértices cuyas distancias difieren a lo sumo en 1 unidad (d[u] <= d[v] <= d[u] + 1). Cada vértice se encola a lo sumo una vez (cuando distancia[v] == -1), garantizando tiempo Theta(V + E).
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct ResultadoBFS {
    std::vector<int> distancia;
    std::vector<int> padre;
};

// Complejidad Temporal: Theta(V + E) | Complejidad Espacial: Theta(V)
ResultadoBFS busquedaEnAmplitudBFS(const std::vector<std::vector<int>>& adj, int origen) {
    int V = static_cast<int>(adj.size());
    ResultadoBFS res{std::vector<int>(V, -1), std::vector<int>(V, -1)};
    std::queue<int> cola;

    res.distancia[origen] = 0;
    cola.push(origen);

    while (!cola.empty()) {
        int u = cola.front();
        cola.pop();

        for (int v : adj[u]) {
            if (res.distancia[v] == -1) { // Vertice aun no visitado (Color BLANCO -> GRIS)
                res.distancia[v] = res.distancia[u] + 1;
                res.padre[v] = u;
                cola.push(v);
            }
        }
    }
    return res;
}

std::vector<int> reconstruirCamino(int origen, int destino, const std::vector<int>& padre) {
    std::vector<int> camino;
    for (int v = destino; v != -1; v = padre[v]) {
        camino.push_back(v);
    }
    std::reverse(camino.begin(), camino.end());
    if (camino.empty() || camino.front() != origen) return {};
    return camino;
}

int main() {
    std::vector<std::vector<int>> grafo = {
        {1, 2},    // 0 conectado con 1, 2
        {0, 3, 4}, // 1 conectado con 0, 3, 4
        {0, 4},    // 2 conectado con 0, 4
        {1, 5},    // 3 conectado con 1, 5
        {1, 2, 5}, // 4 conectado con 1, 2, 5
        {3, 4}     // 5 conectado con 3, 4
    };
    auto bfs = busquedaEnAmplitudBFS(grafo, 0);
    auto ruta = reconstruirCamino(0, 5, bfs.padre);
    std::cout << "Distancia minima de 0 a 5: " << bfs.distancia[5] << " saltos | Ruta: ";
    for (int v : ruta) std::cout << v << " ";
    std::cout << "\n";
    return 0;
}
