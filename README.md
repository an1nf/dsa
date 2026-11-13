# dsa
Algoritmos y estructuras de datos de *Introduction to Algorithms* (Cormen, Leiserson, Rivest y Stein, 3.ª y 4.ª ed.) en C99.

## Ordenación (`algorithms/sorting`)

| Algoritmo | Archivo | Función | Tiempo | CLRS |
|---|---|---|---|---|
| Inserción | `insertion-sort/insertionsort.c` | `insertionSort` | O(n²) | 2.1 |
| Selección | `selection-sort/selectionsort.c` | `selectionSort` | Θ(n²) | Ej. 2.2-2 |
| Burbuja | `bubble-sort/bubblesort.c` | `bubbleSort` | O(n²) | Prob. 2-2 |
| Merge sort | `merge-sort/mergesort.c` | `mergeSort` | Θ(n log n) | 2.3 |
| Merge sort genérico | `merge-sort/genmergesort.c` | `mergeSort` (`void*`, comparador) | Θ(n log n) | 2.3 |
| WHAM sort | `merge-sort/whamsort.c` | `whamSort` | O(n log n) | |
| Heapsort | `heap-sort/heapsort.c` | `heapSort` | O(n log n) | 6.4 |
| Quicksort | `quick-sort/quicksort.c` | `quickSort` | O(n²), Θ(n log n) prom. | 7.1 |
| Quicksort aleatorio | `quick-sort/randomqsort.c` | `randomizedQuickSort` | E = Θ(n log n) | 7.3 |
| Counting sort `[0,k]` | `counting-sort/countingsort-1.c` | `countingSort` | Θ(n + k) | 8.2 |
| Counting sort `[min,max]` | `counting-sort/countingsort-2.c` | `countingSort` | Θ(n + k) | 8.2 |
| Radix sort (base 10) | `radix-sort/radixsort.c` | `radixSort` | Θ(d(n + 10)) | 8.3 |
| Bucket sort `[0,1)` | `bucket-sort/bucketsort.c` | `bucketSort` | E = Θ(n) | 8.4 |

## Divide y vencerás (`algorithms/divide-and-conquer`)

| Problema | Archivo | Función | Tiempo | CLRS |
|---|---|---|---|---|
| Búsqueda binaria | `binsearch/binsearch.c` | `lowerBound`, `binarySearch` | O(log n) | Ej. 2.3-5 |
| Subarreglo máximo, fuerza bruta | `max-subarray/msp-1.c` | `maxSubarray` | Θ(n²) | 4.1 |
| Subarreglo máximo, D&C | `max-subarray/msp-2.c` | `maxSubarray` | Θ(n log n) | 4.1 |
| Subarreglo máximo, Kadane | `max-subarray/msp-3.c` | `maxSubarray` | Θ(n) | Ej. 4.1-5 |
| Inversiones | `inversion-count/inversioncount.c` | `countInversions` | Θ(n log n) | Prob. 2-4 |
| Selección aleatoria | `quickselect/qselect-1.c` | `randomizedSelect` | E = Θ(n) | 9.2 |
| Selección (mediana de medianas) | `quickselect/qselect-2.c` | `deterministicSelect` | Θ(n) | 9.3 |
| Producto de matrices, D&C | `strassen/mmp-1.c` | `matrixMultiply` | Θ(n³) | 4.2 |
| Strassen | `strassen/mmp-2.c` | `strassen` | Θ(n^lg 7) | 4.2 |
| Multiplicación escolar | `karatsuba/imp-1.c` | `multiply` | Θ(nm) | |
| Karatsuba | `karatsuba/imp-2.c` | `karatsuba` | Θ(n^lg 3) | |
| Par más cercano, fuerza bruta | `closest-pair-of-points/cpp-1.c` | `closestPair` | Θ(n²) | 33.4 |
| Par más cercano, D&C | `closest-pair-of-points/cpp-2.c` | `closestPair` | Θ(n log n) | 33.4 |

Los enteros grandes se representan como dígitos decimales en orden little-endian. Las matrices son planas `n×n`, con `n` potencia de 2.

## Programación dinámica (`algorithms/dynamic-programming`)

En cada problema, `-1` es la versión recursiva, `-2` la memoizada y `-3`/`-4` las bottom-up con reconstrucción.

| Problema | Archivos | Funciones | Tiempo (DP) | CLRS |
|---|---|---|---|---|
| Corte de varilla | `rod-cutting/cut-rod{1..4}.c` | `cutRod`, `memoizedCutRod`, `bottomUpCutRod`, `extendedBottomUpCutRod`, `cutRodSolution` | Θ(n²) | 15.1 / 14.1 |
| Cadena de matrices | `matrix-chain-mult/mcm-{1..3}.c` | `recursiveMatrixChain`, `memoizedMatrixChain`, `matrixChainOrder`, `optimalParens` | Θ(n³) | 15.2 / 14.2 |
| LCS | `longest-common-sub/lcs-{1..3}.c` | `lcsLength`, `memoizedLcs`, `lcs` | Θ(mn) | 15.4 / 14.4 |
| Subsecuencia palíndroma más larga | `longest-palin-sub/lps-{1..3}.c` | `lpsLength`, `memoizedLps`, `lps` | Θ(n²) | Prob. 15-2 / 14-2 |
| LIS (no decreciente) | `longest-increasing-sub/lis-{1..4}.c` | `lisLength`, `memoizedLis`, `lis` (Θ(n²)), `lis` (Θ(n log n)) | Θ(n log n) | Ej. 15.4-5,6 |
| Mochila 0-1 | `knapsack/knapsack-{1..3}.c` | `knapsack`, `memoizedKnapsack`, `knapsack` (con ítems) | Θ(nW) | Ej. 16.2-2 / 15.2-2 |
| Distancia de edición | `min-edit-dist/med-{1..4}.c` | `editDistance`, `memoizedEditDistance`, `memoizedEditSequence`, `editSequence` | Θ(mn) | Prob. 15-5 / 14-5 |
| BST óptimo | `opt-bsts/obst-{1..5}.c` | `optimalBstCost`, `memoizedOptimalBst`, `optimalBst`, `knuthOptimalBst`, `constructOptimalBst` | Θ(n³), Knuth Θ(n²) | 15.5 / 14.5 |
| Partición palindrómica mínima | `min-pal-part/mpp-{1..3}.c` | `minPalindromeCuts`, `memoizedPalindromePartition`, `palindromePartition` | Θ(n²) | |
| Wildcard matching (`?`, `*`) | `wd-matching/wpm-{1..4}.c` | `wildcardMatch`, `memoizedWildcardMatch` (`wpm-4`: O(m) memoria) | Θ(nm) | |

En la distancia de edición, `cost[]` se indexa por `Op {COPY, INSERT, DELETE, REPLACE, TWIDDLE, KILL}`.

## Algoritmos voraces (`algorithms/greedy`)

| Problema | Archivo | Función | Tiempo | CLRS |
|---|---|---|---|---|
| Selección de actividades, DP | `activity-selection/asp-1.c` | `dpActivitySelector` | Θ(n³) | 16.1 / 15.1 |
| Selección de actividades, recursiva | `activity-selection/asp-2.c` | `activitySelector` | Θ(n) | 16.1 / 15.1 |
| Selección de actividades, iterativa | `activity-selection/asp-3.c` | `greedyActivitySelector` | Θ(n) | 16.1 / 15.1 |
| Asignación de salas, barrido temporal | `lct-hall-scheduling/lhs-1.c` | `minHalls` | O(nT) | Ej. 16.1-4 |
| Asignación de salas, por inicios | `lct-hall-scheduling/lhs-2.c` | `minHalls` | Θ(n²) | Ej. 16.1-4 |
| Asignación de salas, eventos y pila | `lct-hall-scheduling/lhs-3.c` | `scheduleHalls` | Θ(n log n) | Ej. 16.1-4 |
| Asignación de salas, min-heap | `lct-hall-scheduling/lhs-4.c` | `scheduleHalls` | Θ(n log n) | Ej. 16.1-4 |
| Mochila fraccionaria, ordenando | `fract-knapsack/fkp-1.c` | `fractionalKnapsack` | Θ(n log n) | 16.2 / 15.2 |
| Mochila fraccionaria, selección | `fract-knapsack/fkp-2.c` | `fractionalKnapsack` | E = Θ(n) | Ej. 16.2-6 |
| Huffman | `huffman/huffman.c` | `huffman`, `huffmanCodes`, `freeHuffman` | O(n log n) | 16.3 / 15.3 |
| Cambio de monedas, voraz | `coin-changing/ccp-1.c` | `greedyChange` | O(k) | Prob. 16-1 |
| Cambio de monedas, DP | `coin-changing/ccp-2.c` | `dpChange` | Θ(kA) | Prob. 16-1 |
| Sistema canónico (Kozen y Zaks) | `coin-changing/ccp-3.c` | `isCanonical` | O(k(c₁+c₂)) | |
| Saltos mínimos, recursiva | `min-jumps/mjp-1.c` | `minJumps` | exp. | |
| Saltos mínimos, DP | `min-jumps/mjp-2.c` | `minJumps` | Θ(n²) | |
| Saltos mínimos, voraz | `min-jumps/mjp-3.c` | `minJumps` | Θ(n) | |

Las actividades deben estar ordenadas por tiempo de fin y las monedas en orden descendente.

## Grafos (`algorithms/graphs`)

| Problema | Archivo | Función | Tiempo | CLRS |
|---|---|---|---|---|
| BFS | `bfs/bfs.c` | `bfs` | Θ(V+E) | 22.2 / 20.2 |
| DFS con clasificación de aristas | `dfs/dfs.c` | `dfs` | Θ(V+E) | 22.3 / 20.3 |
| Orden topológico | `top-sort/tps.c` | `topologicalSort` | Θ(V+E) | 22.4 / 20.4 |
| SCC (Kosaraju) | `scc/scc.c` | `stronglyConnectedComponents` | Θ(V+E) | 22.5 / 20.5 |
| MST Kruskal | `MST-kruskal/kruskal.c` | `kruskal` | O(E log E) | 23.2 / 21.2 |
| MST Prim, heap binario | `MST-prim/prim-1.c` | `prim` | O(E log V) | 23.2 / 21.2 |
| MST Prim, heap de Fibonacci | `MST-prim/prim-2.c` | `prim` | O(E + V log V) | 23.2 / 21.2 |
| Bellman-Ford | `SSSP-bellman-ford/bfa.c` | `bellmanFord` | Θ(VE) | 24.1 / 22.1 |
| Caminos mínimos en DAG | `SSSP-DAG/dsp.c` | `dagShortestPaths` | Θ(V+E) | 24.2 / 22.2 |
| Dijkstra, heap binario | `SSSP-dijkstra/dijkstra-1.c` | `dijkstra` | O(E log V) | 24.3 / 22.3 |
| Dijkstra, heap de Fibonacci | `SSSP-dijkstra/dijkstra-2.c` | `dijkstra` | O(E + V log V) | 24.3 / 22.3 |
| APSP por productos | `APSP-matrix-mult/apsp-1.c` | `slowAllPairsShortestPaths` | Θ(V⁴) | 25.1 / 23.1 |
| APSP por cuadrados repetidos | `APSP-matrix-mult/apsp-2.c` | `fasterAllPairsShortestPaths` | Θ(V³ log V) | 25.1 / 23.1 |
| Floyd-Warshall | `APSP-floyd/floyd.c` | `floydWarshall` | Θ(V³) | 25.2 / 23.2 |
| Cierre transitivo vía distancias | `APSP-transitive-closure/trc-1.c` | `transitiveClosureByDistances` | Θ(V³) | 25.2 / 23.2 |
| Cierre transitivo booleano | `APSP-transitive-closure/trc-2.c` | `transitiveClosure` | Θ(V³) | 25.2 / 23.2 |
| Johnson | `APSP-johnson/johnson.c` | `johnson` | O(VE log V) | 25.3 / 23.3 |
| Flujo máximo, Edmonds-Karp | `MF-Edmonds-Karp/emk.c` | `edmondsKarp` | O(VE²) | 26.2 / 24.2 |
| Flujo máximo, escalado de capacidad | `MF-cap-scaling/scaling.c` | `capacityScaling` | O(E² log C) | Prob. 26-5 / 24-5 |
| Flujo máximo, Dinic | `MF-dinitz/dinitz.c` | `dinic` | O(V²E) | |
| Flujo máximo, push-relabel genérico (FIFO) | `MF-push-relabel/prm-1.c` | `genericPushRelabel` | O(V³) | 26.4 |
| Flujo máximo, relabel-to-front | `MF-push-relabel/prm-2.c` | `relabelToFront` | O(V³) | 26.5 |
| Emparejamiento bipartito máximo vía Dinic | `MCBM-dinitz/dinitz.c` | `maxBipartiteMatching` | O(E√V) | 26.3 / 24.3 |
| Hopcroft-Karp | `MCBM-hopcroft-karp/hck.c` | `hopcroftKarp` | O(E√V) | Prob. 26-6 / 25.1 |
| Matrimonio estable (Gale-Shapley) | `MCBM-gale-shapley/gale-shapley.c` | `galeShapley` | Θ(n²) | 4.ª ed. 25.2 |
| Emparejamiento de coste mínimo (SSP) | `MCBM-mcmf/mcmf.c` | `minCostBipartiteMatching` | O(V·VE) | |
| Húngaro (peso máximo) | `MCBM-hungarian/hungarian.c` | `hungarian` | Θ(n³) | 4.ª ed. 25.3 |
| Camino euleriano, Hierholzer | `ETP-Hierholzer/hierholzer.c` | `hierholzer` | Θ(V+E) | Prob. 22-3 / 20-3 |
| Camino euleriano, Fleury | `ETP-fleury/fleury.c` | `fleury` | O(E²) | |

Los algoritmos de flujo usan capacidades `long` y devuelven el flujo máximo. Si `flow` no es `NULL`, también escriben el flujo de cada arista.

`bellmanFord`, `floydWarshall`, `johnson` y las dos versiones de APSP por productos devuelven `false` si hay un ciclo negativo.

`hungarian` recibe una matriz de pesos `n×n` y maximiza. Para minimizar hay que negar los pesos.

## Búsqueda de patrones (`algorithms/string-matching`)

| Algoritmo | Archivo | Funciones | Tiempo | CLRS |
|---|---|---|---|---|
| Ingenuo | `naive-matching/nsm.c` | `naiveStringMatcher` | O((n−m+1)m) | 32.1 |
| Rabin-Karp (q = 10⁹+7) | `rabin-karp/rka.c` | `rabinKarpMatcher` | E = O(n+m) | 32.2 |
| Autómata finito | `finite-automata/sma.c` | `computeTransitionFunction`, `finiteAutomatonMatcher` | O(m³\|Σ\|) + Θ(n) | 32.3 |
| Knuth-Morris-Pratt | `knuth-morris-pratt/kmp.c` | `computePrefixFunction`, `kmpMatcher` | Θ(n+m) | 32.4 |
| Arreglo de sufijos y LCP (Kasai) | `suffix-arrays/sa.c` | `suffixArray`, `lcpArray`, `suffixArrayMatch` | O(n log n), consulta O(m log n) | 4.ª ed. 32.5 |

Los buscadores escriben los desplazamientos válidos en `shifts` y devuelven cuántos encontraron.

## FFT (`algorithms/fft`)

| Algoritmo | Archivo | Funciones | Tiempo | CLRS |
|---|---|---|---|---|
| FFT iterativa sobre ℂ | `fft.c` | `fft`, `polyMultiply` | Θ(n log n) | 30.3 |
| NTT mod 998244353 | `ntt.c` | `ntt`, `polyMultiplyMod` | Θ(n log n) | 30.3 |

## Estructuras de datos (`datastructures`)

| Estructura | Archivos | Operaciones | CLRS |
|---|---|---|---|
| Pila (arreglo dinámico) | `stacks/stack.{h,c}` | `stackPush`, `stackPop`, `stackTop`, `stackIsEmpty` | 10.1 |
| Cola (búfer circular) | `queues/queue.{h,c}` | `enqueue`, `dequeue`, `queuePeek`, `queueIsEmpty` | 10.1 |
| Lista doble con centinela | `lists/dll.{h,c}` | `listSearch`, `listPrepend`, `listAppend`, `listDelete` | 10.2 |
| Tabla hash de un valor por clave | `htables/single-value/map.{h,c}` | `mapPut`, `mapGet`, `mapDelete` | 11.2 |
| Tabla hash de varios valores por clave | `htables/multi-value/htable.{h,c}` | `htAdd`, `htGet`, `htDeleteValue`, `htDeleteKey` | 11.2 |
| BST | `trees/bstrees/bst.{h,c}` | `bstInsert`, `bstDelete`, `bstSearch`, `bstMinimum`, `bstMaximum`, `bstSuccessor`, `bstPredecessor` | 12 |
| Árbol rojo-negro | `trees/rbtrees/rbt.{h,c}` | `rbtInsert`, `rbtDelete`, `rbtSearch`, `rbtMinimum`, `rbtMaximum`, `rbtSuccessor`, `rbtPredecessor` | 13 |
| Max-heap binario | `heaps/binheaps/binheap.{h,c}` | `buildMaxHeap`, `maxHeapify`, `heapMaximum`, `heapExtractMax`, `heapIncreaseKey`, `maxHeapInsert` | 6 |
| Cola de prioridad mín. indexada | `heaps/bpqueues/bpqueue.{h,c}` | `pqInsert`, `pqMinimum`, `pqExtractMin`, `pqDecreaseKey`, `pqDelete`, `pqContains` | 6.5 |
| Heap de Fibonacci | `heaps/fibheaps/fibheap.{h,c}` | `fibInsert`, `fibMinimum`, `fibUnion`, `fibExtractMin`, `fibDecreaseKey`, `fibDelete` | 19 |
| Conjuntos disjuntos | `union-find/unionFind.{h,c}` | `ufFindSet`, `ufUnion`, `ufSameSet` | 21 / 19 |
| Grafo, matriz de adyacencia | `graphs/amatrix/graph.{h,c}` | `graphAddEdge`, `graphDelEdge`, `graphHasEdge`, `graphWeight`, `graphTranspose` | 22.1 / 20.1 |
| Grafo, listas de adyacencia | `graphs/graph/graph.{h,c}` | `graphAddEdge`, `graphDelEdge`, `graphGetEdge`, `graphTranspose` | 22.1 / 20.1 |
| Red de flujo (arcos residuales `a ^ 1`) | `graphs/network/network.{h,c}` | `networkAddEdge`, `residualCapacity`, `pushFlow`, `flowValue` | 26.1 / 24.1 |

Las tablas hash usan encadenamiento, FNV-1a y rehash al duplicar cuando el factor de carga supera 1. La unión por conjuntos usa rango y compresión de caminos.

## Referencias

- CLRS³: Cormen, Leiserson, Rivest, Stein. *Introduction to Algorithms*, 3.ª ed., MIT Press, 2009.
- CLRS⁴: Cormen, Leiserson, Rivest, Stein. *Introduction to Algorithms*, 4.ª ed., MIT Press, 2022.
- Halim, Halim, Effendy. *Competitive Programming 4*, 2022.
- Erickson. *Algorithms*, 2019.
