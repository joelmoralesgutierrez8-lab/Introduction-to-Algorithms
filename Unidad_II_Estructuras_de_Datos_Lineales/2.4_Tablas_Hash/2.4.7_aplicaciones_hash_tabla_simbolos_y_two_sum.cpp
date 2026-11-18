/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           2.4.7 - Implementaciones y aplicaciones
 * Caso Práctico:     Aplicaciones de Tablas Hash (Tabla de símbolos de compilador y Two-Sum en O(n))
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Árbol Binario Lleno (Full / Proper Binary Tree): Todo nodo interno posee exactamente 0 o 2 hijos. Satisface el invariante fundamental L = I + 1 (el número de hojas L excede exactamente en 1 al número de nodos internos I).
 *   - Árbol Binario Perfecto (Perfect Binary Tree): Todas las hojas se sitúan al mismo nivel h y todo nodo interno tiene grado 2. Cuenta exactamente con n = 2\textasciicircum{}(h+1) - 1 nodos totales y 2\textasciicircum{}h hojas, por lo que su altura es h = \lfloorlog_2 n\rfloor.
 *   - Árbol Binario Completo (Complete Binary Tree): Todos los niveles están completamente llenos salvo posiblemente el último nivel h, cuyos nodos se agrupan de manera contigua de izquierda a derecha sin huecos intermedios.
 * ============================================================================
 */

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

struct SimboloCompilador {
    std::string tipoDato;
    int ambitoLexico;
    std::size_t desplazamientoMemoria;
};

// Aplicacion Algoritmica: Resolver 2-Sum en Theta(n) usando Tabla Hash (frente a Theta(n^2) por fuerza bruta)
std::pair<int, int> encontrarParSuma(const std::vector<int>& A, int objetivo) {
    std::unordered_map<int, int> vistoEnIndice; // Mapea: valor -> indice donde aparecio
    vistoEnIndice.reserve(A.size());            // Pre-asigna cubetas evitando rehashes intermedios

    for (int i = 0; i < static_cast<int>(A.size()); ++i) {
        int complemento = objetivo - A[i];
        auto it = vistoEnIndice.find(complemento); // Consulta en tiempo esperado Theta(1)
        if (it != vistoEnIndice.end()) {
            return {it->second, i};
        }
        vistoEnIndice[A[i]] = i;
    }
    return {-1, -1};
}

int main() {
    std::unordered_map<std::string, SimboloCompilador> tablaSimbolos;
    tablaSimbolos["contador_global"] = {"int64_t", 0, 0x0010};
    tablaSimbolos["tasa_aprendizaje"] = {"double", 1, 0x0018};

    std::cout << "Simbolo 'tasa_aprendizaje' -> Tipo: "
              << tablaSimbolos["tasa_aprendizaje"].tipoDato << "\n";

    std::vector<int> nums = {2, 7, 11, 15};
    auto [i, j] = encontrarParSuma(nums, 18);
    std::cout << "Indices que suman 18: [" << i << ", " << j << "]\n"; // [1, 2] (7 + 11 = 18)
    return 0;
}
