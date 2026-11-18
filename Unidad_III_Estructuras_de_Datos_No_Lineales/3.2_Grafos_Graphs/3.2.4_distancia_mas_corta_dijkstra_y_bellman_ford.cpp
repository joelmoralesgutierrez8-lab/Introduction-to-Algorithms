/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           3.2.4 - Distancia más corta
 * Caso Práctico:     Distancia más corta (Algoritmo de Dijkstra O((V+E) log V) y Bellman-Ford O(V*E))
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - 2. Algoritmo de Bellman-Ford (Admite pesos negativos): Relaja sistemáticamente la totalidad de las |E| aristas a lo largo de |V| - 1 pasadas completas en tiempo Theta(V \cdot E), y ejecuta una pasada adicional |V|-ésima para detectar ciclos de peso negativo alcanzables.
 *   - 3. Algoritmo de Floyd-Warshall (Todos los pares): Resuelve el camino mínimo entre todos los pares de vértices (i, j) mediante programación dinámica D⁽^k⁾[i][j] = min(D⁽^k^-^1⁾[i][j], D⁽^k^-^1⁾[i][k] + D⁽^k^-^1⁾[k][j]) en tiempo Theta(V^3) y espacio Theta(V^2).
 *   - Descarte perezoso en Dijkstra (if (dActual > dist[u]) continue): Como std::priority_queue no incluye decrease-key nativo, al relajar una arista se inserta un nuevo par \{dist[v], v\} en O(log E). Cuando la versión antigua emerge de la cola, la guarda dActual > dist[u] la descarta en Theta(1), garantizando que las aristas de cada vértice se relajen una sola vez.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

struct AristaPond { int destino; int peso; };
constexpr int INF_DIST = std::numeric_limits<int>::max() / 2;

// 1. Algoritmo de Dijkstra con Cola de Prioridad (Min-Heap) para grafos con w(u,v) >= 0
std::vector<int> dijkstra(const std::vector<std::vector<AristaPond>>& adj, int origen) {
    int V = static_cast<int>(adj.size());
    std::vector<int> dist(V, INF_DIST);
    // Par en Min-Heap: (distancia_acumulada, vertice)
    using Par = std::pair<int, int>;
    std::priority_queue<Par, std::vector<Par>, std::greater<Par>> pq;

    dist[origen] = 0;
    pq.push({0, origen});

    while (!pq.empty()) {
        auto [dActual, u] = pq.top();
        pq.pop();

        // Descarte perezoso de entradas obsoletas en el monticulo
        if (dActual > dist[u]) continue;

        for (const auto& arista : adj[u]) {
            int v = arista.destino;
            int nuevoCosto = dist[u] + arista.peso;
            // Operacion de Relajacion (Relax)
            if (nuevoCosto < dist[v]) {
                dist[v] = nuevoCosto;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// 2. Algoritmo de Bellman-Ford: Soporta aristas negativas y detecta ciclos negativos en Theta(V*E)
bool bellmanFord(int V, int origen, const std::vector<std::tuple<int, int, int>>& aristas,
                 std::vector<int>& dist) {
    dist.assign(V, INF_DIST);
    dist[origen] = 0;

    for (int i = 1; i <= V - 1; ++i) {
        bool huboCambio = false;
        for (const auto& [u, v, w] : aristas) {
            if (dist[u] != INF_DIST && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                huboCambio = true;
            }
        }
        if (!huboCambio) break; // Parada temprana si las distancias ya convergieron
    }
    // Verificacion de ciclo negativo en la pasada V-esima
    for (const auto& [u, v, w] : aristas) {
        if (dist[u] != INF_DIST && dist[u] + w < dist[v]) return false; // Existe ciclo negativo
    }
    return true;
}

int main() {
    std::vector<std::vector<AristaPond>> red = {
        {{1, 4}, {2, 1}}, // 0 -> 1 (4), 0 -> 2 (1)
        {{3, 1}},         // 1 -> 3 (1)
        {{1, 2}, {3, 5}}, // 2 -> 1 (2), 2 -> 3 (5)
        {}
    };
    auto d = dijkstra(red, 0);
    std::cout << "Dijkstra distancia minima 0 -> 3: " << d[3] << "\n"; // 0->2->1->3 = 1+2+1 = 4
    return 0;
}
