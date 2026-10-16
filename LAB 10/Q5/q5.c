/*
 * Lab 10 - Question 5: Lexicographically Smallest Connected Component Permutation
 * 
 * Problem Statement:
 * Given a permutation A of numbers 1 . . . n, and a list of allowable pairwise
 * swaps (u, v) forming edges in an undirected graph, find the lexicographically
 * smallest permutation achievable through any number of valid swaps. By choosing
 * the proper input representation, write a program in C to validate your algorithm
 * and derive the complexity analysis of your algorithm.
 *
 * Algorithm:
 * 1. Equivalence Relation and Graph Components:
 *    - Allowable pairwise swaps (u, v) can be performed arbitrarily many times.
 *    - Swap reachability is symmetric and transitive; hence, the swap pairs form
 *      an undirected graph whose connected components partition the indices
 *      {0, 1, ..., n-1} into independent equivalence classes.
 *    - Any permutation of values within the same connected component of indices
 *      can be achieved.
 * 2. Greedy Lexicographical Minimization:
 *    - To make the overall permutation lexicographically as small as possible,
 *      smaller indices must be assigned smaller values.
 *    - We use a Disjoint Set Union (DSU) to group indices into connected components.
 *    - For each connected component of indices C = {i_1, i_2, ..., i_k} (with i_1 < i_2 < ... < i_k):
 *        a. Extract the values currently residing at these positions: {A[i_1], ..., A[i_k]}.
 *        b. Sort the extracted values in ascending order: v_1 <= v_2 <= ... <= v_k.
 *        c. Assign the sorted values back into the sorted index positions:
 *           A[i_j] = v_j for all j = 1, ..., k.
 *
 * Complexity Analysis:
 * - Time Complexity:
 *   - DSU Initialization: O(n) time.
 *   - Processing m swap edges: O(m * alpha(n)) using path compression and union by rank.
 *   - Grouping indices into components: O(n) time.
 *   - Sorting within components:
 *       If component i has size k_i, sorting its values using qsort takes O(k_i * log(k_i)).
 *       Since sum(k_i) = n, the total sorting time satisfies:
 *         sum(k_i * log(k_i)) <= O(n * log(n)).
 *   - Total Time Complexity: O(n * log(n) + m * alpha(n)) ~ O(n log n + m).
 * - Space Complexity:
 *   - O(n) auxiliary space for DSU (parent, rank), component index grouping, and sorting buffer.
 */

#include <stdio.h>
#include <stdlib.h>

int *parent;
int *rankArr;

int find(int i) {
    if (parent[i] != i) {
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

void unite(int i, int j) {
    int rootI = find(i);
    int rootJ = find(j);
    if (rootI == rootJ) return;

    if (rankArr[rootI] < rankArr[rootJ]) {
        parent[rootI] = rootJ;
    } else if (rankArr[rootI] > rankArr[rootJ]) {
        parent[rootJ] = rootI;
    } else {
        parent[rootJ] = rootI;
        rankArr[rootI]++;
    }
}

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main(void) {
    int n, m;
    printf("Enter permutation size (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    int *A = (int*)malloc(n * sizeof(int));
    printf("Enter permutation of %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    parent = (int*)malloc(n * sizeof(int));
    rankArr = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    printf("Enter number of allowable swaps (m): ");
    if (scanf("%d", &m) != 1 || m < 0) {
        return 1;
    }

    printf("Enter %d swap pairs (u v):\n", m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 1 && u <= n && v >= 1 && v <= n) {
            u--; v--;
        }
        unite(u, v);
    }

    int *compSize = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        compSize[find(i)]++;
    }

    int **compIndices = (int**)calloc(n, sizeof(int*));
    int *ptr = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        if (compSize[i] > 0) {
            compIndices[i] = (int*)malloc(compSize[i] * sizeof(int));
        }
    }

    for (int i = 0; i < n; i++) {
        int r = find(i);
        compIndices[r][ptr[r]++] = i;
    }

    int *vals = (int*)malloc(n * sizeof(int));
    for (int r = 0; r < n; r++) {
        if (compSize[r] > 1) {
            int k = compSize[r];
            for (int j = 0; j < k; j++) {
                vals[j] = A[compIndices[r][j]];
            }

            qsort(vals, k, sizeof(int), cmp);

            for (int j = 0; j < k; j++) {
                A[compIndices[r][j]] = vals[j];
            }
        }
    }

    printf("\nLexicographically Smallest Permutation:\n");
    for (int i = 0; i < n; i++) {
        printf("%d%c", A[i], (i == n - 1 ? '\n' : ' '));
    }

    free(vals);
    for (int i = 0; i < n; i++) {
        if (compIndices[i]) free(compIndices[i]);
    }
    free(compIndices);
    free(ptr);
    free(compSize);
    free(parent);
    free(rankArr);
    free(A);

    return 0;
}
