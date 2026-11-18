/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           2.3.7 - Implementaciones y aplicaciones
 * Caso Práctico:     Aplicaciones de Listas (Suma simbólica de polinomios dispersos en O(n+m))
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Compresión estructural de datos dispersos: Representar un polinomio de grado 1000 con solo 4 términos no nulos requiere exactamente 4 nodos enlazados en lugar de 1001 celdas contiguas. La fusión ordenada avanza dos iteradores en paralelo con complejidad óptima Theta(|P| + |Q|).
 * ============================================================================
 */

#include <iostream>
#include <list>

struct Termino {
    double coef;
    int exp;
};

using Polinomio = std::list<Termino>; // Ordenado decrecientemente por exponente

Polinomio sumarPolinomios(const Polinomio& P, const Polinomio& Q) {
    Polinomio R;
    auto itP = P.begin();
    auto itQ = Q.begin();

    while (itP != P.end() && itQ != Q.end()) {
        if (itP->exp > itQ->exp) {
            R.push_back(*itP++);
        } else if (itQ->exp > itP->exp) {
            R.push_back(*itQ++);
        } else {
            double sumaCoef = itP->coef + itQ->coef;
            if (sumaCoef != 0.0) { // Suprime terminos que se cancelan mutuamente
                R.push_back({sumaCoef, itP->exp});
            }
            ++itP; ++itQ;
        }
    }
    while (itP != P.end()) R.push_back(*itP++);
    while (itQ != Q.end()) R.push_back(*itQ++);
    return R;
}

int main() {
    // P(x) = 4x^1000 + 3x^50 - 2x + 7  (en un arreglo requeriria 1001 celdas; aqui solo 4 nodos)
    Polinomio P = {{4.0, 1000}, {3.0, 50}, {-2.0, 1}, {7.0, 0}};
    Polinomio Q = {{5.0, 1000}, {-3.0, 50}, {8.0, 2}, {1.0, 0}};
    Polinomio S = sumarPolinomios(P, Q);

    for (const auto& t : S) std::cout << "(" << t.coef << "x^" << t.exp << ") ";
    std::cout << "\n"; // (9x^1000) (8x^2) (-2x^1) (8x^0)
    return 0;
}
