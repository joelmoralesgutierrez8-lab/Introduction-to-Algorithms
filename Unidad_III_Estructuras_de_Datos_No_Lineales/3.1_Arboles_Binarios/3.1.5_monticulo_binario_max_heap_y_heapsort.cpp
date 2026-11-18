/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           3.1.5 - Montículo (Binary Heap)
 * Caso Práctico:     Montículo Binario (Max-Heap, construcción lineal de Floyd O(n) y HeapSort)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Demostración de la complejidad lineal $\Theta$(n) de Build-Heap: Un árbol completo de n nodos contiene a lo sumo \lceiln / 2\textasciicircum{}(h+1)\rceil nodos de altura h. El trabajo total de siftDown está acotado por \sum_\{h=0\}\textasciicircum{}\{\lfloorlog n\rfloor\} \lceiln / 2\textasciicircum{}(h+1)\rceil \cdot O(h) = O(n \cdot \sum h / 2\textasciicircum{}h) = O(2n) = Theta(n).
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>

template <typename T>
class MaxHeap {
private:
    std::vector<T> A_;

    void siftUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (A_[p] >= A_[i]) break;
            std::swap(A_[p], A_[i]);
            i = p;
        }
    }

    static void siftDown(std::vector<T>& arr, int n, int i) {
        while (true) {
            int mayor = i;
            int izq = 2 * i + 1;
            int der = 2 * i + 2;
            if (izq < n && arr[izq] > arr[mayor]) mayor = izq;
            if (der < n && arr[der] > arr[mayor]) mayor = der;
            if (mayor == i) break;
            std::swap(arr[i], arr[mayor]);
            i = mayor;
        }
    }

public:
    MaxHeap() = default;

    // Constructor de Floyd (Build-Max-Heap) en tiempo lineal estricto Theta(n)
    explicit MaxHeap(std::vector<T> datos) : A_(std::move(datos)) {
        int n = static_cast<int>(A_.size());
        for (int i = n / 2 - 1; i >= 0; --i) {
            siftDown(A_, n, i);
        }
    }

    void insertar(const T& x) {
        A_.push_back(x);
        siftUp(static_cast<int>(A_.size()) - 1); // Flotar en O(log n)
    }

    T extraerMax() {
        if (A_.empty()) throw std::underflow_error("Heap vacio");
        T maximo = A_.front();
        A_.front() = A_.back();
        A_.pop_back();
        if (!A_.empty()) siftDown(A_, static_cast<int>(A_.size()), 0); // Hundir en O(log n)
        return maximo;
    }

    // Algoritmo HeapSort In-Place: Tiempo Theta(n log n) en peor caso, Memoria Auxiliar Theta(1)
    static void heapSort(std::vector<T>& arr) {
        int n = static_cast<int>(arr.size());
        for (int i = n / 2 - 1; i >= 0; --i) siftDown(arr, n, i); // Fase 1: Build-Heap Theta(n)
        for (int fin = n - 1; fin > 0; --fin) {                   // Fase 2: n-1 extracciones O(n log n)
            std::swap(arr[0], arr[fin]);
            siftDown(arr, fin, 0);
        }
    }
};

int main() {
    std::vector<int> v = {12, 11, 13, 5, 6, 7, 99, 2};
    MaxHeap<int>::heapSort(v);
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";
    return 0;
}
