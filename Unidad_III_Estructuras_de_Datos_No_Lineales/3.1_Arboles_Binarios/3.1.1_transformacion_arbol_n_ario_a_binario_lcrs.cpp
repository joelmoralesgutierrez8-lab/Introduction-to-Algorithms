/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           3.1.1 - Transformación de árboles generales a binarios
 * Caso Práctico:     Transformación de árboles generales a binarios (Representación LCRS de Knuth)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Regla 2 (Enlace Hermano Derecho — siguienteHermano): El puntero derecho del nodo u en el árbol binario apunta al hermano inmediato a la derecha de u que comparte el mismo padre en el árbol general.
 *   - Regla 3 (Eliminación de enlaces verticales redundantes): Se suprimen las aristas directas entre el padre y sus hijos segundo, tercero, ..., k-ésimo, los cuales quedan encadenados secuencialmente a través de los punteros derechos del primer hijo.
 *   - Biyección estructural sin pérdida de información: En transformarGeneralABinario, cada nodo del árbol general se visita exactamente una vez en Theta(n). El bucle for encadena los hermanos i = 1..k-1 sobre el puntero hermanoDerecho, reduciendo el consumo de punteros a exactamente 2n punteros (de los cuales n + 1 son nullptr).
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>

// Nodo de un Arbol General (grado arbitrario mediante std::vector)
struct NodoGeneral {
    std::string clave;
    std::vector<NodoGeneral*> hijos;
    explicit NodoGeneral(std::string c) : clave(std::move(c)) {}
};

// Nodo Binario Isomorfo (Representacion Hijo Izquierdo - Hermano Derecho)
struct NodoBinarioLCRS {
    std::string clave;
    NodoBinarioLCRS* hijoIzquierdo = nullptr;   // Primer hijo en el arbol general
    NodoBinarioLCRS* hermanoDerecho = nullptr;  // Siguiente hermano del mismo padre
    explicit NodoBinarioLCRS(std::string c) : clave(std::move(c)) {}
};

// Algoritmo recursivo de transformacion en tiempo lineal Theta(n)
NodoBinarioLCRS* transformarGeneralABinario(const NodoGeneral* raizGen) {
    if (!raizGen) return nullptr;
    auto* nodoBin = new NodoBinarioLCRS(raizGen->clave);

    if (!raizGen->hijos.empty()) {
        // 1. El primer hijo general se convierte en el hijo izquierdo binario
        nodoBin->hijoIzquierdo = transformarGeneralABinario(raizGen->hijos[0]);

        // 2. Los hijos restantes se encadenan como hermanos derechos sucesivos
        NodoBinarioLCRS* actualBin = nodoBin->hijoIzquierdo;
        for (std::size_t i = 1; i < raizGen->hijos.size(); ++i) {
            actualBin->hermanoDerecho = transformarGeneralABinario(raizGen->hijos[i]);
            actualBin = actualBin->hermanoDerecho;
        }
    }
    return nodoBin;
}

void imprimirBinarioLCRS(const NodoBinarioLCRS* u, int prof = 0) {
    if (!u) return;
    std::cout << std::string(prof * 2, ' ') << "- " << u->clave << "\n";
    imprimirBinarioLCRS(u->hijoIzquierdo, prof + 1);  // Baja un nivel jerarquico
    imprimirBinarioLCRS(u->hermanoDerecho, prof);     // Permanece en el mismo nivel
}

int main() {
    auto* dirRaiz = new NodoGeneral("Raiz_IPN");
    auto* escom   = new NodoGeneral("ESCOM");
    auto* upiiz   = new NodoGeneral("UPIIZ");
    auto* upiiap  = new NodoGeneral("UPIIAP");
    escom->hijos.push_back(new NodoGeneral("ISC"));
    escom->hijos.push_back(new NodoGeneral("LCD"));
    dirRaiz->hijos = {escom, upiiz, upiiap};

    NodoBinarioLCRS* arbolBin = transformarGeneralABinario(dirRaiz);
    imprimirBinarioLCRS(arbolBin);
    return 0;
}
