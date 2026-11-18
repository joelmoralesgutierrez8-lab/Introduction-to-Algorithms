/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           2.2.4 - Colas de prioridad
 * Caso Práctico:     Colas de prioridad (Min-Priority Queue para planificación de tareas)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Estabilidad FIFO en colas de prioridad: Un montículo binario estándar no preserva por sí solo el orden de llegada entre claves iguales. Al incluir el campo monótono ordenLlegada como segundo criterio lexicográfico en operator>, se garantiza desempate FIFO exacto en O(log n).
 * ============================================================================
 */

#include <iostream>
#include <queue>
#include <vector>
#include <string>

struct Proceso {
    int prioridad;        // Menor valor numerico = mayor urgencia (Tiempo Real)
    int ordenLlegada;     // Desempate FIFO estricto ante igual prioridad
    std::string nombre;

    // Sobrecarga para Min-Heap: retorna true si 'this' tiene MENOR urgencia que 'otro'
    bool operator>(const Proceso& otro) const {
        if (prioridad != otro.prioridad) return prioridad > otro.prioridad;
        return ordenLlegada > otro.ordenLlegada;
    }
};

int main() {
    std::priority_queue<Proceso, std::vector<Proceso>, std::greater<Proceso>> planificador;

    planificador.push({3, 1, "Backup_Disco_Batch"});
    planificador.push({1, 2, "Interrupcion_Kernel_IO"});
    planificador.push({2, 3, "Renderizado_UI"});
    planificador.push({1, 4, "Control_Frenos_ABS"});

    while (!planificador.empty()) {
        const auto& p = planificador.top();
        std::cout << "[Prioridad " << p.prioridad << " | Llegada " << p.ordenLlegada
                  << "] Ejecutando: " << p.nombre << "\n";
        planificador.pop();
    }
    return 0;
}
