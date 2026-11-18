/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           2.4.2 - Función hash
 * Caso Práctico:     Función hash (Multiplicación de Fibonacci, Polinomial de Horner y Universal)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - 4. Hashing Universal (Carter \& Wegman): Elige aleatoriamente la función hash al inicio de la ejecución dentro de la familia H_\{p,m\} = \{ h_\{a,b\}(k) = ((a\cdotk + b) mod p) mod m : a \in [1, p-1], b \in [0, p-1] \}, garantizando que para cualquier par de claves distintas la probabilidad de colisión sea <= 1/m incluso frente a entradas adversarias.
 *   - Desplazamiento de bits en Fibonacci Hashing: Al multiplicar clave por MULTIPLICADOR_AUREO en aritmética modular de 64 bits, los bits más significativos del producto mezclan todos los bits de entrada; el desplazamiento >> (64 - bitsSalida) extrae el índice en 2 ciclos de reloj sin usar la costosa instrucción de división entera.
 *   - Sensibilidad al orden en hashPolinomialCadena: A diferencia de sumar códigos ASCII (donde los anagramas 'ROMA' y 'AMOR' colisionan siempre), el esquema de Horner pondera cada posición por potencias de 131, erradicando colisiones por permutación de caracteres.
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <cstdint>

// 1. Hashing de Multiplicacion de Fibonacci (Knuth) para claves enteras de 64 bits
std::size_t hashFibonacci64(uint64_t clave, std::size_t bitsSalida) {
    // 2^64 / phi = 11400714819323198485ULL
    constexpr uint64_t MULTIPLICADOR_AUREO = 11400714819323198485ULL;
    return static_cast<std::size_t>((clave * MULTIPLICADOR_AUREO) >> (64 - bitsSalida));
}

// 2. Hashing Polinomial (Regla de Horner con primo 131) para cadenas std::string
std::size_t hashPolinomialCadena(const std::string& s, std::size_t m) {
    uint64_t acumulador = 0;
    constexpr uint64_t BASE_PRIMA = 131;
    for (unsigned char c : s) {
        acumulador = (acumulador * BASE_PRIMA + c) % m;
    }
    return static_cast<std::size_t>(acumulador);
}

// 3. Hashing Universal h_{a,b}(k) = ((a*k + b) mod p) mod m (Primo de Mersenne p = 2^31 - 1)
std::size_t hashUniversal(uint64_t k, uint64_t a, uint64_t b, std::size_t m) {
    constexpr uint64_t PRIMO_MERSENNE = 2147483647ULL; // 2^31 - 1
    return static_cast<std::size_t>(((a * k + b) % PRIMO_MERSENNE) % m);
}

int main() {
    std::cout << "Fibonacci Hash (clave=20261117, m=1024): " << hashFibonacci64(20261117ULL, 10) << "\n";
    std::cout << "Polinomial Hash ('ESCOM-IPN', m=997)   : " << hashPolinomialCadena("ESCOM-IPN", 997) << "\n";
    std::cout << "Universal Hash (clave=42, m=997)       : " << hashUniversal(42, 314159, 271828, 997) << "\n";
    return 0;
}
