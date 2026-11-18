/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           1.2.3 - Ordenamiento de burbuja
 * Caso Práctico:     Ordenamiento de burbuja (Bubble Sort optimizado y Cocktail Shaker Sort)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Optimización por frontera de último intercambio (ultimoSwap): Supera a la bandera booleana tradicional porque si los últimos k elementos del arreglo ya estaban ordenados, acorta inmediatamente el límite superior n a ultimoSwap en una sola pasada en lugar de decrementar n de uno en uno.
 *   - Asimetría de liebres y tortugas: En Bubble Sort unidireccional, un valor grande al inicio ('liebre') viaja hasta el final en una sola pasada, pero un valor pequeño al final ('tortuga') solo retrocede una casilla por pasada. Cocktail Shaker Sort elimina esta asimetría alternando barridos izquierda-derecha y derecha-izquierda.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <utility>

// 1. Bubble Sort con memoria del ultimo indice intercambiado: Mejor caso Theta(n), Peor caso Theta(n^2)
template <typename T>
void bubbleSortOptimizado(std::vector<T>& A) {
    int n = static_cast<int>(A.size());
    while (n > 1) {
        int ultimoSwap = 0; // Registra la frontera exacta donde ocurrio el ultimo intercambio
        for (int j = 0; j < n - 1; ++j) {
            if (A[j] > A[j + 1]) {
                std::swap(A[j], A[j + 1]);
                ultimoSwap = j + 1;
            }
        }
        // Todo elemento a partir de ultimoSwap ya esta en su posicion final definitiva
        n = ultimoSwap;
    }
}

// 2. Cocktail Shaker Sort (Bidireccional): Corrige la asimetria de elementos "tortuga"
template <typename T>
void cocktailShakerSort(std::vector<T>& A) {
    int inicio = 0;
    int fin = static_cast<int>(A.size()) - 1;
    bool intercambiado = true;

    while (intercambiado) {
        intercambiado = false;
        for (int i = inicio; i < fin; ++i) {
            if (A[i] > A[i + 1]) {
                std::swap(A[i], A[i + 1]);
                intercambiado = true;
            }
        }
        if (!intercambiado) break;
        intercambiado = false;
        --fin;
        for (int i = fin - 1; i >= inicio; --i) {
            if (A[i] > A[i + 1]) {
                std::swap(A[i], A[i + 1]);
                intercambiado = true;
            }
        }
        ++inicio;
    }
}

int main() {
    std::vector<int> v = {5, 1, 4, 2, 8, 9, 10};
    bubbleSortOptimizado(v);
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";
    return 0;
}
