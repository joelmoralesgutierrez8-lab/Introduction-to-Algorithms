/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           3.2.5 - Implementaciones y aplicaciones
 * Caso Práctico:     Aplicaciones de Grafos (Árbol de Expansión Mínima MST con Kruskal y Union-Find DSU)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Optimalidad casi constante del Union-Find: Al combinar compresión de caminos en find(i) con unión por rango en unir(x, y), una secuencia de m operaciones sobre V vértices toma tiempo O(m \cdot \alpha(V)), donde \alpha(V) <= 4 es la inversa de la función de Ackermann de Tarjan. Así, el costo de Kruskal queda dominado únicamente por el ordenamiento inicial de las aristas en O(E log E) = O(E log V).
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

struct AristaKruskal {
    int u, v, peso;
    bool operator<(const AristaKruskal& otra) const noexcept { return peso < otra.peso; }
};

// Estructura de Conjuntos Disjuntos (Disjoint Set Union) en tiempo casi constante O(alpha(V))
class UnionFind {
private:
    std::vector<int> padre_;
    std::vector<int> rango_;

public:
    explicit UnionFind(int n) : padre_(n), rango_(n, 0) {
        std::iota(padre_.begin(), padre_.end(), 0);
    }

    int find(int i) {
        if (padre_[i] != i) {
            padre_[i] = find(padre_[i]); // Compresion de caminos (Path Compression)
        }
        return padre_[i];
    }

    bool unir(int x, int y) {
        int raizX = find(x), raizY = find(y);
        if (raizX == raizY) return false; // Ya estan en la misma componente (formaria ciclo)
        // Union por rango (Union by Rank)
        if (rango_[raizX] < rango_[raizY]) padre_[raizX] = raizY;
        else if (rango_[raizX] > rango_[raizY]) padre_[raizY] = raizX;
        else { padre_[raizY] = raizX; ++rango_[raizX]; }
        return true;
    }
};

int kruskalMST(int V, std::vector<AristaKruskal>& aristas, std::vector<AristaKruskal>& mstSalida) {
    std::sort(aristas.begin(), aristas.end()); // O(E log E)
    UnionFind dsu(V);
    int costoTotal = 0;

    for (const auto& a : aristas) {
        if (dsu.unir(a.u, a.v)) {
            costoTotal += a.peso;
            mstSalida.push_back(a);
            if (static_cast<int>(mstSalida.size()) == V - 1) break;
        }
    }
    return costoTotal;
}

int main() {
    std::vector<AristaKruskal> redFibra = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}
    };
    std::vector<AristaKruskal> mst;
    int costo = kruskalMST(4, redFibra, mst);
    std::cout << "Costo total del Arbol de Expansion Minima (MST): " << costo << "\n"; // 4 + 5 + 10 = 19
    return 0;
}
