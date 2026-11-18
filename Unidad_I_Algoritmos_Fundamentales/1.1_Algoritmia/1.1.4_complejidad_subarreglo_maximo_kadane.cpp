/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           1.1.4 - Orden de complejidad O() de un algoritmo
 * Caso Práctico:     Orden de complejidad O() (Fuerza Bruta O(n^2) vs Kadane O(n))
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Estabilidad: Un algoritmo de ordenamiento es estable si para todo par de registros con claves idénticas (k(a_i) = k(a_j)) donde i < j en la entrada, a_i precede a a_j en la permutación de salida.
 *   - Operación en Sitio (In-Place): Un algoritmo es in-place si transforma la secuencia original empleando únicamente O(1) —o a lo sumo O(log n) para la pila de recursión— de memoria adicional fuera del contenedor de entrada.
 *   - Adaptatividad: Un algoritmo es adaptativo si aprovecha el orden parcial preexistente (medido por el número de inversiones Inv(A)) para reducir su tiempo de ejecución hacia O(n).
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

// Enfoque 1: Fuerza Bruta Cuadratica Theta(n^2) - Dos bucles anidados (Regla del Producto)
long long maxSubarregloCuadratico(const std::vector<int>& A) {
    long long mejorSuma = std::numeric_limits<long long>::min();
    int n = static_cast<int>(A.size());
    for (int i = 0; i < n; ++i) {
        long long sumaActual = 0;
        for (int j = i; j < n; ++j) {
            sumaActual += A[j];
            mejorSuma = std::max(mejorSuma, sumaActual);
        }
    }
    return mejorSuma;
}

// Enfoque 2: Algoritmo de Kadane Theta(n) - Un unico recorrido lineal con programacion dinamica O(1)
long long maxSubarregloKadane(const std::vector<int>& A) {
    long long mejorGlobal = A[0];
    long long mejorTerminandoAqui = A[0];
    for (size_t i = 1; i < A.size(); ++i) {
        mejorTerminandoAqui = std::max(static_cast<long long>(A[i]), mejorTerminandoAqui + A[i]);
        mejorGlobal = std::max(mejorGlobal, mejorTerminandoAqui);
    }
    return mejorGlobal;
}

int main() {
    std::vector<int> datos = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << "Suma maxima O(n^2): " << maxSubarregloCuadratico(datos) << "\n";
    std::cout << "Suma maxima O(n)  : " << maxSubarregloKadane(datos) << "\n"; // Resultado: 6 ([4, -1, 2, 1])
    return 0;
}
