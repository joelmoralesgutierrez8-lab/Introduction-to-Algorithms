# Unidad Temática I: Algoritmos Fundamentales

**Unidad de Competencia (Programa Oficial IPN ISC-2020):** *Identifica algoritmos fundamentales de la computación con base en sus órdenes de complejidad.*

Toda la fundamentación teórica, invariantes de bucle y cotas asintóticas se encuentra en [`../Introduction_to_Algorithms.pdf`](../Introduction_to_Algorithms.pdf).

## Subcarpetas y Casos Prácticos Técnicos (13 programas en C++)

1. **[`1.1_Algoritmia/`](./1.1_Algoritmia/)**
   * `1.1.1_euclides_iterativo_vs_recursivo.cpp` — Algoritmo de Euclides iterativo vs. recursivo de cola.
   * `1.1.2_polinomio_horner_invariante.cpp` — Evaluación polinomial de Horner con aserciones de invariante en $\Theta(n)$.
   * `1.1.3_tda_conjunto_finito_templates.cpp` — Especificación algebraica e implementación genérica del TDA Conjunto Finito.
   * `1.1.4_complejidad_subarreglo_maximo_kadane.cpp` — Comparativa empírica $\Theta(n^2)$ vs. Algoritmo de Kadane $\Theta(n)$.
2. **[`1.2_El_Problema_del_Ordenamiento/`](./1.2_El_Problema_del_Ordenamiento/)**
   * `1.2.1_insertion_sort_y_binary_insertion.cpp` — *Insertion Sort* clásico estable y *Binary Insertion Sort*.
   * `1.2.2_selection_sort_conteo_escrituras.cpp` — *Selection Sort* con minimización de escrituras en memoria $\mathcal{O}(n)$.
   * `1.2.3_bubble_sort_y_cocktail_shaker.cpp` — *Bubble Sort* con salto por último índice de intercambio y *Cocktail Shaker Sort*.
   * `1.2.4_merge_sort_conteo_inversiones.cpp` — *Merge Sort* estable con *buffer* único preasignado y conteo de inversiones en $\Theta(n \log n)$.
3. **[`1.3_El_Problema_de_la_Busqueda/`](./1.3_El_Problema_de_la_Busqueda/)**
   * `1.3.1_busqueda_secuencial_y_centinela.cpp` — Búsqueda secuencial estándar vs. optimizada con centinela de Knuth.
   * `1.3.2_busqueda_binaria_lower_bound.cpp` — Búsqueda binaria iterativa, recursiva y primera aparición (*Lower Bound*).
   * `1.3.3_busqueda_indexada_indice_disperso.cpp` — Búsqueda indexada mediante índice disperso por bloques $\lfloor\sqrt{n}\rfloor$.
4. **[`1.4_Exploracion_Exhaustiva_y_Vuelta_Atras/`](./1.4_Exploracion_Exhaustiva_y_Vuelta_Atras/)**
   * `1.4.1_exploracion_exhaustiva_mochila_bitmask.cpp` — Exploración exhaustiva de $2^n$ subconjuntos con máscara de bits (Mochila 0/1 Exacta).
   * `1.4.2_backtracking_n_reinas_bitmask.cpp` — *Backtracking* con poda en $\Theta(1)$ mediante máscaras de ataque ($N$-Reinas).
