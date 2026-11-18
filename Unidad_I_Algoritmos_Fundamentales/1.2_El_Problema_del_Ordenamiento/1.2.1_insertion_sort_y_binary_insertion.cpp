/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           1.2.1 - Ordenamiento por inserción
 * Caso Práctico:     Ordenamiento por inserción (Insertion Sort y Binary Insertion Sort)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Complejidad temporal dependiente de inversiones: El bucle interno while se ejecuta exactamente tantas veces como inversiones (pares i < j con A[i] > A[j]) existan en el arreglo. En el mejor caso (arreglo ya ordenado), Inv(A) = 0 y realiza n - 1 comparaciones en tiempo Theta(n). En el peor caso (orden inverso) y caso promedio realiza n(n - 1)/2 y n(n - 1)/4 operaciones respectivamente, dando Theta(n^2).
 *   - Preservación de la estabilidad: La condición A[i] > clave detiene el desplazamiento en cuanto encuentra un elemento igual a clave, garantizando que claves duplicadas nunca se crucen.
 *   - Optimización con Binary Insertion Sort: Utiliza std::upper_bound sobre el prefijo ya ordenado para acotar las comparaciones a \sum\lceillog_2 j\rceil = Theta(n log n), ideal cuando comparar objetos complejos (p. ej. cadenas largas o registros compuestos) es mucho más costoso que mover punteros.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

// 1. Insertion Sort Clasico: Estable, In-Place O(1), Adaptativo O(n + Inv(A))
template <typename T>
void insertionSort(std::vector<T>& A) {
    int n = static_cast<int>(A.size());
    for (int j = 1; j < n; ++j) {
        T clave = A[j];
        int i = j - 1;
        // Desplaza elementos mayores hacia la derecha (comparacion estricta '>' preserva estabilidad)
        while (i >= 0 && A[i] > clave) {
            A[i + 1] = A[i];
            --i;
        }
        A[i + 1] = clave;
    }
}

// 2. Binary Insertion Sort: Reduce comparaciones a O(n log n), manteniendo desplazamientos O(n^2)
template <typename T>
void binaryInsertionSort(std::vector<T>& A) {
    for (auto it = A.begin(); it != A.end(); ++it) {
        // std::upper_bound halla en O(log j) el primer elemento estrictamente mayor que *it
        auto posInsercion = std::upper_bound(A.begin(), it, *it);
        // Rota el subrango desplazando los elementos hacia la derecha
        std::rotate(posInsercion, it, it + 1);
    }
}

int main() {
    std::vector<int> datos = {29, 10, 14, 37, 14, 13, 8};
    insertionSort(datos);
    for (int x : datos) std::cout << x << " ";
    std::cout << "\n";
    return 0;
}
