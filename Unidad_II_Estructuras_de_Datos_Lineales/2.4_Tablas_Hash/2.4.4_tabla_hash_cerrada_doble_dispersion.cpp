/**
 * ============================================================================
 * Libro / Documento: Introduction to Algorithms (Algoritmos y Estructuras de Datos IPN)
 * Autor:             Joel Morales Gutiérrez
 * Sección:           2.4.4 - Tablas hash cerradas (Direccionamiento abierto / Sondeo)
 * Caso Práctico:     Tablas hash cerradas (Direccionamiento abierto con Doble Dispersión y Tombstones)
 * Estándar:          C++17 / C++20
 * ----------------------------------------------------------------------------
 * Aspectos Técnicos Destacados (explicados en el documento original):
 *   - Eliminación Perezosa (Lazy Deletion / Tombstones): Al eliminar una clave no se puede marcar la celda como VACIA porque truncaría la búsqueda de claves insertadas posteriormente tras colisionar con ella; se marca como BORRADA (Tombstone), reutilizable en futuras inserciones.
 *   - Garantía de recorrido completo por coprimalidad: Como M_PRIMO = 11 es primo y h_2(k) \in [1, 7] nunca es cero ni múltiplo de 11, mcd(h_2(k), 11) = 1. Esto garantiza que la progresión (base + i\cdotpaso) mod 11 visite las 11 ranuras sin caer en ciclos prematuros.
 *   - Reciclaje inteligente de lápidas (primeraBorrada): Durante insertar, si se atraviesa una celda BORRADA se guarda su índice pero se sigue sondeando hasta verificar que k no exista más adelante; luego se reutiliza primeraBorrada evitando degradar el factor de carga.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <optional>
#include <stdexcept>

template <typename K, typename V>
class TablaHashCerrada {
private:
    enum class Estado { VACIA, OCUPADA, BORRADA };
    struct Celda {
        K clave{};
        V valor{};
        Estado estado = Estado::VACIA;
    };

    std::vector<Celda> tabla_;
    std::size_t n_ = 0;
    static constexpr std::size_t M_PRIMO = 11; // Capacidad prima
    static constexpr std::size_t R_PRIMO = 7;  // Primo auxiliar R < M para h2

    std::size_t h1(const K& k) const noexcept { return static_cast<std::size_t>(k) % M_PRIMO; }
    std::size_t h2(const K& k) const noexcept { return R_PRIMO - (static_cast<std::size_t>(k) % R_PRIMO); }

public:
    TablaHashCerrada() : tabla_(M_PRIMO) {}

    bool insertar(const K& k, const V& v) {
        if (n_ >= M_PRIMO) return false;
        std::size_t base = h1(k), paso = h2(k);
        int primeraBorrada = -1;

        for (std::size_t i = 0; i < M_PRIMO; ++i) {
            std::size_t idx = (base + i * paso) % M_PRIMO;
            if (tabla_[idx].estado == Estado::OCUPADA && tabla_[idx].clave == k) {
                tabla_[idx].valor = v; // Actualiza clave existente
                return true;
            }
            if (tabla_[idx].estado == Estado::BORRADA && primeraBorrada == -1) {
                primeraBorrada = static_cast<int>(idx); // Recuerda la primera lapida disponible
            }
            if (tabla_[idx].estado == Estado::VACIA) {
                std::size_t destino = (primeraBorrada != -1) ? static_cast<std::size_t>(primeraBorrada) : idx;
                tabla_[destino] = {k, v, Estado::OCUPADA};
                ++n_;
                return true;
            }
        }
        if (primeraBorrada != -1) {
            tabla_[primeraBorrada] = {k, v, Estado::OCUPADA};
            ++n_;
            return true;
        }
        return false;
    }

    std::optional<V> buscar(const K& k) const {
        std::size_t base = h1(k), paso = h2(k);
        for (std::size_t i = 0; i < M_PRIMO; ++i) {
            std::size_t idx = (base + i * paso) % M_PRIMO;
            if (tabla_[idx].estado == Estado::VACIA) return std::nullopt; // Parada inmediata
            if (tabla_[idx].estado == Estado::OCUPADA && tabla_[idx].clave == k) {
                return tabla_[idx].valor;
            }
            // Si es BORRADA, continua el sondeo sin interrumpir la cadena
        }
        return std::nullopt;
    }

    bool eliminar(const K& k) {
        std::size_t base = h1(k), paso = h2(k);
        for (std::size_t i = 0; i < M_PRIMO; ++i) {
            std::size_t idx = (base + i * paso) % M_PRIMO;
            if (tabla_[idx].estado == Estado::VACIA) return false;
            if (tabla_[idx].estado == Estado::OCUPADA && tabla_[idx].clave == k) {
                tabla_[idx].estado = Estado::BORRADA; // Marca Tombstone
                --n_;
                return true;
            }
        }
        return false;
    }
};

int main() {
    TablaHashCerrada<int, std::string> th;
    th.insertar(10, "Diez");
    th.insertar(21, "Veintiuno"); // 21 % 11 == 10 (Colisiona con 10, resuelve por h2)
    th.eliminar(10);              // Deja Tombstone en 10 sin romper la busqueda de 21
    auto res = th.buscar(21);
    std::cout << "Busqueda de 21 tras borrar 10: " << (res ? *res : "No hallado") << "\n";
    return 0;
}
