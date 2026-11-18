/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           1.2.2 - Ordenamiento por selección
 * Caso Práctico:     Ordenamiento por selección (Selection Sort con conteo de escrituras)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Insensibilidad a la distribución de entrada: El bucle interno evalúa invariablemente n - 1 - i comparaciones en la pasada i, acumulando exactamente n(n - 1)/2 = Theta(n^2) comparaciones tanto en el mejor, promedio como peor caso.
 *   - Optimalidad en escrituras de memoria: Dado que std::swap se invoca fuera del bucle interno a lo sumo n - 1 veces, Selection Sort realiza O(n) escrituras físicas en memoria, superando a Insertion Sort y Bubble Sort (que realizan Theta(n^2) escrituras en el peor caso).
 *   - Inestabilidad por intercambios a distancia: Al intercambiar A[i] con A[minIdx], si existe otro elemento idéntico a A[i] en una posición k (con i < k < minIdx), el elemento original A[i] salta más allá de k, rompiendo el orden relativo original.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <utility>

template <typename T>
size_t selectionSort(std::vector<T>& A) {
    int n = static_cast<int>(A.size());
    size_t numIntercambios = 0;

    // Invariante: A[0..i-1] contiene los i elementos mas pequenos en su posicion final
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (A[j] < A[minIdx]) {
                minIdx = j;
            }
        }
        // Solo escribe en memoria si el minimo no se encuentra ya en la posicion i
        if (minIdx != i) {
            std::swap(A[i], A[minIdx]);
            ++numIntercambios;
        }
    }
    return numIntercambios;
}

int main() {
    std::vector<int> v = {64, 25, 12, 22, 11};
    size_t swaps = selectionSort(v);
    std::cout << "Arreglo ordenado (" << swaps << " intercambios): ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";
    return 0;
}
