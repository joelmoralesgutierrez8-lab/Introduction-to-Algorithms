/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           2.1.3 - Implementación dinámica
 * Caso Práctico:     Implementación dinámica de Pila (Pila enlazada con memoria segura RAII)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Reconectividad de punteros en $\Theta$(1): La instrucción cima_ = new Nodo(valor, cima_) construye el nodo en el heap, enlaza su puntero siguiente hacia el nodo que antes ocupaba la cima y actualiza cima_ en una sola expresión atómica.
 *   - Principio RAII y prevención de fugas: El destructor \textasciitilde{}PilaDinamica() invoca limpiar(), recorriendo y liberando los n_ nodos dinámicos en Theta(n). Además, se bloquea el constructor de copia por defecto para impedir copias superficiales de punteros crudos.
 * ============================================================================
 */

#include <iostream>
#include <stdexcept>

template <typename T>
class PilaDinamica {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(const T& d, Nodo* sig = nullptr) : dato(d), siguiente(sig) {}
    };
    Nodo* cima_ = nullptr;
    std::size_t n_ = 0;

public:
    PilaDinamica() = default;

    // Destructor RAII: Garantiza cero fugas de memoria (Memory Leaks) al salir de ambito
    ~PilaDinamica() { limpiar(); }

    // Deshabilitar copia superficial para evitar doble liberacion (Double Free)
    PilaDinamica(const PilaDinamica&) = delete;
    PilaDinamica& operator=(const PilaDinamica&) = delete;

    bool estaVacia() const noexcept { return cima_ == nullptr; }
    std::size_t tamano() const noexcept { return n_; }

    void push(const T& valor) {
        cima_ = new Nodo(valor, cima_); // El nuevo nodo apunta a la antigua cima en Theta(1)
        ++n_;
    }

    void pop() {
        if (estaVacia()) {
            throw std::underflow_error("Stack Underflow: Pila dinamica vacia");
        }
        Nodo* nodoRemovido = cima_;
        cima_ = cima_->siguiente;
        delete nodoRemovido; // Libera el nodo extraido en el heap
        --n_;
    }

    const T& top() const {
        if (estaVacia()) {
            throw std::underflow_error("Stack Underflow: Pila dinamica vacia");
        }
        return cima_->dato;
    }

    void limpiar() noexcept {
        while (!estaVacia()) {
            Nodo* temp = cima_;
            cima_ = cima_->siguiente;
            delete temp;
        }
        n_ = 0;
    }
};

int main() {
    PilaDinamica<std::string> historial;
    historial.push("https://ipn.mx");
    historial.push("https://escom.ipn.mx");
    std::cout << "Pagina activa: " << historial.top() << "\n";
    historial.pop();
    std::cout << "Tras regresar: " << historial.top() << "\n";
    return 0;
}
