/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           1.4.2 - Programación por vuelta atrás
 * Caso Práctico:     Programación por vuelta atrás / Backtracking (N-Reinas con poda en O(1))
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Esquema Anotar-Ensayar-Deshacer con Poda O(1): En lugar de recorrer las filas previas en O(N) para verificar ataques, utiliza tres arreglos booleanos indexados por las invariantes geométricas de las diagonales: fila - col + (N - 1) para diagonales principales y fila + col para diagonales secundarias.
 *   - Restauración exacta del estado: Tras retornar de backtrack(fila + 1), la línea de vuelta atrás restablece en false las tres banderas exactamente al estado previo antes de probar la siguiente columna col + 1.
 * ============================================================================
 */

#include <iostream>
#include <vector>

class SolucionadorNReinas {
private:
    int N_;
    int totalSoluciones_ = 0;
    std::vector<int> reinaEnFila_;     // reinaEnFila_[fila] = columna colocada
    std::vector<bool> colOcupada_;     // Restriccion de columna
    std::vector<bool> diagPrincipal_;  // fila - col + (N - 1) constante
    std::vector<bool> diagSecundaria_; // fila + col constante

    void backtrack(int fila) {
        if (fila == N_) { // Caso base: Tupla completa valida <x_0, ..., x_{N-1}>
            ++totalSoluciones_;
            return;
        }
        for (int col = 0; col < N_; ++col) {
            int d1 = fila - col + (N_ - 1);
            int d2 = fila + col;
            // Funcion de Poda en tiempo constante O(1)
            if (!colOcupada_[col] && !diagPrincipal_[d1] && !diagSecundaria_[d2]) {
                // 1. Anotar paso
                reinaEnFila_[fila] = col;
                colOcupada_[col] = diagPrincipal_[d1] = diagSecundaria_[d2] = true;

                // 2. Ensayar siguiente nivel recursivamente
                backtrack(fila + 1);

                // 3. Deshacer paso (Vuelta Atras / Backtrack)
                colOcupada_[col] = diagPrincipal_[d1] = diagSecundaria_[d2] = false;
            }
        }
    }

public:
    explicit SolucionadorNReinas(int n)
        : N_(n), reinaEnFila_(n, -1), colOcupada_(n, false),
          diagPrincipal_(2 * n - 1, false), diagSecundaria_(2 * n - 1, false) {}

    int resolver() {
        totalSoluciones_ = 0;
        backtrack(0);
        return totalSoluciones_;
    }
};

int main() {
    SolucionadorNReinas ochoReinas(8);
    std::cout << "Soluciones exactas para 8-Reinas: " << ochoReinas.resolver() << "\n"; // 92 soluciones
    return 0;
}
