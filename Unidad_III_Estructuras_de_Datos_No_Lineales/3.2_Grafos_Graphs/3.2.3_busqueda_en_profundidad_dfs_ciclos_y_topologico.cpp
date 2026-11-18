/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           3.2.3 - Búsqueda en profundidad (DFS — Depth-First Search)
 * Caso Práctico:     Búsqueda en profundidad DFS (3 colores, detección de ciclos y orden topológico)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Teorema de aciclicidad por aristas de retroceso: Un grafo dirigido G es acíclico (DAG) si y solo si un recorrido DFS de G no produce ninguna arista de retroceso (es decir, nunca encuentra un vecino v en estado Color::GRIS). Al apilar cada vértice al tornarse NEGRO e invertir el vector al final, toda arista (u, v) cumple que u precede a v en Theta(V + E).
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

enum class Color { BLANCO, GRIS, NEGRO };

class AnalizadorDFS {
private:
    const std::vector<std::vector<int>>& adj_;
    std::vector<Color> color_;
    std::vector<int> ordenTopologico_;
    bool tieneCiclo_ = false;

    void dfsVisitar(int u) {
        color_[u] = Color::GRIS; // Entra en el marco de activacion actual
        for (int v : adj_[u]) {
            if (color_[v] == Color::BLANCO) {
                dfsVisitar(v); // Arista de Arbol (Tree Edge)
            } else if (color_[v] == Color::GRIS) {
                // Arista de Retroceso (Back-Edge) hacia un ancestro activo -> Ciclo detectado!
                tieneCiclo_ = true;
            }
        }
        color_[u] = Color::NEGRO; // Finaliza la exploracion del subarbol de u
        ordenTopologico_.push_back(u);
    }

public:
    explicit AnalizadorDFS(const std::vector<std::vector<int>>& adj)
        : adj_(adj), color_(adj.size(), Color::BLANCO) {}

    bool ejecutarYOrdenarTopologicamente(std::vector<int>& salidaOrden) {
        for (int u = 0; u < static_cast<int>(adj_.size()); ++u) {
            if (color_[u] == Color::BLANCO) dfsVisitar(u);
        }
        if (tieneCiclo_) return false;
        std::reverse(ordenTopologico_.begin(), ordenTopologico_.end());
        salidaOrden = ordenTopologico_;
        return true;
    }
};

int main() {
    // Seriacion de materias IPN: 0(Fund. Prog) -> 1(Algoritmos y ED) -> 3(Analisis de Alg.)
    //                            2(Mat. Discretas) -> 1(Algoritmos y ED)
    std::vector<std::vector<int>> dag = {{1}, {3}, {1}, {}};
    AnalizadorDFS dfs(dag);
    std::vector<int> orden;
    if (dfs.ejecutarYOrdenarTopologicamente(orden)) {
        std::cout << "Orden Topologico valido del DAG: ";
        for (int u : orden) std::cout << u << " ";
        std::cout << "\n";
    }
    return 0;
}
