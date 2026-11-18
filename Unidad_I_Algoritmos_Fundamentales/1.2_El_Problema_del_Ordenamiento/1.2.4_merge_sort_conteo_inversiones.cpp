/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           1.2.4 - Ordenamiento por mezcla
 * Caso Práctico:     Ordenamiento por mezcla (Merge Sort estable y conteo de inversiones)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Optimización de memoria con buffer único preasignado: En lugar de instanciar vectores temporales L y R dentro de cada llamada a intercalar (lo cual presionaría al asignador dinámico del heap miles de veces), se reserva un único std::vector<T> aux de tamaño n en la función envolvente, manteniendo complejidad espacial Theta(n) con sobrecarga mínima.
 *   - Prevención de desbordamiento aritmético: El punto medio se calcula como izq + (der - izq) / 2 en lugar de (izq + der) / 2, previniendo overflow en enteros de 32 bits cuando los índices superan 2^3^0.
 *   - Estabilidad e invariante de intercalación: La condición aux[i] <= aux[j] prioriza el elemento de la sublista izquierda ante empates de clave, garantizando que el ordenamiento sea estable y permitiendo además contabilizar el número exacto de inversiones en Theta(n log n).
 * ============================================================================
 */

#include <iostream>
#include <vector>

template <typename T>
long long intercalar(std::vector<T>& A, std::vector<T>& aux, int izq, int medio, int der) {
    for (int k = izq; k <= der; ++k) {
        aux[k] = A[k];
    }
    int i = izq;       // Cursor de la mitad izquierda [izq .. medio]
    int j = medio + 1; // Cursor de la mitad derecha   [medio+1 .. der]
    long long inversiones = 0;

    for (int k = izq; k <= der; ++k) {
        if (i > medio) {
            A[k] = aux[j++];
        } else if (j > der) {
            A[k] = aux[i++];
        } else if (aux[i] <= aux[j]) { // '<=' garantiza estabilidad estricta
            A[k] = aux[i++];
        } else {
            A[k] = aux[j++];
            inversiones += (medio - i + 1); // Todos los restantes en izq son mayores que aux[j]
        }
    }
    return inversiones;
}

template <typename T>
long long mergeSortRec(std::vector<T>& A, std::vector<T>& aux, int izq, int der) {
    if (izq >= der) return 0;
    int medio = izq + (der - izq) / 2; // Evita desbordamiento de entero en (izq + der)
    long long inv = 0;
    inv += mergeSortRec(A, aux, izq, medio);
    inv += mergeSortRec(A, aux, medio + 1, der);
    inv += intercalar(A, aux, izq, medio, der);
    return inv;
}

template <typename T>
long long mergeSort(std::vector<T>& A) {
    if (A.empty()) return 0;
    std::vector<T> aux(A.size()); // Una unica reserva en el heap evita O(n log n) reservas
    return mergeSortRec(A, aux, 0, static_cast<int>(A.size()) - 1);
}

int main() {
    std::vector<int> datos = {38, 27, 43, 3, 9, 82, 10};
    long long inv = mergeSort(datos);
    std::cout << "Ordenado (Inversiones corregidas = " << inv << "): ";
    for (int x : datos) std::cout << x << " ";
    std::cout << "\n";
    return 0;
}
