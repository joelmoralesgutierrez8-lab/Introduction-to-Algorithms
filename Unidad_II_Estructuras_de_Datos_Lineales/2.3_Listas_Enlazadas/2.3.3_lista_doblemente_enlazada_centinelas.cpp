/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           2.3.3 - Listas doblemente enlazadas
 * Caso Práctico:     Listas doblemente enlazadas (Nodos centinela Header & Trailer en O(1))
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Simetría estructural con centinelas cabeza\_ y cola\_: Todo nodo real queda siempre encerrado entre dos nodos válidos (predecesor y sucesor). Gracias a ello, insertarAntesDe y eliminarNodo carecen por completo de instrucciones if (p == nullptr), ejecutando 4 y 2 asignaciones de punteros respectivamente en Theta(1).
 * ============================================================================
 */

#include <iostream>

template <typename T>
class ListaDobleCentinela {
public:
    struct Nodo {
        T dato;
        Nodo* anterior;
        Nodo* siguiente;
        Nodo(const T& d = T{}, Nodo* ant = nullptr, Nodo* sig = nullptr)
            : dato(d), anterior(ant), siguiente(sig) {}
    };

private:
    Nodo* cabeza_; // Centinela izquierdo (Header Dummy)
    Nodo* cola_;   // Centinela derecho  (Trailer Dummy)
    std::size_t n_ = 0;

    // Inserta un nuevo nodo con valor x inmediatamente antes del nodo 'sucesor' en Theta(1)
    Nodo* insertarAntesDe(Nodo* sucesor, const T& x) {
        Nodo* predecesor = sucesor->anterior;
        Nodo* nuevo = new Nodo(x, predecesor, sucesor);
        predecesor->siguiente = nuevo;
        sucesor->anterior = nuevo;
        ++n_;
        return nuevo;
    }

public:
    ListaDobleCentinela() {
        cabeza_ = new Nodo();
        cola_ = new Nodo();
        cabeza_->siguiente = cola_;
        cola_->anterior = cabeza_;
    }

    ~ListaDobleCentinela() {
        while (cabeza_->siguiente != cola_) eliminarNodo(cabeza_->siguiente);
        delete cabeza_;
        delete cola_;
    }

    Nodo* pushFront(const T& x) { return insertarAntesDe(cabeza_->siguiente, x); }
    Nodo* pushBack(const T& x)  { return insertarAntesDe(cola_, x); }

    // Eliminacion directa de cualquier nodo en Theta(1) sin buscar su predecesor
    void eliminarNodo(Nodo* p) {
        p->anterior->siguiente = p->siguiente;
        p->siguiente->anterior = p->anterior;
        delete p;
        --n_;
    }

    void imprimirAdelanteYAtras() const {
        std::cout << "Adelante: ";
        for (Nodo* p = cabeza_->siguiente; p != cola_; p = p->siguiente) std::cout << p->dato << " ";
        std::cout << "| Atras: ";
        for (Nodo* p = cola_->anterior; p != cabeza_; p = p->anterior) std::cout << p->dato << " ";
        std::cout << "\n";
    }
};

int main() {
    ListaDobleCentinela<int> dl;
    dl.pushBack(100);
    auto* n2 = dl.pushBack(200);
    dl.pushBack(300);
    dl.eliminarNodo(n2); // Elimina el 200 directamente en Theta(1) usando su puntero
    dl.imprimirAdelanteYAtras();
    return 0;
}
