/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           2.4.5 - Tablas hash abiertas (Encadenamiento separado / Separate Chaining)
 * Caso Práctico:     Tablas hash abiertas (Separate Chaining con Rehashing dinámico)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Control automático del factor de carga (rehash): Cuando \alpha = n/m alcanza 0.75, el método rehash construye un nuevo vector de 2m + 1 cubetas y recalcula indiceCubeta para cada elemento. Aunque un rehash individual toma Theta(n + m), ocurre tras \Omega(n) inserciones, preservando tiempo amortizado O(1).
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <functional>

template <typename K, typename V>
class TablaHashAbierta {
private:
    std::vector<std::list<std::pair<K, V>>> cubetas_;
    std::size_t n_ = 0;
    double factorCargaMax_ = 0.75;

    std::size_t indiceCubeta(const K& k, std::size_t m) const {
        return std::hash<K>{}(k) % m;
    }

    void rehash(std::size_t nuevaCapacidad) {
        std::vector<std::list<std::pair<K, V>>> nuevaTabla(nuevaCapacidad);
        for (const auto& lista : cubetas_) {
            for (const auto& par : lista) {
                std::size_t nuevoIdx = indiceCubeta(par.first, nuevaCapacidad);
                nuevaTabla[nuevoIdx].push_back(par);
            }
        }
        cubetas_ = std::move(nuevaTabla);
    }

public:
    explicit TablaHashAbierta(std::size_t mInicial = 7) : cubetas_(mInicial) {}

    double factorCarga() const noexcept {
        return static_cast<double>(n_) / static_cast<double>(cubetas_.size());
    }

    void insertar(const K& k, const V& v) {
        if (factorCarga() >= factorCargaMax_) {
            rehash(cubetas_.size() * 2 + 1); // Duplica capacidad y reubica en O(n + m)
        }
        auto& lista = cubetas_[indiceCubeta(k, cubetas_.size())];
        for (auto& par : lista) {
            if (par.first == k) {
                par.second = v;
                return;
            }
        }
        lista.emplace_back(k, v);
        ++n_;
    }

    V* buscar(const K& k) {
        auto& lista = cubetas_[indiceCubeta(k, cubetas_.size())];
        for (auto& par : lista) {
            if (par.first == k) return &par.second;
        }
        return nullptr;
    }

    bool eliminar(const K& k) {
        auto& lista = cubetas_[indiceCubeta(k, cubetas_.size())];
        for (auto it = lista.begin(); it != lista.end(); ++it) {
            if (it->first == k) {
                lista.erase(it);
                --n_;
                return true;
            }
        }
        return false;
    }
};

int main() {
    TablaHashAbierta<std::string, int> edades;
    edades.insertar("Joel", 20);
    edades.insertar("Ana", 22);
    edades.insertar("Luis", 21);
    if (int* e = edades.buscar("Joel")) {
        std::cout << "Edad de Joel: " << *e << " (Factor de carga: " << edades.factorCarga() << ")\n";
    }
    return 0;
}
