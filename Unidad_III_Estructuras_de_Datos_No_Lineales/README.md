# Unidad Temática III: Estructuras de Datos No Lineales

**Unidad de Competencia (Programa Oficial IPN ISC-2020):** *Implementa estructuras de datos no lineales (árboles y grafos) en la resolución de problemas de búsqueda jerárquica, optimización y rutas óptimas.*

Toda la fundamentación teórica, invariantes de coloración y teoremas de optimalidad se encuentra en [`../Introduction_to_Algorithms.pdf`](../Introduction_to_Algorithms.pdf).

## Subcarpetas y Casos Prácticos Técnicos (12 programas en C++)

1. **[`3.1_Arboles_Binarios/`](./3.1_Arboles_Binarios/)**
   * `3.1.1_transformacion_arbol_n_ario_a_binario_lcrs.cpp` — Transformación de un árbol general $n$-ario a binario (Representación LCRS de Knuth).
   * `3.1.2_recorridos_arbol_binario_recursivos_e_iterativos.cpp` — Recorridos recursivos (Preorden, Inorden, Postorden) e iterativos (Pila explícita y BFS por niveles).
   * `3.1.3_arbol_binario_de_busqueda_abb_hibbard.cpp` — Árbol Binario de Búsqueda (ABB / BST) con eliminación de Hibbard (3 casos).
   * `3.1.4_arbol_balanceado_rojo_negro_llrb.cpp` — Árbol balanceado Rojo-Negro (Variante LLRB de Sedgewick) con rotaciones en $\Theta(1)$.
   * `3.1.5_monticulo_binario_max_heap_y_heapsort.cpp` — Montículo Binario Máximo (*Max-Heap*), construcción lineal de Floyd $\Theta(n)$ y *HeapSort In-Place*.
   * `3.1.6_aplicaciones_arbol_expresion_aritmetica.cpp` — Construcción y evaluación recursiva en postorden de un Árbol de Expresión Aritmética.
   * `3.1.8_otros_arboles_trie_prefijos.cpp` — Árbol de Prefijos (*Trie*) para autocompletado y búsqueda lexicográfica en $\Theta(L)$.
2. **[`3.2_Grafos_Graphs/`](./3.2_Grafos_Graphs/)**
   * `3.2.1_representacion_grafos_matriz_y_lista_adyacencia.cpp` — Representación dual de un grafo ponderado: Matriz de Adyacencia y Lista de Adyacencia.
   * `3.2.2_busqueda_en_amplitud_bfs_camino_minimo.cpp` — Búsqueda en Amplitud (BFS) con distancias mínimas en aristas y reconstrucción de camino.
   * `3.2.3_busqueda_en_profundidad_dfs_ciclos_y_topologico.cpp` — Búsqueda en Profundidad (DFS) con clasificación de 3 colores, detección de ciclos y Orden Topológico.
   * `3.2.4_distancia_mas_corta_dijkstra_y_bellman_ford.cpp` — Algoritmo de Dijkstra $\mathcal{O}((V+E)\log V)$ y Algoritmo de Bellman-Ford $\mathcal{O}(V \cdot E)$.
   * `3.2.5_aplicaciones_grafos_mst_kruskal_union_find.cpp` — Árbol de Expansión Mínima (MST) mediante Kruskal y estructura *Union-Find* (DSU).
