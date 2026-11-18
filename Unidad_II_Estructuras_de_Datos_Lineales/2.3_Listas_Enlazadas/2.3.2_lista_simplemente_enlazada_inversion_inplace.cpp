/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           2.3.2 - Listas simplemente enlazadas
 * Caso Práctico:     Listas simplemente enlazadas (Inserción, eliminación e inversión In-Place)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Uso de Nodo Cabeza o Centinela (Header / Dummy Node): Colocar un nodo ficticio permanente al inicio garantiza que todo nodo de datos posea un nodo predecesor válido, eliminando las bifurcaciones condicionales especiales para el primer elemento.
 *   - Técnica de doble puntero de arrastre (previo, actual): En eliminarValor, dado que los enlaces son unidireccionales, el puntero previo conserva la dirección del nodo anterior para poder ejecutar previo->siguiente = actual->siguiente en cuanto se localiza el objetivo.
 *   - Inversión en sitio con tres punteros (invertirInPlace): Recorre la lista una sola vez invirtiendo el sentido de cada puntero siguiente sin reservar ningún nodo adicional en el heap, alcanzando complejidad temporal Theta(n) y espacial Theta(1).
 * ============================================================================
 */

#include <iostream>
#include <stdexcept>

template <typename T>
class ListaSimple {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(const T& d, Nodo* sig = nullptr) : dato(d), siguiente(sig) {}
    };
    Nodo* cabeza_ = nullptr;
    std::size_t n_ = 0;

public:
    ListaSimple() = default;
    ~ListaSimple() {
        while (cabeza_ != nullptr) {
            Nodo* temp = cabeza_;
            cabeza_ = cabeza_->siguiente;
            delete temp;
        }
    }

    void insertarInicio(const T& x) {
        cabeza_ = new Nodo(x, cabeza_); // Theta(1)
        ++n_;
    }

    void insertarFinal(const T& x) {
        Nodo* nuevo = new Nodo(x, nullptr);
        if (!cabeza_) {
            cabeza_ = nuevo;
        } else {
            Nodo* actual = cabeza_;
            while (actual->siguiente != nullptr) actual = actual->siguiente;
            actual->siguiente = nuevo; // Theta(n) sin puntero cola; Theta(1) si se mantiene puntero cola
        }
        ++n_;
    }

    bool eliminarValor(const T& x) {
        Nodo* actual = cabeza_;
        Nodo* previo = nullptr;
        while (actual != nullptr && actual->dato != x) {
            previo = actual;
            actual = actual->siguiente;
        }
        if (actual == nullptr) return false; // No encontrado
        if (previo == nullptr) cabeza_ = actual->siguiente; // Era el primer nodo
        else previo->siguiente = actual->siguiente;         // Puentea el nodo intermedio
        delete actual;
        --n_;
        return true;
    }

    // Algoritmo clasico de inversion en sitio (In-Place Reversal): Tiempo Theta(n), Espacio Auxiliar Theta(1)
    void invertirInPlace() noexcept {
        Nodo* previo = nullptr;
        Nodo* actual = cabeza_;
        while (actual != nullptr) {
            Nodo* siguienteTemp = actual->siguiente; // 1. Preserva el resto de la lista
            actual->siguiente = previo;              // 2. Invierte la flecha hacia atras
            previo = actual;                         // 3. Avanza previo
            actual = siguienteTemp;                  // 4. Avanza actual
        }
        cabeza_ = previo;
    }

    void imprimir() const {
        for (Nodo* p = cabeza_; p != nullptr; p = p->siguiente) std::cout << p->dato << " -> ";
        std::cout << "nullptr\n";
    }
};

int main() {
    ListaSimple<int> L;
    L.insertarFinal(10); L.insertarFinal(20); L.insertarFinal(30);
    L.imprimir();
    L.invertirInPlace();
    L.imprimir(); // 30 -> 20 -> 10 -> nullptr
    return 0;
}
