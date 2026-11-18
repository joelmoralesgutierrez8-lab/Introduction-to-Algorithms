/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           2.1.5 - Aplicaciones
 * Caso Práctico:     Aplicaciones de Pila (Balanceo de delimitadores y evaluador Postfijo RPN)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - No conmutatividad de operandos en RPN: Al extraer dos operandos de la pila para un operador binario no conmutativo (-, /, \textasciicircum{}), el elemento en la cima corresponde al operando derecho (opDer) y el inmediato inferior al operando izquierdo (opIzq), evaluándose opIzq \theta opDer.
 *   - Complejidad lineal $\Theta$(n): Cada token o carácter de la cadena se apila a lo sumo una vez y se desapila a lo sumo una vez, garantizando tiempo y espacio O(n).
 * ============================================================================
 */

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
#include <stdexcept>

// Aplicacion 1: Validacion lexico-sintactica de simbolos de agrupacion en Theta(n)
bool delimitadoresBalanceados(const std::string& expr) {
    std::stack<char> pila;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            pila.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (pila.empty()) return false; // Cierre sin apertura previa
            char a = pila.top();
            pila.pop();
            if ((c == ')' && a != '(') || (c == ']' && a != '[') || (c == '}' && a != '{')) {
                return false; // Discrepancia de tipo de delimitador
            }
        }
    }
    return pila.empty();
}

// Aplicacion 2: Evaluador de Notacion Polaca Inversa (Postfija / RPN) en Theta(n)
double evaluarPostfijaRPN(const std::string& exprRPN) {
    std::stack<double> operandos;
    std::istringstream iss(exprRPN);
    std::string token;

    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
            if (operandos.size() < 2) throw std::runtime_error("Expresion RPN mal formada");
            double opDer = operandos.top(); operandos.pop(); // Primero en salir: operando derecho
            double opIzq = operandos.top(); operandos.pop(); // Segundo en salir: operando izquierdo
            if (token == "+") operandos.push(opIzq + opDer);
            else if (token == "-") operandos.push(opIzq - opDer);
            else if (token == "*") operandos.push(opIzq * opDer);
            else if (token == "/") operandos.push(opIzq / opDer);
            else if (token == "^") operandos.push(std::pow(opIzq, opDer));
        } else {
            operandos.push(std::stod(token));
        }
    }
    return operandos.top();
}

int main() {
    std::string codigo = "{ a[i] = (b + c) * (d - e); }";
    std::cout << "Balanceo valido: " << (delimitadoresBalanceados(codigo) ? "SI" : "NO") << "\n";
    // Expresion infija: ((5 + 3) * 2) - 4  --> RPN: "5 3 + 2 * 4 -" = 12
    std::cout << "Resultado RPN  : " << evaluarPostfijaRPN("5 3 + 2 * 4 -") << "\n";
    return 0;
}
