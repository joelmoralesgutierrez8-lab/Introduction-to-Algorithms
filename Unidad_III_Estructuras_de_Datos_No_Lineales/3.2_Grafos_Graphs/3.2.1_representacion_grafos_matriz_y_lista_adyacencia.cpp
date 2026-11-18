/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           3.2.1 - Representaciones matriciales y basadas en listas
 * Caso Práctico:     Representaciones matriciales y basadas en listas (Grafo ponderado dual)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - 1. Matriz de Adyacencia: Arreglo bidimensional A de dimensión V \times V donde A[u][v] = w(u, v) (o 1 en grafos sin peso) si (u, v) \in E, y \infty (o 0) si (u, v) \notin E. Permite verificar la existencia de una arista (u, v) en tiempo constante Theta(1), pero consume invariablemente Theta(V^2) de memoria y exige Theta(V) para iterar sobre los vecinos de un vértice u.
 *   - 2. Lista de Adyacencia: Arreglo de V contenedores dinámicos (std::vector<std::vector<Arista>>), donde Adj[u] almacena exclusivamente los vértices adyacentes a u. Requiere memoria óptima Theta(V + E) y recorre los vecinos de u en tiempo proporcional a su grado Theta(deg(u)), siendo el estándar en grafos dispersos.
 *   - Selección de std::vector sobre std::list para Listas de Adyacencia: En ingeniería de algoritmos moderna, cada lista Adj[u] se implementa como std::vector<Arista> en lugar de nodos enlazados individuales para maximizar la localidad en caché L1 durante los recorridos BFS, DFS y Dijkstra.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <limits>

struct Arista {
    int destino;
    int peso;
};

class GrafoDual {
private:
    int V_;
    static constexpr int INF = std::numeric_limits<int>::max() / 2;
    std::vector<std::vector<int>> matrizAdy_;       // Representacion Matricial Theta(V^2)
    std::vector<std::vector<Arista>> listaAdy_;     // Representacion en Listas Theta(V + E)

public:
    explicit GrafoDual(int vertices)
        : V_(vertices),
          matrizAdy_(vertices, std::vector<int>(vertices, INF)),
          listaAdy_(vertices) {
        for (int i = 0; i < V_; ++i) matrizAdy_[i][i] = 0;
    }

    void agregarArista(int u, int v, int peso, bool dirigido = false) {
        matrizAdy_[u][v] = peso;
        listaAdy_[u].push_back({v, peso});
        if (!dirigido) {
            matrizAdy_[v][u] = peso;
            listaAdy_[v].push_back({u, peso});
        }
    }

    bool existeAristaMatriz(int u, int v) const noexcept {
        return matrizAdy_[u][v] != INF && u != v; // Consulta instantanea en Theta(1)
    }

    void imprimirVecinosLista(int u) const {
        std::cout << "Vecinos de " << u << " (en Theta(deg(u))): ";
        for (const auto& a : listaAdy_[u]) {
            std::cout << "->[v=" << a.destino << ", w=" << a.peso << "] ";
        }
        std::cout << "\n";
    }
};

int main() {
    GrafoDual g(4);
    g.agregarArista(0, 1, 10);
    g.agregarArista(0, 2, 25);
    g.agregarArista(1, 3, 5);
    g.imprimirVecinosLista(0);
    std::cout << "Existe arista (0,2) en O(1): " << (g.existeAristaMatriz(0, 2) ? "SI" : "NO") << "\n";
    return 0;
}
