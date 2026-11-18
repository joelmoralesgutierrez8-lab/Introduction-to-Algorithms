# Unidad Temática II: Estructuras de Datos Lineales

**Unidad de Competencia (Programa Oficial IPN ISC-2020):** *Implementa estructuras de datos lineales en la resolución de problemas computacionales con base en la eficiencia de sus operaciones.*

Toda la fundamentación teórica, axiomas de TDAs y análisis de localidad de caché se encuentra en [`../Introduction_to_Algorithms.pdf`](../Introduction_to_Algorithms.pdf).

## Subcarpetas y Casos Prácticos Técnicos (15 programas en C++)

1. **[`2.1_Pila_Stack/`](./2.1_Pila_Stack/)**
   * `2.1.2_pila_estatica_plantillas.cpp` — Pila estática genérica basada en plantillas no-tipo (`Fixed-Capacity Stack`).
   * `2.1.3_pila_dinamica_enlazada_raii.cpp` — Pila dinámica enlazada con gestión segura de memoria (RAII y semántica `move`).
   * `2.1.5_aplicaciones_pila_balanceo_y_rpn.cpp` — Verificador de delimitadores balanceados y evaluador Postfijo (RPN).
2. **[`2.2_Cola_Queue/`](./2.2_Cola_Queue/)**
   * `2.2.2_cola_estatica_circular_ring_buffer.cpp` — Cola estática circular (*Ring Buffer*) en tiempo constante $\Theta(1)$.
   * `2.2.3_cola_dinamica_enlazada.cpp` — Cola dinámica enlazada con doble puntero exterior (`frente_` y `final_`).
   * `2.2.4_cola_de_prioridad_min_heap.cpp` — Cola de prioridad de mínimo (*Min-Priority Queue*) para planificación de tareas.
   * `2.2.6_aplicaciones_cola_planificador_round_robin.cpp` — Simulador de planificación de CPU *Round-Robin* con *Quantum* configurable.
3. **[`2.3_Listas_Enlazadas/`](./2.3_Listas_Enlazadas/)**
   * `2.3.2_lista_simplemente_enlazada_inversion_inplace.cpp` — Lista simplemente enlazada genérica con inversión *In-Place* en $\Theta(n)$.
   * `2.3.3_lista_doblemente_enlazada_centinelas.cpp` — Lista doblemente enlazada con nodos centinela (*Header & Trailer Sentinels*) en $\Theta(1)$.
   * `2.3.4_lista_circular_flavio_josefo.cpp` — Lista circular con puntero a cola y resolución del Problema de Flavio Josefo.
   * `2.3.7_aplicaciones_listas_polinomios_dispersos.cpp` — Suma simbólica de polinomios dispersos mediante listas enlazadas ordenadas en $\mathcal{O}(n+m)$.
4. **[`2.4_Tablas_Hash/`](./2.4_Tablas_Hash/)**
   * `2.4.2_funciones_hash_fibonacci_horner_universal.cpp` — Funciones Hash: Multiplicación de Fibonacci (64 bits), Polinomial de Horner y Universal.
   * `2.4.4_tabla_hash_cerrada_doble_dispersion.cpp` — Tabla Hash cerrada con Doble Dispersión (*Double Hashing*) y *Tombstones*.
   * `2.4.5_tabla_hash_abierta_separate_chaining.cpp` — Tabla Hash abierta (*Separate Chaining*) con *Rehashing* dinámico automático.
   * `2.4.7_aplicaciones_hash_tabla_simbolos_y_two_sum.cpp` — Tabla de símbolos de un compilador y problema *Two-Sum* en $\Theta(n)$.
