/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           3.1.2 - Recorridos en un árbol binario
 * Caso Práctico:     Recorridos en árbol binario (Preorden, Inorden, Postorden y Por Niveles BFS)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Postorden (Izquierdo – Derecho – Raíz | LRN): Recorre primero T_L, luego T_R y visita al final la raíz r. Es indispensable cuando el procesamiento del padre depende de sus hijos (liberación de memoria delete, cálculo de alturas o evaluación postfija RPN).
 *   - Recorrido en Amplitud o por Niveles (Level-Order / BFS): Visita los nodos nivel por nivel de arriba hacia abajo y de izquierda a derecha auxiliándose de una cola FIFO.
 *   - Complejidad temporal y espacial: En los cuatro recorridos cada arista se atraviesa un número constante de veces, garantizando tiempo exacto Theta(n). El espacio auxiliar en profundidad está acotado por la altura del árbol Theta(h) (donde log_2 n <= h < n), mientras que en el recorrido por niveles está acotado por el ancho máximo del árbol w <= \lceiln/2\rceil.
 * ============================================================================
 */

#include <iostream>
#include <stack>
#include <queue>

struct NodoArbol {
    int dato;
    NodoArbol* izq;
    NodoArbol* der;
    explicit NodoArbol(int d, NodoArbol* i = nullptr, NodoArbol* r = nullptr)
        : dato(d), izq(i), der(r) {}
};

// 1. Recorridos en Profundidad Recursivos: Tiempo Theta(n), Espacio Theta(h) en Call Stack
void preorden(const NodoArbol* r) {
    if (!r) return;
    std::cout << r->dato << " ";
    preorden(r->izq);
    preorden(r->der);
}

void inorden(const NodoArbol* r) {
    if (!r) return;
    inorden(r->izq);
    std::cout << r->dato << " ";
    inorden(r->der);
}

void postorden(const NodoArbol* r) {
    if (!r) return;
    postorden(r->izq);
    postorden(r->der);
    std::cout << r->dato << " ";
}

// 2. Inorden Iterativo con Pila Explicita: Evita desbordamiento de pila del sistema
void inordenIterativo(const NodoArbol* raiz) {
    std::stack<const NodoArbol*> pila;
    const NodoArbol* actual = raiz;
    while (actual != nullptr || !pila.empty()) {
        while (actual != nullptr) { // Desciende al extremo mas izquierdo apilando ancestros
            pila.push(actual);
            actual = actual->izq;
        }
        actual = pila.top();
        pila.pop();
        std::cout << actual->dato << " "; // Visita el nodo central
        actual = actual->der;             // Transiciona al subarbol derecho
    }
}

// 3. Recorrido por Niveles (Amplitud) con Cola FIFO: Tiempo Theta(n), Espacio O(w) anchura maxima
void recorridoPorNiveles(const NodoArbol* raiz) {
    if (!raiz) return;
    std::queue<const NodoArbol*> cola;
    cola.push(raiz);
    while (!cola.empty()) {
        const NodoArbol* u = cola.front();
        cola.pop();
        std::cout << u->dato << " ";
        if (u->izq) cola.push(u->izq);
        if (u->der) cola.push(u->der);
    }
}

int main() {
    auto* raiz = new NodoArbol(4,
                    new NodoArbol(2, new NodoArbol(1), new NodoArbol(3)),
                    new NodoArbol(6, new NodoArbol(5), new NodoArbol(7)));
    std::cout << "Preorden        : "; preorden(raiz); std::cout << "\n";
    std::cout << "Inorden (Iter.) : "; inordenIterativo(raiz); std::cout << "\n";
    std::cout << "Postorden       : "; postorden(raiz); std::cout << "\n";
    std::cout << "Por Niveles BFS : "; recorridoPorNiveles(raiz); std::cout << "\n";
    return 0;
}
