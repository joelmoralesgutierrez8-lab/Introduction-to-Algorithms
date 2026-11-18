/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           1.3.1 - Búsqueda secuencial
 * Caso Práctico:     Búsqueda secuencial (Estándar y optimizada con centinela)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Técnica del centinela de Knuth: En busquedaConCentinela se almacena temporalmente el valor buscado x en A[n-1]. Esto garantiza que el ciclo while (A[i] != x) termine siempre sin necesidad de comprobar i < n en cada iteración, reduciendo a la mitad las instrucciones de salto condicional del bucle interno.
 *   - Complejidad asintótica: Mejor caso Theta(1) cuando x = A[0]; peor caso Theta(n) cuando x no existe o está al final; caso promedio (n + 1)/2 = Theta(n) bajo distribución uniforme de consultas exitosas.
 * ============================================================================
 */

#include <iostream>
#include <vector>

// 1. Busqueda Secuencial Estandar: Evalua 2 condiciones por iteracion (i < n y A[i] != x)
template <typename T>
int busquedaSecuencial(const std::vector<T>& A, const T& x) {
    int n = static_cast<int>(A.size());
    // Invariante: Para todo k en [0, i-1], A[k] != x
    for (int i = 0; i < n; ++i) {
        if (A[i] == x) return i;
    }
    return -1;
}

// 2. Busqueda con Centinela (Knuth TAOCP Vol. 3): Elimina la comparacion de limite i < n en el bucle
template <typename T>
int busquedaConCentinela(std::vector<T>& A, const T& x) {
    int n = static_cast<int>(A.size());
    if (n == 0) return -1;
    if (A[n - 1] == x) return n - 1;

    T respaldoUltimo = A[n - 1];
    A[n - 1] = x; // Coloca el centinela en la ultima posicion garantizando parada

    int i = 0;
    while (A[i] != x) { // Una sola evaluacion condicional por paso
        ++i;
    }

    A[n - 1] = respaldoUltimo; // Restaura el arreglo original
    return (i < n - 1) ? i : -1;
}

int main() {
    std::vector<int> datos = {42, 15, 8, 99, 23, 4};
    std::cout << "Indice de 99 (Estandar) : " << busquedaSecuencial(datos, 99) << "\n";
    std::cout << "Indice de 99 (Centinela): " << busquedaConCentinela(datos, 99) << "\n";
    return 0;
}
