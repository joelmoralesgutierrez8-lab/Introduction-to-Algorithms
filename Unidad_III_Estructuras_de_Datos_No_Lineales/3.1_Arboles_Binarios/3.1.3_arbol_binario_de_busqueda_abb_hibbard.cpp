/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           3.1.3 - Árbol binario de búsqueda
 * Caso Práctico:     Árbol Binario de Búsqueda ABB / BST (Inserción, búsqueda y borrado de Hibbard)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Preservación del invariante en el Caso 3 de Hibbard: El sucesor inorden s = encontrarMinimo(r->der) es estrictamente mayor que todo el subárbol izquierdo de r y menor que cualquier otro nodo restante en el subárbol derecho de r. Por tanto, sustituir r->clave por s->clave preserva el invariante global de búsqueda binaria en O(h).
 * ============================================================================
 */

#include <iostream>

template <typename T>
class ArbolBinarioBusqueda {
private:
    struct Nodo {
        T clave;
        Nodo* izq = nullptr;
        Nodo* der = nullptr;
        explicit Nodo(const T& k) : clave(k) {}
    };
    Nodo* raiz_ = nullptr;

    Nodo* insertarRec(Nodo* r, const T& k) {
        if (!r) return new Nodo(k);
        if (k < r->clave)      r->izq = insertarRec(r->izq, k);
        else if (k > r->clave) r->der = insertarRec(r->der, k);
        return r;
    }

    Nodo* encontrarMinimo(Nodo* r) const {
        while (r && r->izq != nullptr) r = r->izq;
        return r;
    }

    Nodo* eliminarRec(Nodo* r, const T& k) {
        if (!r) return nullptr;
        if (k < r->clave) {
            r->izq = eliminarRec(r->izq, k);
        } else if (k > r->clave) {
            r->der = eliminarRec(r->der, k);
        } else {
            // Caso 1 y Caso 2: Cero o un solo hijo
            if (!r->izq) {
                Nodo* temp = r->der;
                delete r;
                return temp;
            }
            if (!r->der) {
                Nodo* temp = r->izq;
                delete r;
                return temp;
            }
            // Caso 3: Dos hijos -> Reemplazar por el Sucesor Inorden (minimo del subarbol derecho)
            Nodo* sucesor = encontrarMinimo(r->der);
            r->clave = sucesor->clave;
            r->der = eliminarRec(r->der, sucesor->clave);
        }
        return r;
    }

    void inordenRec(const Nodo* r) const {
        if (!r) return;
        inordenRec(r->izq);
        std::cout << r->clave << " ";
        inordenRec(r->der);
    }

public:
    void insertar(const T& k) { raiz_ = insertarRec(raiz_, k); }
    void eliminar(const T& k) { raiz_ = eliminarRec(raiz_, k); }
    bool buscar(const T& k) const {
        Nodo* actual = raiz_;
        while (actual) {
            if (k == actual->clave) return true;
            actual = (k < actual->clave) ? actual->izq : actual->der;
        }
        return false;
    }
    void imprimirOrdenado() const { inordenRec(raiz_); std::cout << "\n"; }
};

int main() {
    ArbolBinarioBusqueda<int> abb;
    for (int x : {50, 30, 70, 20, 40, 60, 80}) abb.insertar(x);
    abb.eliminar(50); // Elimina la raiz con dos hijos (promueve al sucesor inorden 60)
    abb.imprimirOrdenado(); // 20 30 40 60 70 80
    return 0;
}
