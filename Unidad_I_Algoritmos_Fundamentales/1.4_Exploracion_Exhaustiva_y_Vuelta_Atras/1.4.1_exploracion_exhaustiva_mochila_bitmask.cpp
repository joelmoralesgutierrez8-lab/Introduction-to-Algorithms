/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           1.4.1 - Exploración exhaustiva
 * Caso Práctico:     Exploración exhaustiva (Problema de la Mochila 0/1 con máscara de bits)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Biyección entre enteros y el conjunto potencia P(S): Cada entero mascara \in [0, 2^n - 1] codifica en binario un subconjunto único de los n objetos. El operador a nivel de bits (mascara \& (1LL << i)) determina en Theta(1) si el objeto i pertenece al candidato actual.
 *   - Cota de viabilidad computacional: Al ejecutar n iteraciones por cada una de las 2^n máscaras, su costo es exactamente Theta(n\cdot2^n) con espacio auxiliar Theta(n), siendo factible en tiempos sub-segundo para n <= 22.
 * ============================================================================
 */

#include <iostream>
#include <vector>

struct Objeto { int peso; int valor; };

// Exploracion Exhaustiva O(n * 2^n): Evalua los 2^n subconjuntos del conjunto potencia
int mochilaExhaustiva(const std::vector<Objeto>& objs, int capacidadMax, std::vector<int>& mejorSeleccion) {
    int n = static_cast<int>(objs.size());
    long long totalSubconjuntos = 1LL << n; // 2^n configuraciones
    int maxValor = 0;

    for (long long mascara = 0; mascara < totalSubconjuntos; ++mascara) {
        int pesoActual = 0, valorActual = 0;
        std::vector<int> actual;
        for (int i = 0; i < n; ++i) {
            if (mascara & (1LL << i)) { // Verifica si el bit i-esimo esta activo
                pesoActual += objs[i].peso;
                valorActual += objs[i].valor;
                actual.push_back(i);
            }
        }
        if (pesoActual <= capacidadMax && valorActual > maxValor) {
            maxValor = valorActual;
            mejorSeleccion = actual;
        }
    }
    return maxValor;
}

int main() {
    std::vector<Objeto> items = {{2, 30}, {3, 40}, {4, 50}, {5, 60}};
    std::vector<int> seleccion;
    int optimo = mochilaExhaustiva(items, 8, seleccion);
    std::cout << "Valor optimo Mochila (Cap=8): " << optimo << " con objetos: ";
    for (int idx : seleccion) std::cout << idx << " ";
    std::cout << "\n";
    return 0;
}
