/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           2.3.4 - Listas circulares
 * Caso Práctico:     Listas circulares (Puntero a cola y problema de Flavio Josefo)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Doble acceso en $\Theta$(1) mediante puntero único cola\_: Mantener la referencia en cola_ en vez de cabeza_ ofrece acceso instantáneo tanto al final (cola_) como al inicio (cola_->siguiente), permitiendo insertar al frente o al fondo en Theta(1) sin recorrer el anillo.
 * ============================================================================
 */

#include <iostream>

template <typename T>
class ListaCircular {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        explicit Nodo(const T& d) : dato(d), siguiente(nullptr) {}
    };
    Nodo* cola_ = nullptr; // cola_->siguiente es siempre la cabeza de la lista circular
    std::size_t n_ = 0;

public:
    ~ListaCircular() {
        if (!cola_) return;
        Nodo* actual = cola_->siguiente;
        cola_->siguiente = nullptr; // Rompe el ciclo para liberar linealmente
        while (actual) {
            Nodo* t = actual;
            actual = actual->siguiente;
            delete t;
        }
    }

    void insertarFinal(const T& x) {
        Nodo* nuevo = new Nodo(x);
        if (!cola_) {
            nuevo->siguiente = nuevo; // Auto-referencia inicial de anillo de 1 nodo
            cola_ = nuevo;
        } else {
            nuevo->siguiente = cola_->siguiente; // Apunta a la antigua cabeza
            cola_->siguiente = nuevo;            // El antiguo ultimo apunta al nuevo
            cola_ = nuevo;                       // El nuevo pasa a ser la cola
        }
        ++n_;
    }

    // Simulacion del problema de Josefo: elimina cada k-esimo nodo hasta quedar 1 superviviente
    T resolverJosefo(int pasoK) {
        Nodo* prev = cola_;
        Nodo* actual = cola_->siguiente;
        while (n_ > 1) {
            for (int c = 1; c < pasoK; ++c) {
                prev = actual;
                actual = actual->siguiente;
            }
            prev->siguiente = actual->siguiente;
            if (actual == cola_) cola_ = prev;
            delete actual;
            actual = prev->siguiente;
            --n_;
        }
        return cola_->dato;
    }
};

int main() {
    ListaCircular<int> circulo;
    for (int i = 1; i <= 7; ++i) circulo.insertarFinal(i);
    std::cout << "Superviviente de Josefo (N=7, K=3): " << circulo.resolverJosefo(3) << "\n"; // 4
    return 0;
}
