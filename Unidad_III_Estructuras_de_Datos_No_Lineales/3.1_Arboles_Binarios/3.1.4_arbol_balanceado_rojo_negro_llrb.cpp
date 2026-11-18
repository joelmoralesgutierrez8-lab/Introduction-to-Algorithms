/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           3.1.4 - Árbol balanceado rojo-negro
 * Caso Práctico:     Árbol balanceado Rojo-Negro (Variante LLRB de Sedgewick con rotaciones O(1))
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - 4. Propiedad Roja (Sin Rojos Adyacentes): Si un nodo es ROJO, entonces sus dos hijos son obligatoriamente NEGROS (no pueden existir dos nodos rojos consecutivos en ningún camino).
 *   - 5. Propiedad de Altura Negra (Black-Height): Para cada nodo u, todos los caminos simples desde u hasta cualquier hoja descendiente NIL contienen exactamente el mismo número de nodos negros, denotado bh(u).
 *   - Mecanismo de las rotaciones locales en $\Theta$(1): rotarIzquierda y rotarDerecha reasignan únicamente tres punteros sin alterar el recorrido Inorden del árbol. Al insertar 15 claves en orden estrictamente creciente (el peor caso para un ABB simple, que tendría altura 15), el árbol Rojo-Negro mantiene una altura perfectamente balanceada igual a 4.
 * ============================================================================
 */

#include <iostream>
#include <algorithm>

template <typename T>
class ArbolRojoNegro {
private:
    static constexpr bool ROJO = true;
    static constexpr bool NEGRO = false;

    struct Nodo {
        T clave;
        Nodo* izq = nullptr;
        Nodo* der = nullptr;
        bool color = ROJO; // Todo nodo nuevo ingresa inicialmente como ROJO
        explicit Nodo(const T& k) : clave(k) {}
    };

    Nodo* raiz_ = nullptr;

    bool esRojo(const Nodo* x) const noexcept { return x != nullptr && x->color == ROJO; }

    // Rotacion a la izquierda en Theta(1) preservando el orden Inorden
    Nodo* rotarIzquierda(Nodo* h) noexcept {
        Nodo* x = h->der;
        h->der = x->izq;
        x->izq = h;
        x->color = h->color;
        h->color = ROJO;
        return x;
    }

    // Rotacion a la derecha en Theta(1) preservando el orden Inorden
    Nodo* rotarDerecha(Nodo* h) noexcept {
        Nodo* x = h->izq;
        h->izq = x->der;
        x->der = h;
        x->color = h->color;
        h->color = ROJO;
        return x;
    }

    // Cambio de colores ( division de un 4-nodo temporal ascendente ) en Theta(1)
    void invertirColores(Nodo* h) noexcept {
        h->color = ROJO;
        h->izq->color = NEGRO;
        h->der->color = NEGRO;
    }

    Nodo* insertarRec(Nodo* h, const T& k) {
        if (!h) return new Nodo(k);
        if (k < h->clave)      h->izq = insertarRec(h->izq, k);
        else if (k > h->clave) h->der = insertarRec(h->der, k);

        // Restauracion de los invariantes Rojo-Negro en el ascenso recursivo:
        if (esRojo(h->der) && !esRojo(h->izq))     h = rotarIzquierda(h);
        if (esRojo(h->izq) && esRojo(h->izq->izq)) h = rotarDerecha(h);
        if (esRojo(h->izq) && esRojo(h->der))      invertirColores(h);
        return h;
    }

    int alturaRec(const Nodo* h) const noexcept {
        if (!h) return 0;
        return 1 + std::max(alturaRec(h->izq), alturaRec(h->der));
    }

public:
    void insertar(const T& k) {
        raiz_ = insertarRec(raiz_, k);
        raiz_->color = NEGRO; // Invariante 2: La raiz es siempre NEGRA
    }
    int altura() const noexcept { return alturaRec(raiz_); }
};

int main() {
    ArbolRojoNegro<int> rbt;
    // Insertar 1..15 en orden creciente produciria altura 15 en un ABB normal; aqui se autobalancea:
    for (int i = 1; i <= 15; ++i) rbt.insertar(i);
    std::cout << "Altura del Arbol Rojo-Negro tras insertar 1..15 en orden: " << rbt.altura() << "\n"; // 4
    return 0;
}
