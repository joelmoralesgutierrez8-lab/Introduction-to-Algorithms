/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           2.2.3 - Implementación dinámica
 * Caso Práctico:     Implementación dinámica de Cola (Doble puntero frente y final)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Sincronización de punteros en estados frontera: En dequeue(), cuando se extrae el único nodo restante de la cola, frente_ pasa a ser nullptr. Es indispensable actualizar también final_ = nullptr para evitar que final_ quede como un puntero colgante (dangling pointer) hacia memoria liberada.
 * ============================================================================
 */

#include <iostream>
#include <stdexcept>

template <typename T>
class ColaDinamica {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        explicit Nodo(const T& d) : dato(d), siguiente(nullptr) {}
    };
    Nodo* frente_ = nullptr;
    Nodo* final_ = nullptr;
    std::size_t n_ = 0;

public:
    ColaDinamica() = default;
    ~ColaDinamica() { while (!estaVacia()) dequeue(); }

    ColaDinamica(const ColaDinamica&) = delete;
    ColaDinamica& operator=(const ColaDinamica&) = delete;

    bool estaVacia() const noexcept { return frente_ == nullptr; }
    std::size_t tamano() const noexcept { return n_; }

    void enqueue(const T& x) {
        Nodo* nuevo = new Nodo(x);
        if (estaVacia()) {
            frente_ = final_ = nuevo; // Caso especial: primer nodo ingresado
        } else {
            final_->siguiente = nuevo; // Enlaza al final actual en Theta(1)
            final_ = nuevo;            // Actualiza el puntero final_
        }
        ++n_;
    }

    void dequeue() {
        if (estaVacia()) {
            throw std::underflow_error("Queue Underflow: Cola dinamica vacia");
        }
        Nodo* temp = frente_;
        frente_ = frente_->siguiente;
        if (frente_ == nullptr) {
            final_ = nullptr; // Critico: si la cola quedo vacia, anular tambien final_
        }
        delete temp;
        --n_;
    }

    const T& front() const {
        if (estaVacia()) throw std::underflow_error("Cola vacia");
        return frente_->dato;
    }
};

int main() {
    ColaDinamica<std::string> spooler;
    spooler.enqueue("Reporte_Anual.pdf");
    spooler.enqueue("Tesis_IPN.docx");
    std::cout << "Imprimiendo: " << spooler.front() << "\n";
    spooler.dequeue();
    std::cout << "Siguiente  : " << spooler.front() << "\n";
    return 0;
}
