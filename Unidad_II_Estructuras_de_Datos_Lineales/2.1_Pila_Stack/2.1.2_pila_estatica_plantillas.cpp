/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           2.1.2 - Implementación estática
 * Caso Práctico:     Implementación estática de Pila (Fixed-Capacity Stack con Templates)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Asignación contigua sin heap (std::array<T, Capacidad>): El bloque de memoria de tamaño Capacidad * sizeof(T) se aloja directamente en el segmento de pila o datos sin invocar new/malloc, garantizando latencia determinista Theta(1).
 *   - Control de estados límite mediante excepciones estándar: Valida rigurosamente las precondiciones lanzando std::overflow_error ante desbordamiento de capacidad y std::underflow_error ante subdesbordamiento en pilas vacías.
 * ============================================================================
 */

#include <iostream>
#include <stdexcept>
#include <array>

template <typename T, std::size_t Capacidad>
class PilaEstatica {
private:
    std::array<T, Capacidad> datos_;
    int tope_ = -1; // -1 indica estado vacio en indexacion base 0

public:
    PilaEstatica() = default;

    bool estaVacia() const noexcept { return tope_ == -1; }
    bool estaLlena() const noexcept { return tope_ == static_cast<int>(Capacidad) - 1; }
    std::size_t tamano() const noexcept { return static_cast<std::size_t>(tope_ + 1); }

    void push(const T& x) {
        if (estaLlena()) {
            throw std::overflow_error("Stack Overflow: Capacidad estatica maxima alcanzada");
        }
        datos_[++tope_] = x; // Pre-incremento e insercion directa en Theta(1)
    }

    void pop() {
        if (estaVacia()) {
            throw std::underflow_error("Stack Underflow: Intento de pop sobre pila vacia");
        }
        --tope_; // Eliminacion logica en Theta(1) sin necesidad de borrar memoria fisica
    }

    const T& top() const {
        if (estaVacia()) {
            throw std::underflow_error("Stack Underflow: Intento de top sobre pila vacia");
        }
        return datos_[tope_];
    }
};

int main() {
    PilaEstatica<int, 5> pila;
    pila.push(10); pila.push(20); pila.push(30);
    std::cout << "Cima actual: " << pila.top() << " (Tamano: " << pila.tamano() << ")\n";
    pila.pop();
    std::cout << "Cima tras pop: " << pila.top() << "\n";
    return 0;
}
