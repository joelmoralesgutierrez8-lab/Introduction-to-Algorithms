/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           3.1.6 - Implementaciones y aplicaciones
 * Caso Práctico:     Aplicaciones de Árboles (Árbol binario de expresión aritmética y evaluación)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Dualidad recorrido-notación en el AST: Sobre el árbol construido por construirArbolExpresion, un recorrido Preorden recupera la notación prefija (* + 10 5 - 8 3), Inorden con paréntesis recupera la infija ((10 + 5) * (8 - 3)), y evaluarArbol ejecuta un Postorden bottom-up evaluando primero ambos subárboles hijos antes de aplicar el operador de la raíz.
 * ============================================================================
 */

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>

struct NodoExpr {
    std::string token;
    NodoExpr* izq = nullptr;
    NodoExpr* der = nullptr;
    explicit NodoExpr(std::string t, NodoExpr* i = nullptr, NodoExpr* d = nullptr)
        : token(std::move(t)), izq(i), der(d) {}
};

bool esOperador(const std::string& t) {
    return t == "+" || t == "-" || t == "*" || t == "/";
}

// Construye el Arbol de Expresion en Theta(n) a partir de una cadena en notacion Postfija (RPN)
NodoExpr* construirArbolExpresion(const std::string& rpn) {
    std::stack<NodoExpr*> pila;
    std::istringstream iss(rpn);
    std::string tok;
    while (iss >> tok) {
        if (!esOperador(tok)) {
            pila.push(new NodoExpr(tok));
        } else {
            NodoExpr* der = pila.top(); pila.pop();
            NodoExpr* izq = pila.top(); pila.pop();
            pila.push(new NodoExpr(tok, izq, der));
        }
    }
    return pila.top();
}

// Evalua el Arbol de Expresion mediante recorrido Postorden (LRN) en Theta(n)
double evaluarArbol(const NodoExpr* r) {
    if (!r->izq && !r->der) return std::stod(r->token);
    double valIzq = evaluarArbol(r->izq);
    double valDer = evaluarArbol(r->der);
    if (r->token == "+") return valIzq + valDer;
    if (r->token == "-") return valIzq - valDer;
    if (r->token == "*") return valIzq * valDer;
    return valIzq / valDer;
}

int main() {
    // Expresion: (10 + 5) * (8 - 3) -> Postfija: "10 5 + 8 3 - *" = 75
    NodoExpr* ast = construirArbolExpresion("10 5 + 8 3 - *");
    std::cout << "Resultado del Arbol de Expresion: " << evaluarArbol(ast) << "\n";
    return 0;
}
