/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           1.1.3 - Abstracción y tipo de dato abstracto
 * Caso Práctico:     Abstracción y Tipo de Dato Abstracto (TDA Conjunto Finito con Templates)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Encapsulamiento y ocultamiento de información: El atributo privado elementos_ oculta la estructura de datos física. Si posteriormente se sustituye std::vector<T> por un Árbol Rojo-Negro, el código cliente en main() permanece intacto.
 *   - Parametrización genérica (template <typename T>): Permite instanciar el TDA para cualquier tipo T que defina el operador relacional menor que (<).
 *   - Invariante de representación: El método insertar utiliza std::lower_bound para ubicar la posición exacta en O(log n) y verifica que el elemento no exista previamente, manteniendo el contenedor estrictamente ordenado y sin duplicados.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Especificacion Generica del TDA Conjunto<T> con Ocultamiento de Informacion
template <typename T>
class ConjuntoTDA {
private:
    // Implementacion privada (Caja Negra): Vector dinamico mantenido en orden estricto
    std::vector<T> elementos_;

public:
    ConjuntoTDA() = default;

    // Operacion Pertenece(x): Busqueda binaria en O(log n) gracias al invariante de orden
    bool pertenece(const T& x) const {
        return std::binary_search(elementos_.begin(), elementos_.end(), x);
    }

    // Operacion Insertar(x): Preserva unicidad y orden en O(n)
    void insertar(const T& x) {
        auto it = std::lower_bound(elementos_.begin(), elementos_.end(), x);
        if (it == elementos_.end() || *it != x) {
            elementos_.insert(it, x);
        }
    }

    // Operacion Union Matematica (A U B) en tiempo lineal O(|A| + |B|)
    ConjuntoTDA<T> unirCon(const ConjuntoTDA<T>& otro) const {
        ConjuntoTDA<T> resultado;
        std::set_union(elementos_.begin(), elementos_.end(),
                       otro.elementos_.begin(), otro.elementos_.end(),
                       std::back_inserter(resultado.elementos_));
        return resultado;
    }

    size_t cardinalidad() const { return elementos_.size(); }
    void imprimir() const {
        std::cout << "{ ";
        for (const auto& e : elementos_) std::cout << e << " ";
        std::cout << "}\n";
    }
};

int main() {
    ConjuntoTDA<int> A, B;
    A.insertar(10); A.insertar(5); A.insertar(20); A.insertar(10); // 10 no se duplica
    B.insertar(15); B.insertar(5); B.insertar(30);
    ConjuntoTDA<int> C = A.unirCon(B);
    C.imprimir(); // Salida ordenada: { 5 10 15 20 30 }
    return 0;
}
