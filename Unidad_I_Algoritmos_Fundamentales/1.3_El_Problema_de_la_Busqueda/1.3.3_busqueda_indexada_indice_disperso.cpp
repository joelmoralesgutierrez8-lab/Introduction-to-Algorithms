/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           1.3.3 - Búsqueda indexada
 * Caso Práctico:     Búsqueda indexada (Índice disperso + búsqueda binaria de bloque)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Optimización de tamaño de bloque: Si se realiza búsqueda secuencial tanto en el índice de tamaño k = n/B como dentro del bloque de tamaño B, el costo esperado es k/2 + B/2, el cual se minimiza eligiendo B = \sqrt{}n para obtener O(\sqrt{}n). Si se aplica búsqueda binaria en ambos niveles, el costo se reduce a O(log(n/B) + log B) = O(log n).
 *   - Arquitectura en dos fases: El constructor construye un índice disperso con k = \lceiln/B\rceil entradas almacenando la clave máxima y los límites de cada bloque. Al consultar buscar(x), la Fase 1 descarta bloques completos en O(log k) sin tocar el contenedor principal.
 *   - Localidad espacial y parada temprana: La Fase 2 recorre únicamente el bloque candidato de longitud B (compatible con una línea de caché L1 o página de disco) y aborta anticipadamente si datos_[i] > x.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <cmath>

struct EntradaIndice {
    int claveMaxima;
    size_t inicioBloque;
    size_t finBloque;
};

class BuscadorIndexado {
private:
    const std::vector<int>& datos_;
    std::vector<EntradaIndice> tablaIndice_;

public:
    explicit BuscadorIndexado(const std::vector<int>& datosOrdenados, size_t tamBloque)
        : datos_(datosOrdenados) {
        size_t n = datos_.size();
        for (size_t i = 0; i < n; i += tamBloque) {
            size_t fin = std::min(i + tamBloque - 1, n - 1);
            tablaIndice_.push_back({datos_[fin], i, fin});
        }
    }

    int buscar(int x) const {
        if (datos_.empty() || x < datos_.front() || x > datos_.back()) return -1;

        // Fase 1: Busqueda binaria sobre la tabla de indices en O(log(n/B))
        int L = 0, R = static_cast<int>(tablaIndice_.size()) - 1, bloqueCandidato = -1;
        while (L <= R) {
            int m = L + (R - L) / 2;
            if (tablaIndice_[m].claveMaxima >= x) {
                bloqueCandidato = m;
                R = m - 1;
            } else {
                L = m + 1;
            }
        }
        if (bloqueCandidato == -1) return -1;

        // Fase 2: Busqueda acotada exclusivamente dentro del bloque fisico [inicioBloque .. finBloque]
        size_t ini = tablaIndice_[bloqueCandidato].inicioBloque;
        size_t fin = tablaIndice_[bloqueCandidato].finBloque;
        for (size_t i = ini; i <= fin; ++i) {
            if (datos_[i] == x) return static_cast<int>(i);
            if (datos_[i] > x)  break; // Parada temprana por orden interno del bloque
        }
        return -1;
    }
};

int main() {
    std::vector<int> archivo = {4, 8, 15, 16, 23, 42, 50, 61, 77, 84, 91, 105};
    BuscadorIndexado isam(archivo, 4); // Bloques de 4 registros
    std::cout << "Registro 61 localizado en indice: " << isam.buscar(61) << "\n";
    return 0;
}
