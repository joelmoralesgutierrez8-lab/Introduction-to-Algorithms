/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           2.2.2 - Implementación estática
 * Caso Práctico:     Implementación estática de Cola (Cola circular / Ring Buffer en O(1))
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Aritmética modular de anillo Z\_Capacidad: La transición (indice + 1) \% Capacidad envuelve automáticamente el índice desde Capacidad - 1 hacia 0, eliminando por completo cualquier desplazamiento de elementos.
 *   - Aprovechamiento del 100\% de celdas: Al mantener el atributo contador n_, no es necesario sacrificar una casilla vacía para diferenciar cola llena de cola vacía, logrando operaciones enqueue, dequeue y front en Theta(1) estricto.
 * ============================================================================
 */

#include <iostream>
#include <array>
#include <stdexcept>

template <typename T, std::size_t Capacidad>
class ColaCircularEstatica {
private:
    std::array<T, Capacidad> buffer_;
    std::size_t frente_ = 0;
    std::size_t final_ = 0;
    std::size_t n_ = 0; // Resuelve la ambigüedad frente_ == final_ aprovechando el 100% del arreglo

public:
    ColaCircularEstatica() = default;

    bool estaVacia() const noexcept { return n_ == 0; }
    bool estaLlena() const noexcept { return n_ == Capacidad; }
    std::size_t tamano() const noexcept { return n_; }

    void enqueue(const T& x) {
        if (estaLlena()) {
            throw std::overflow_error("Queue Overflow: Buffer circular lleno");
        }
        buffer_[final_] = x;
        final_ = (final_ + 1) % Capacidad; // Avance modular en Theta(1)
        ++n_;
    }

    void dequeue() {
        if (estaVacia()) {
            throw std::underflow_error("Queue Underflow: Buffer circular vacio");
        }
        frente_ = (frente_ + 1) % Capacidad; // Avance modular del frente en Theta(1)
        --n_;
    }

    const T& front() const {
        if (estaVacia()) {
            throw std::underflow_error("Queue Underflow: Buffer circular vacio");
        }
        return buffer_[frente_];
    }
};

int main() {
    ColaCircularEstatica<int, 3> ring;
    ring.enqueue(10); ring.enqueue(20); ring.enqueue(30);
    ring.dequeue(); // Libera la casilla 0
    ring.enqueue(40); // Da la vuelta circularmente y ocupa la casilla 0
    while (!ring.estaVacia()) {
        std::cout << ring.front() << " ";
        ring.dequeue();
    }
    std::cout << "\n"; // Imprime: 20 30 40
    return 0;
}
