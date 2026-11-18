/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           2.2.6 - Aplicaciones
 * Caso Práctico:     Aplicaciones de Cola (Simulador de planificación de CPU Round-Robin)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Justicia temporal y ausencia de inanición (Starvation-free): Cada proceso en el frente recibe a lo sumo q unidades de CPU en Theta(1). Si su ráfaga restante supera q, es expropiado (preempted) y reencolado al final, garantizando un tiempo de respuesta máximo de (n - 1)\cdotq para n procesos activos.
 * ============================================================================
 */

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

struct TareaCPU {
    std::string id;
    int tiempoRestante;
};

void simularRoundRobin(std::vector<TareaCPU> tareas, int quantum) {
    std::queue<TareaCPU> colaListos;
    for (const auto& t : tareas) colaListos.push(t);

    int relojGlobal = 0;
    while (!colaListos.empty()) {
        TareaCPU actual = colaListos.front();
        colaListos.pop();

        int ejecutado = std::min(quantum, actual.tiempoRestante);
        relojGlobal += ejecutado;
        actual.tiempoRestante -= ejecutado;

        std::cout << "[t=" << relojGlobal << "ms] Proceso " << actual.id
                  << " ejecuto " << ejecutado << "ms (Restante: " << actual.tiempoRestante << "ms)\n";

        // Si el proceso no ha terminado su rafaga de CPU, reingresa al final de la cola FIFO
        if (actual.tiempoRestante > 0) {
            colaListos.push(actual);
        }
    }
}

int main() {
    simularRoundRobin({{"P1", 10}, {"P2", 4}, {"P3", 7}}, 4);
    return 0;
}
