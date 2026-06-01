# ADA Lab Exam Programs

This repository contains separate, self-contained C11 programs for common
algorithm design and analysis lab topics. Each `.c` file has its own `main()`
function, hard-coded test cases, labeled output, and comments explaining the
algorithm, complexity, and walkthrough.

## Compile

Compile any program individually:

```sh
gcc -Wall -Wextra -std=c11 01_naive_string_matching.c -o naive_string_matching
./naive_string_matching
```

Compile all programs into a temporary build folder:

```sh
mkdir -p build
for file in *.c; do
    gcc -Wall -Wextra -std=c11 "$file" -o "build/${file%.c}"
done
```

## Programs

| No. | File | Algorithm |
| --- | --- | --- |
| 01 | `01_naive_string_matching.c` | String Matching - Naive Pattern Matching |
| 02 | `02_tsp_exhaustive.c` | Travelling Salesman Problem - Exhaustive Search |
| 03 | `03_knapsack_exhaustive.c` | Knapsack Problem - Exhaustive Search |
| 04 | `04_assignment_exhaustive.c` | Assignment Problem - Exhaustive Search |
| 05 | `05_topological_sort_kahn.c` | Topological Sorting - Kahn's Algorithm |
| 06 | `06_johnson_trotter.c` | Generating Permutations - Johnson-Trotter Algorithm |
| 07 | `07_russian_peasant_multiplication.c` | Russian Peasant Multiplication |
| 08 | `08_median_selection_deterministic.c` | Median and Selection - Deterministic Quickselect |
| 09 | `09_merge_sort.c` | Merge Sort |
| 10 | `10_quicksort.c` | Quicksort |
| 11 | `11_long_integer_multiplication.c` | Multiplication of Long Integers using Arrays |
| 12 | `12_strassen_matrix_multiplication.c` | Strassen's Matrix Multiplication |
| 13 | `13_presorting_duplicate_detection.c` | Presorting for Duplicate Detection |
| 14 | `14_heap_sort.c` | Heaps and Heap Sort |
| 15 | `15_horners_rule.c` | Horner's Rule |
| 16 | `16_coin_change_dp.c` | Coin Problem - Minimum Coins using Dynamic Programming |
| 17 | `17_knapsack_dp.c` | 0/1 Knapsack Problem - Dynamic Programming |
| 18 | `18_warshall_transitive_closure.c` | Warshall's Algorithm |
| 19 | `19_floyd_all_pairs_shortest_paths.c` | Floyd's Algorithm |
| 20 | `20_prim_mst.c` | Prim's Algorithm |
| 21 | `21_kruskal_mst.c` | Kruskal's Algorithm |
| 22 | `22_dijkstra_adjacency_matrix.c` | Dijkstra's Algorithm |
| 23 | `23_huffman_coding.c` | Huffman Coding |
| 24 | `24_fractional_knapsack.c` | Fractional Knapsack Problem |
| 25 | `25_n_queens_backtracking.c` | n-Queens Problem |
| 26 | `26_subset_sum_backtracking.c` | Subset-Sum Problem |
| 27 | `27_knapsack_branch_and_bound.c` | Knapsack Problem - Branch and Bound |
| 28 | `28_tsp_branch_and_bound.c` | Travelling Salesman Problem - Branch and Bound |

## Notes

- All programs use only standard C headers.
- The examples are intentionally small so outputs can be visually verified.
- Graph programs print the input graph and the computed result.
- Optimization programs print both the optimal value and the selected solution.
