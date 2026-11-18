/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           1.1.1 - Características de los algoritmos y tipos
 * Caso Práctico:     Características de los algoritmos y tipos (Algoritmo de Euclides MCD)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Invariante matemático e identidad de Euclides: Ambas funciones implementan la identidad mcd(a, b) = mcd(b, a mod b). Dado que en cada dos pasos el operando se reduce al menos a la mitad, el número de divisiones está acotado por el Teorema de Lamé en O(log(min(a, b))).
 *   - Eficiencia espacial en mcdIterativo: Reutiliza los registros escalares a, b y residuo dentro de un único marco de activación, logrando memoria auxiliar estricta Theta(1).
 *   - Recursión de cola en mcdRecursivo: La llamada recursiva es la última operación evaluada antes del retorno (tail call). Con optimización de compilador (-O2), el compilador transforma esta llamada en un salto iterativo evitando el consumo de O(log n) marcos en el Call Stack.
 * ============================================================================
 */

#include <iostream>
#include <stdexcept>

// 1. Implementacion Iterativa: Complejidad Temporal O(log(min(a,b))), Espacial O(1)
long long mcdIterativo(long long a, long long b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        long long residuo = a % b;
        a = b;
        b = residuo;
    }
    return a;
}

// 2. Implementacion Recursiva: Complejidad Temporal O(log(min(a,b))), Espacial O(log(min(a,b)))
long long mcdRecursivo(long long a, long long b) {
    a = std::abs(a);
    b = std::abs(b);
    if (b == 0) {
        return a; // Caso base que garantiza la propiedad de finitud
    }
    return mcdRecursivo(b, a % b); // Paso recursivo (Tail Recursion)
}

int main() {
    long long x = 1071, y = 462;
    std::cout << "MCD Iterativo (" << x << ", " << y << ") = " << mcdIterativo(x, y) << "\n";
    std::cout << "MCD Recursivo (" << x << ", " << y << ") = " << mcdRecursivo(x, y) << "\n";
    return 0;
}
