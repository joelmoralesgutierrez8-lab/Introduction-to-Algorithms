/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           3.1.8 - Otros tipos de árboles
 * Caso Práctico:     Otros tipos de árboles (Árbol de Prefijos / Trie para autocompletado en O(L))
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Grafo Ponderado (Weighted Graph): Asocia a cada arista e \in E un peso numérico real w(e) \in \mathbb{R} que representa costo, latencia, distancia o capacidad.
 *   - Grado de un vértice y Lema del Apretón de Manos (Euler): En un grafo no dirigido, el grado deg(u) es el número de aristas incidentes en u, satisfaciendo \sum_\{u \in V\} deg(u) = 2|E|. En un digrafo se distingue entre grado de entrada indeg(u) y grado de salida outdeg(u), cumpliéndose \sum indeg(u) = \sum outdeg(u) = |E|.
 *   - Densidad del grafo: Un grafo es disperso (sparse) si |E| = O(V) (como redes viales, eléctricas o la Web), y es denso (dense) si |E| = Theta(V^2).
 * ============================================================================
 */

#include <iostream>
#include <unordered_map>
#include <string>

class TriePrefijos {
private:
    struct NodoTrie {
        std::unordered_map<char, NodoTrie*> hijos;
        bool esFinDePalabra = false;
    };
    NodoTrie* raiz_ = new NodoTrie();

public:
    // Insercion en tiempo Theta(L), donde L es la longitud de la palabra
    void insertar(const std::string& palabra) {
        NodoTrie* actual = raiz_;
        for (char c : palabra) {
            if (actual->hijos.find(c) == actual->hijos.end()) {
                actual->hijos[c] = new NodoTrie();
            }
            actual = actual->hijos[c];
        }
        actual->esFinDePalabra = true;
    }

    bool buscarPalabraExacta(const std::string& palabra) const {
        const NodoTrie* actual = raiz_;
        for (char c : palabra) {
            auto it = actual->hijos.find(c);
            if (it == actual->hijos.end()) return false;
            actual = it->second;
        }
        return actual->esFinDePalabra;
    }

    bool existePrefijo(const std::string& prefijo) const {
        const NodoTrie* actual = raiz_;
        for (char c : prefijo) {
            auto it = actual->hijos.find(c);
            if (it == actual->hijos.end()) return false;
            actual = it->second;
        }
        return true;
    }
};

int main() {
    TriePrefijos diccionario;
    diccionario.insertar("algoritmo");
    diccionario.insertar("algebra");
    std::cout << "Prefijo 'alg' existe   : " << (diccionario.existePrefijo("alg") ? "SI" : "NO") << "\n";
    std::cout << "Palabra 'alg' completa : " << (diccionario.buscarPalabraExacta("alg") ? "SI" : "NO") << "\n";
    return 0;
}
