/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           1.1.2 - Representación de algoritmos en pseudocódigo
 * Caso Práctico:     Representación en pseudocódigo e invariantes (Regla de Horner)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - 4. Verificación mediante Invariantes de Bucle: Demostración formal de correctitud en tres etapas: Inicialización (verdadero antes de la primera iteración), Mantenimiento (si es verdadero antes de la iteración, permanece verdadero después) y Terminación (al salir del bucle implica la postcondición).
 *   - Verificación por contrato (assert): La macro assert valida en tiempo de ejecución la precondición formal del pseudocódigo (!coef.empty()), abortando si el contrato de entrada se incumple.
 *   - Reducción de complejidad aritmética: Mientras la evaluación ingenua término a término requiere Theta(n^2) multiplicaciones (o Theta(n log n) con exponenciación binaria), la factorización anidada de Horner P(x) = a_0 + x(a_1 + x(a_2 + ...)) ejecuta exactamente n multiplicaciones y n adiciones, logrando complejidad temporal óptima Theta(n) y espacial Theta(1).
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <cassert>

/*
 * Pseudocodigo Formal: HORNER(A[0..n], x)
 * Precondicion: A contiene n+1 coeficientes reales; representa P(x) = sum_{k=0}^n A[k]*x^k
 * Postcondicion: Retorna el valor exacto P(x) en Theta(n) multiplicaciones y sumas.
 * 1. resultado <- A[n]
 * 2. para i <- n - 1 downto 0 hacer
 * 3.     resultado <- resultado * x + A[i]
 * 4. retornar resultado
 */
double metodoHorner(const std::vector<double>& coef, double x) {
    assert(!coef.empty() && "Precondicion violada: el vector de coeficientes no puede estar vacio");
    int n = static_cast<int>(coef.size()) - 1;
    double resultado = coef[n];

    // Invariante de bucle: Al inicio de cada iteracion i,
    // resultado = sum_{k=0}^{n-(i+1)} coef[k + i + 1] * x^k
    for (int i = n - 1; i >= 0; --i) {
        resultado = resultado * x + coef[i];
    }
    return resultado;
}

int main() {
    // Polinomio P(x) = 2 + 3x - x^2 + 4x^3 evaluado en x = 2 -> 2 + 6 - 4 + 32 = 36
    std::vector<double> P = {2.0, 3.0, -1.0, 4.0};
    std::cout << "P(2.0) mediante Regla de Horner = " << metodoHorner(P, 2.0) << "\n";
    return 0;
}
