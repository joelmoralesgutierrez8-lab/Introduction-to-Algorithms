/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           1.3.2 - Búsqueda binaria
 * Caso Práctico:     Búsqueda binaria (Iterativa, recursiva y primera aparición Lower Bound)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Invariante de intervalo cerrado [L, R]: La condición L <= R asegura que el intervalo de longitud 1 (cuando L == R) sea inspeccionado antes de concluir fallo. En cada paso el tamaño del intervalo R - L + 1 disminuye estrictamente al menos a la mitad.
 *   - Determinismo ante claves duplicadas: Mientras la búsqueda binaria estándar puede devolver cualquiera de los índices donde aparece una clave repetida, busquedaPrimeraAparicion continúa acotando R = m - 1 al hallar coincidencia, garantizando localizar el índice mínimo en Theta(log n).
 * ============================================================================
 */

#include <iostream>
#include <vector>

// 1. Busqueda Binaria Iterativa: Complejidad Temporal O(log n), Espacial O(1)
template <typename T>
int busquedaBinariaIterativa(const std::vector<T>& A, const T& x) {
    int L = 0;
    int R = static_cast<int>(A.size()) - 1;
    // Invariante: Si x pertenece a A, entonces x se encuentra dentro del subrango cerrado A[L..R]
    while (L <= R) {
        int m = L + (R - L) / 2;
        if (A[m] == x) return m;
        if (x < A[m])  R = m - 1;
        else           L = m + 1;
    }
    return -1;
}

// 2. Busqueda Binaria Recursiva: Complejidad Temporal O(log n), Espacial O(log n) en pila
template <typename T>
int busquedaBinariaRecursiva(const std::vector<T>& A, const T& x, int L, int R) {
    if (L > R) return -1;
    int m = L + (R - L) / 2;
    if (A[m] == x) return m;
    if (x < A[m])  return busquedaBinariaRecursiva(A, x, L, m - 1);
    return busquedaBinariaRecursiva(A, x, m + 1, R);
}

// 3. Lower Bound: Localiza la primera posicion i tal que A[i] >= x (manejo exacto de duplicados)
template <typename T>
int busquedaPrimeraAparicion(const std::vector<T>& A, const T& x) {
    int L = 0, R = static_cast<int>(A.size()) - 1, resultado = -1;
    while (L <= R) {
        int m = L + (R - L) / 2;
        if (A[m] >= x) {
            if (A[m] == x) resultado = m;
            R = m - 1; // Sigue buscando hacia la izquierda por si existen duplicados previos
        } else {
            L = m + 1;
        }
    }
    return resultado;
}

int main() {
    std::vector<int> ordenado = {3, 7, 12, 12, 12, 19, 25, 40};
    std::cout << "Binaria Iterativa (19)    : indice " << busquedaBinariaIterativa(ordenado, 19) << "\n";
    std::cout << "Primera aparicion de (12) : indice " << busquedaPrimeraAparicion(ordenado, 12) << "\n";
    return 0;
}
