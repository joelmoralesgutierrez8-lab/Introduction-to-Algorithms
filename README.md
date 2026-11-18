# Introduction to Algorithms — Manual Técnico, Análisis Asintótico y 40 Casos Prácticos en C++

**Autor:** Joel Morales Gutiérrez  
**Materia:** Algoritmos y Estructuras de Datos (Programa Oficial IPN ISC-2020)  
**Institución:** Instituto Politécnico Nacional (IPN) — Unidad Profesional Interdisciplinaria de Ingeniería "Alejo Peralta" Puebla (UPIIP)

---

## Descripción General del Repositorio

Este repositorio contiene el documento maestro original **`Introduction to Algorithms`** (disponible en formatos **PDF**, **LaTeX `.tex`** y **Word `.docx`**) junto con **40 casos prácticos implementados en C++ moderno (C++17/C++20)** organizados jerárquicamente por unidad temática y subtema.

* **Documento Original Completo:**  
  * [`Introduction_to_Algorithms.pdf`](./Introduction_to_Algorithms.pdf) *(Acceso directo en la raíz del repositorio)*  
  * [`00_Documento_Original_Introduction_to_Algorithms/`](./00_Documento_Original_Introduction_to_Algorithms/) *(Incluye código fuente en LaTeX `.tex`, documento `.docx`, portada y PDF compilado)*
* **Enfoque Dual (Teoría + Práctica Técnica):**  
  Toda la fundamentación matemática, demostraciones por invariante de bucle, axiomas de Tipos de Datos Abstractos (TDA), cotas asintóticas ($\mathcal{O}, \Omega, \Theta$) y tablas comparativas se encuentran explicadas a detalle en el **documento original**, mientras que en las carpetas del repositorio se desarrollan los **40 casos prácticos en código C++** enfocados en las cuestiones técnicas de ingeniería de software (gestión de memoria RAII, plantillas genéricas, optimización de caché, centinelas, invariantes y pruebas ejecutables).

---

## Estructura y Clasificación de los Temas y Casos Prácticos

```text
Introduction-to-Algorithms/
├── Introduction_to_Algorithms.pdf
├── 00_Documento_Original_Introduction_to_Algorithms/
│   ├── Introduction_to_Algorithms_IPN.pdf
│   ├── Introduction_to_Algorithms_IPN.tex
│   ├── Introduction_to_Algorithms_IPN.docx
│   └── cover.png
├── Unidad_I_Algoritmos_Fundamentales/
│   ├── 1.1_Algoritmia/
│   ├── 1.2_El_Problema_del_Ordenamiento/
│   ├── 1.3_El_Problema_de_la_Busqueda/
│   └── 1.4_Exploracion_Exhaustiva_y_Vuelta_Atras/
├── Unidad_II_Estructuras_de_Datos_Lineales/
│   ├── 2.1_Pila_Stack/
│   ├── 2.2_Cola_Queue/
│   ├── 2.3_Listas_Enlazadas/
│   └── 2.4_Tablas_Hash/
└── Unidad_III_Estructuras_de_Datos_No_Lineales/
    ├── 3.1_Arboles_Binarios/
    └── 3.2_Grafos_Graphs/
```

---

## Índice Maestro de Temas (Teoría en el Documento vs. Caso Práctico en C++)

### UNIDAD TEMÁTICA I: Algoritmos Fundamentales

#### 1.1 Algoritmia (`Unidad_I_Algoritmos_Fundamentales/1.1_Algoritmia/`)
| Subtema | Tema en el Documento Original | Caso Práctico Técnico en Código C++ | Complejidad |
| :--- | :--- | :--- | :--- |
| **1.1.1** | Características de los algoritmos y tipos | [`1.1.1_euclides_iterativo_vs_recursivo.cpp`](./Unidad_I_Algoritmos_Fundamentales/1.1_Algoritmia/1.1.1_euclides_iterativo_vs_recursivo.cpp) — Comparativa de flujo iterativo vs. recursivo de cola (MCD de Euclides) | $\mathcal{O}(\log(\min(a,b)))$ |
| **1.1.2** | Representación de algoritmos en pseudocódigo | [`1.1.2_polinomio_horner_invariante.cpp`](./Unidad_I_Algoritmos_Fundamentales/1.1_Algoritmia/1.1.2_polinomio_horner_invariante.cpp) — Traducción de pseudocódigo formal con aserciones de invariante (Regla de Horner) | $\Theta(n)$ |
| **1.1.3** | Abstracción y tipo de dato abstracto (TDA) | [`1.1.3_tda_conjunto_finito_templates.cpp`](./Unidad_I_Algoritmos_Fundamentales/1.1_Algoritmia/1.1.3_tda_conjunto_finito_templates.cpp) — Especificación algebraica e implementación genérica del TDA Conjunto Finito (`templates`) | $\mathcal{O}(n)$ |
| **1.1.4** | Orden de complejidad $\mathcal{O}()$ de un algoritmo | [`1.1.4_complejidad_subarreglo_maximo_kadane.cpp`](./Unidad_I_Algoritmos_Fundamentales/1.1_Algoritmia/1.1.4_complejidad_subarreglo_maximo_kadane.cpp) — Demostración empírica $\Theta(n^2)$ vs. Programación Dinámica de Kadane $\Theta(n)$ | $\Theta(n^2) \to \Theta(n)$ |

#### 1.2 El Problema del Ordenamiento (`Unidad_I_Algoritmos_Fundamentales/1.2_El_Problema_del_Ordenamiento/`)
| Subtema | Tema en el Documento Original | Caso Práctico Técnico en Código C++ | Complejidad |
| :--- | :--- | :--- | :--- |
| **1.2.1** | Ordenamiento por inserción (*Insertion Sort*) | [`1.2.1_insertion_sort_y_binary_insertion.cpp`](./Unidad_I_Algoritmos_Fundamentales/1.2_El_Problema_del_Ordenamiento/1.2.1_insertion_sort_y_binary_insertion.cpp) — *Insertion Sort* clásico estable y *Binary Insertion Sort* con `std::upper_bound` | $\mathcal{O}(n + \text{Inv}(A))$ |
| **1.2.2** | Ordenamiento por selección (*Selection Sort*) | [`1.2.2_selection_sort_conteo_escrituras.cpp`](./Unidad_I_Algoritmos_Fundamentales/1.2_El_Problema_del_Ordenamiento/1.2.2_selection_sort_conteo_escrituras.cpp) — *Selection Sort* con minimización y conteo de escrituras en memoria $\mathcal{O}(n)$ | $\Theta(n^2)$ comp / $\mathcal{O}(n)$ swaps |
| **1.2.3** | Ordenamiento de burbuja (*Bubble Sort*) | [`1.2.3_bubble_sort_y_cocktail_shaker.cpp`](./Unidad_I_Algoritmos_Fundamentales/1.2_El_Problema_del_Ordenamiento/1.2.3_bubble_sort_y_cocktail_shaker.cpp) — *Bubble Sort* con salto al último índice de intercambio y *Cocktail Shaker Sort* bidireccional | $\Omega(n)$ / $\mathcal{O}(n^2)$ |
| **1.2.4** | Ordenamiento por mezcla (*Merge Sort*) | [`1.2.4_merge_sort_conteo_inversiones.cpp`](./Unidad_I_Algoritmos_Fundamentales/1.2_El_Problema_del_Ordenamiento/1.2.4_merge_sort_conteo_inversiones.cpp) — *Merge Sort* estable con *buffer* único preasignado y conteo exacto de inversiones | $\Theta(n \log n)$ |
| **1.2.5** | Comparación de órdenes de complejidad | *Sección teórica y tabla analítica explicada en el documento original.* | — |

#### 1.3 El Problema de la Búsqueda (`Unidad_I_Algoritmos_Fundamentales/1.3_El_Problema_de_la_Busqueda/`)
| Subtema | Tema en el Documento Original | Caso Práctico Técnico en Código C++ | Complejidad |
| :--- | :--- | :--- | :--- |
| **1.3.1** | Búsqueda secuencial | [`1.3.1_busqueda_secuencial_y_centinela.cpp`](./Unidad_I_Algoritmos_Fundamentales/1.3_El_Problema_de_la_Busqueda/1.3.1_busqueda_secuencial_y_centinela.cpp) — Búsqueda secuencial estándar vs. optimizada con centinela de Knuth (mitad de ramificaciones) | $\mathcal{O}(n)$ |
| **1.3.2** | Búsqueda binaria | [`1.3.2_busqueda_binaria_lower_bound.cpp`](./Unidad_I_Algoritmos_Fundamentales/1.3_El_Problema_de_la_Busqueda/1.3.2_busqueda_binaria_lower_bound.cpp) — Búsqueda binaria iterativa libre de *overflow*, recursiva y primera aparición (*Lower Bound*) | $\mathcal{O}(\log n)$ |
| **1.3.3** | Búsqueda indexada | [`1.3.3_busqueda_indexada_indice_disperso.cpp`](./Unidad_I_Algoritmos_Fundamentales/1.3_El_Problema_de_la_Busqueda/1.3.3_busqueda_indexada_indice_disperso.cpp) — Índice denso por bloques $\lfloor\sqrt{n}\rfloor$ con búsqueda binaria de bloque y barrido acotado | $\mathcal{O}(\log(n/B) + B)$ |
| **1.3.4** | Comparación de órdenes de complejidad | *Sección teórica y tabla comparativa explicada en el documento original.* | — |

#### 1.4 Exploración Exhaustiva y Vuelta Atrás (`Unidad_I_Algoritmos_Fundamentales/1.4_Exploracion_Exhaustiva_y_Vuelta_Atras/`)
| Subtema | Tema en el Documento Original | Caso Práctico Técnico en Código C++ | Complejidad |
| :--- | :--- | :--- | :--- |
| **1.4.1** | Exploración exhaustiva (*Brute Force*) | [`1.4.1_exploracion_exhaustiva_mochila_bitmask.cpp`](./Unidad_I_Algoritmos_Fundamentales/1.4_Exploracion_Exhaustiva_y_Vuelta_Atras/1.4.1_exploracion_exhaustiva_mochila_bitmask.cpp) — Generación exhaustiva de $2^n$ subconjuntos con máscara de bits (Mochila 0/1 Exacta) | $\Theta(n \cdot 2^n)$ |
| **1.4.2** | Programación por vuelta atrás (*Backtracking*) | [`1.4.2_backtracking_n_reinas_bitmask.cpp`](./Unidad_I_Algoritmos_Fundamentales/1.4_Exploracion_Exhaustiva_y_Vuelta_Atras/1.4.2_backtracking_n_reinas_bitmask.cpp) — *Backtracking* con poda en $\Theta(1)$ mediante máscaras de bits de ataque (Problema de las $N$-Reinas) | $\mathcal{O}(N!)$ con poda |
| **1.4.3** | Nociones de complejidad | *Análisis formal de espacios de estados $b^d$ y $n!$ en el documento original.* | — |

---

### UNIDAD TEMÁTICA II: Estructuras de Datos Lineales

#### 2.1 Pila / Stack (`Unidad_II_Estructuras_de_Datos_Lineales/2.1_Pila_Stack/`)
| Subtema | Tema en el Documento Original | Caso Práctico Técnico en Código C++ | Complejidad |
| :--- | :--- | :--- | :--- |
| **2.1.1** | Especificación genérica (TDA Pila LIFO) | *Especificación formal y axiomas LIFO en el documento original.* | — |
| **2.1.2** | Implementación estática | [`2.1.2_pila_estatica_plantillas.cpp`](./Unidad_II_Estructuras_de_Datos_Lineales/2.1_Pila_Stack/2.1.2_pila_estatica_plantillas.cpp) — Pila estática genérica basada en plantillas no-tipo (`template <typename T, size_t Cap>`) | $\Theta(1)$ |
| **2.1.3** | Implementación dinámica | [`2.1.3_pila_dinamica_enlazada_raii.cpp`](./Unidad_II_Estructuras_de_Datos_Lineales/2.1_Pila_Stack/2.1.3_pila_dinamica_enlazada_raii.cpp) — Pila dinámica simplemente enlazada con gestión segura de memoria (RAII y semántica de movimiento) | $\Theta(1)$ |
| **2.1.4** | Nociones de complejidad | *Tabla comparativa estática vs. dinámica en el documento original.* | — |
| **2.1.5** | Aplicaciones de Pilas | [`2.1.5_aplicaciones_pila_balanceo_y_rpn.cpp`](./Unidad_II_Estructuras_de_Datos_Lineales/2.1_Pila_Stack/2.1.5_aplicaciones_pila_balanceo_y_rpn.cpp) — Verificador de balanceo de delimitadores y evaluador de expresiones en Notación Polaca Inversa (RPN) | $\Theta(n)$ |

#### 2.2 Cola / Queue (`Unidad_II_Estructuras_de_Datos_Lineales/2.2_Cola_Queue/`)
| Subtema | Tema en el Documento Original | Caso Práctico Técnico en Código C++ | Complejidad |
| :--- | :--- | :--- | :--- |
| **2.2.1** | Especificación genérica (TDA Cola FIFO) | *Especificación algebraica FIFO en el documento original.* | — |
| **2.2.2** | Implementación estática | [`2.2.2_cola_estatica_circular_ring_buffer.cpp`](./Unidad_II_Estructuras_de_Datos_Lineales/2.2_Cola_Queue/2.2.2_cola_estatica_circular_ring_buffer.cpp) — Cola estática circular (*Ring Buffer*) con aritmética modular sin desplazamientos | $\Theta(1)$ |
| **2.2.3** | Implementación dinámica | [`2.2.3_cola_dinamica_enlazada.cpp`](./Unidad_II_Estructuras_de_Datos_Lineales/2.2_Cola_Queue/2.2.3_cola_dinamica_enlazada.cpp) — Cola dinámica enlazada con doble puntero exterior (`frente_` y `final_`) | $\Theta(1)$ |
| **2.2.4** | Colas de prioridad (*Priority Queues*) | [`2.2.4_cola_de_prioridad_min_heap.cpp`](./Unidad_II_Estructuras_de_Datos_Lineales/2.2_Cola_Queue/2.2.4_cola_de_prioridad_min_heap.cpp) — Cola de prioridad de mínimo (*Min-Heap*) con desempate determinista por orden de llegada | $\mathcal{O}(\log n)$ |
| **2.2.5** | Nociones de complejidad | *Comparativa técnica de implementaciones de colas en el documento original.* | — |
| **2.2.6** | Aplicaciones de Colas | [`2.2.6_aplicaciones_cola_planificador_round_robin.cpp`](./Unidad_II_Estructuras_de_Datos_Lineales/2.2_Cola_Queue/2.2.6_aplicaciones_cola_planificador_round_robin.cpp) — Simulador de planificación de procesos de CPU *Round-Robin* con *Quantum* configurable | $\mathcal{O}(n \cdot \text{ciclos})$ |

#### 2.3 Listas / Lists (`Unidad_II_Estructuras_de_Datos_Lineales/2.3_Listas_Enlazadas/`)
| Subtema | Tema en el Documento Original | Caso Práctico Técnico en Código C++ | Complejidad |
| :--- | :--- | :--- | :--- |
| **2.3.1** | Especificación genérica | *Operaciones posicionales y axiomas del TDA Lista en el documento original.* | — |
| **2.3.2** | Listas simplemente enlazadas | [`2.3.2_lista_simplemente_enlazada_inversion_inplace.cpp`](./Unidad_II_Estructuras_de_Datos_Lineales/2.3_Listas_Enlazadas/2.3.2_lista_simplemente_enlazada_inversion_inplace.cpp) — Lista simplemente enlazada genérica con inserción, eliminación e inversión *In-Place* de 3 punteros | $\Theta(1)$ / $\Theta(n)$ |
| **2.3.3** | Listas doblemente enlazadas | [`2.3.3_lista_doblemente_enlazada_centinelas.cpp`](./Unidad_II_Estructuras_de_Datos_Lineales/2.3_Listas_Enlazadas/2.3.3_lista_doblemente_enlazada_centinelas.cpp) — Lista doblemente enlazada con nodos centinela permanentes (*Header & Trailer Sentinels*) | $\Theta(1)$ extremos |
| **2.3.4** | Listas circulares | [`2.3.4_lista_circular_flavio_josefo.cpp`](./Unidad_II_Estructuras_de_Datos_Lineales/2.3_Listas_Enlazadas/2.3.4_lista_circular_flavio_josefo.cpp) — Lista circular gestionada por puntero a cola (`cola_`) y resolución del Problema de Flavio Josefo | $\Theta(1)$ / $\mathcal{O}(n \cdot k)$ |
| **2.3.5 - 2.3.6** | Arreglos/vectores vs. listas y complejidad | *Análisis de localidad espacial de caché L1/L2 y tablas asintóticas en el documento original.* | — |
| **2.3.7** | Implementaciones y aplicaciones | [`2.3.7_aplicaciones_listas_polinomios_dispersos.cpp`](./Unidad_II_Estructuras_de_Datos_Lineales/2.3_Listas_Enlazadas/2.3.7_aplicaciones_listas_polinomios_dispersos.cpp) — Suma simbólica de polinomios dispersos mediante listas enlazadas ordenadas por exponente | $\mathcal{O}(n + m)$ |

#### 2.4 Tablas Hash / Hash Tables (`Unidad_II_Estructuras_de_Datos_Lineales/2.4_Tablas_Hash/`)
| Subtema | Tema en el Documento Original | Caso Práctico Técnico en Código C++ | Complejidad |
| :--- | :--- | :--- | :--- |
| **2.4.1** | Especificación genérica (TDA Diccionario) | *Especificación formal del mapa asociativo clave-valor en el documento original.* | — |
| **2.4.2** | Función hash | [`2.4.2_funciones_hash_fibonacci_horner_universal.cpp`](./Unidad_II_Estructuras_de_Datos_Lineales/2.4_Tablas_Hash/2.4.2_funciones_hash_fibonacci_horner_universal.cpp) — Dispersión por Multiplicación de Fibonacci (64 bits), Polinomial de Horner y Universal de Carter-Wegman | $\Theta(1)$ / $\Theta(L)$ |
| **2.4.3** | Resolución de colisiones | *Fundamentos del factor de carga $\alpha = n/m$ en el documento original.* | — |
| **2.4.4** | Tablas hash cerradas (Direccionamiento abierto) | [`2.4.4_tabla_hash_cerrada_doble_dispersion.cpp`](./Unidad_II_Estructuras_de_Datos_Lineales/2.4_Tablas_Hash/2.4.4_tabla_hash_cerrada_doble_dispersion.cpp) — Tabla Hash cerrada con Doble Dispersión (*Double Hashing*) y borrado perezoso (*Tombstones*) | $\Theta(1/(1-\alpha))$ |
| **2.4.5** | Tablas hash abiertas (*Separate Chaining*) | [`2.4.5_tabla_hash_abierta_separate_chaining.cpp`](./Unidad_II_Estructuras_de_Datos_Lineales/2.4_Tablas_Hash/2.4.5_tabla_hash_abierta_separate_chaining.cpp) — Tabla Hash abierta con encadenamiento separado y *Rehashing* dinámico automático | $\Theta(1 + \alpha)$ |
| **2.4.6** | Nociones de complejidad | *Tabla comparativa esperada vs. peor caso en el documento original.* | — |
| **2.4.7** | Implementaciones y aplicaciones | [`2.4.7_aplicaciones_hash_tabla_simbolos_y_two_sum.cpp`](./Unidad_II_Estructuras_de_Datos_Lineales/2.4_Tablas_Hash/2.4.7_aplicaciones_hash_tabla_simbolos_y_two_sum.cpp) — Tabla de símbolos léxicos de un compilador e identificación de pares con suma objetivo (*Two-Sum*) | $\Theta(n)$ |

---

### UNIDAD TEMÁTICA III: Estructuras de Datos No Lineales

#### 3.1 Árboles Binarios (`Unidad_III_Estructuras_de_Datos_No_Lineales/3.1_Arboles_Binarios/`)
| Subtema | Tema en el Documento Original | Caso Práctico Técnico en Código C++ | Complejidad |
| :--- | :--- | :--- | :--- |
| **3.1.1** | Transformación de árboles generales a binarios | [`3.1.1_transformacion_arbol_n_ario_a_binario_lcrs.cpp`](./Unidad_III_Estructuras_de_Datos_No_Lineales/3.1_Arboles_Binarios/3.1.1_transformacion_arbol_n_ario_a_binario_lcrs.cpp) — Transformación isomorfa de un árbol general $n$-ario a binario (Representación LCRS de Knuth) | $\Theta(n)$ |
| **3.1.2** | Recorridos en un árbol binario | [`3.1.2_recorridos_arbol_binario_recursivos_e_iterativos.cpp`](./Unidad_III_Estructuras_de_Datos_No_Lineales/3.1_Arboles_Binarios/3.1.2_recorridos_arbol_binario_recursivos_e_iterativos.cpp) — Recorridos recursivos (Preorden, Inorden, Postorden) e iterativos con Pila explícita y Cola por niveles | $\Theta(n)$ |
| **3.1.3** | Árbol binario de búsqueda (ABB / BST) | [`3.1.3_arbol_binario_de_busqueda_abb_hibbard.cpp`](./Unidad_III_Estructuras_de_Datos_No_Lineales/3.1_Arboles_Binarios/3.1.3_arbol_binario_de_busqueda_abb_hibbard.cpp) — ABB completo con inserción, búsqueda y eliminación de Hibbard (3 casos con sucesor inorden) | $\mathcal{O}(h)$ |
| **3.1.4** | Árbol balanceado Rojo-Negro (*Red-Black Tree*) | [`3.1.4_arbol_balanceado_rojo_negro_llrb.cpp`](./Unidad_III_Estructuras_de_Datos_No_Lineales/3.1_Arboles_Binarios/3.1.4_arbol_balanceado_rojo_negro_llrb.cpp) — Árbol Rojo-Negro autobalanceado (Variante LLRB de Sedgewick) con rotaciones en $\Theta(1)$ | $\Theta(\log n)$ |
| **3.1.5** | Montículo (*Binary Heap*) | [`3.1.5_monticulo_binario_max_heap_y_heapsort.cpp`](./Unidad_III_Estructuras_de_Datos_No_Lineales/3.1_Arboles_Binarios/3.1.5_monticulo_binario_max_heap_y_heapsort.cpp) — Montículo Binario Máximo (*Max-Heap*), construcción lineal de Floyd $\Theta(n)$ y *HeapSort In-Place* | $\Theta(n)$ / $\Theta(n \log n)$ |
| **3.1.6** | Implementaciones y aplicaciones | [`3.1.6_aplicaciones_arbol_expresion_aritmetica.cpp`](./Unidad_III_Estructuras_de_Datos_No_Lineales/3.1_Arboles_Binarios/3.1.6_aplicaciones_arbol_expresion_aritmetica.cpp) — Construcción desde notación postfija y evaluación en postorden de un Árbol de Expresión Aritmética | $\Theta(n)$ |
| **3.1.7** | Nociones de complejidad | *Tabla comparativa de árboles degenerados vs. balanceados en el documento original.* | — |
| **3.1.8** | Otros tipos de árboles | [`3.1.8_otros_arboles_trie_prefijos.cpp`](./Unidad_III_Estructuras_de_Datos_No_Lineales/3.1_Arboles_Binarios/3.1.8_otros_arboles_trie_prefijos.cpp) — Árbol de Prefijos (*Trie*) para autocompletado y búsqueda lexicográfica independiente de $N$ | $\Theta(L)$ |

#### 3.2 Grafos / Graphs (`Unidad_III_Estructuras_de_Datos_No_Lineales/3.2_Grafos_Graphs/`)
| Subtema | Tema en el Documento Original | Caso Práctico Técnico en Código C++ | Complejidad |
| :--- | :--- | :--- | :--- |
| **3.2.1** | Representaciones matriciales y basadas en listas | [`3.2.1_representacion_grafos_matriz_y_lista_adyacencia.cpp`](./Unidad_III_Estructuras_de_Datos_No_Lineales/3.2_Grafos_Graphs/3.2.1_representacion_grafos_matriz_y_lista_adyacencia.cpp) — Representación dual de un grafo ponderado mediante Matriz de Adyacencia y Lista de Adyacencia | $\Theta(V^2)$ vs $\Theta(V+E)$ |
| **3.2.2** | Búsqueda en amplitud (BFS) | [`3.2.2_busqueda_en_amplitud_bfs_camino_minimo.cpp`](./Unidad_III_Estructuras_de_Datos_No_Lineales/3.2_Grafos_Graphs/3.2.2_busqueda_en_amplitud_bfs_camino_minimo.cpp) — BFS con cálculo de distancias mínimas en número de aristas y reconstrucción del camino óptimo | $\Theta(V + E)$ |
| **3.2.3** | Búsqueda en profundidad (DFS) | [`3.2.3_busqueda_en_profundidad_dfs_ciclos_y_topologico.cpp`](./Unidad_III_Estructuras_de_Datos_No_Lineales/3.2_Grafos_Graphs/3.2.3_busqueda_en_profundidad_dfs_ciclos_y_topologico.cpp) — DFS con clasificación de estados (3 colores), detección de ciclos dirigidos y Ordenamiento Topológico | $\Theta(V + E)$ |
| **3.2.4** | Distancia más corta | [`3.2.4_distancia_mas_corta_dijkstra_y_bellman_ford.cpp`](./Unidad_III_Estructuras_de_Datos_No_Lineales/3.2_Grafos_Graphs/3.2.4_distancia_mas_corta_dijkstra_y_bellman_ford.cpp) — Algoritmo de Dijkstra con *Min-Heap* y Algoritmo de Bellman-Ford con detección de ciclos negativos | $\mathcal{O}((V+E)\log V)$ / $\mathcal{O}(VE)$ |
| **3.2.5** | Implementaciones y aplicaciones | [`3.2.5_aplicaciones_grafos_mst_kruskal_union_find.cpp`](./Unidad_III_Estructuras_de_Datos_No_Lineales/3.2_Grafos_Graphs/3.2.5_aplicaciones_grafos_mst_kruskal_union_find.cpp) — Árbol de Expansión Mínima (MST) con el Algoritmo de Kruskal y estructura *Union-Find* (DSU) | $\mathcal{O}(E \log E)$ |
| **3.2.6** | Nociones de complejidad | *Tabla resumen de complejidades temporales y espaciales sobre grafos en el documento original.* | — |

---

## Cómo Compilar y Ejecutar Cualquier Caso Práctico

Cada uno de los **40 archivos `.cpp`** es completamente autónomo (incluye su propia función `main()` con datos de prueba y salida demostrativa en consola) y cumple con el estándar **ISO C++17 / C++20**.

```bash
# Ejemplo: Compilar y ejecutar Merge Sort con conteo de inversiones (Sección 1.2.4)
g++ -std=c++17 -Wall -Wextra -O2 \
  Unidad_I_Algoritmos_Fundamentales/1.2_El_Problema_del_Ordenamiento/1.2.4_merge_sort_conteo_inversiones.cpp \
  -o merge_sort
./merge_sort
```
