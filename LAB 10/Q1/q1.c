/*
 * Lab 10 - Question 1: Online Graph-Bipartiteness Testing
 *
 * Problem Statement:
 * A graph is bipartite if and only if it contains no odd-length cycles. Given an
 * undirected graph with V vertices, edges arrive online one by one. Maintain whether
 * the graph remains bipartite. If adding an edge (u, v) does not introduce an odd cycle,
 * add it; otherwise, report that it violates bipartiteness and skip it.
 * By choosing the proper input representation, write a program in C to validate your
 * algorithm and derive the complexity analysis of your algorithm.
 *
 * Algorithm:
 * 1. We maintain a Disjoint Set Union (DSU) data structure augmented with distance parity
 *    (parity-tracking / 2-coloring DSU).
 * 2. For each vertex x:
 *      - parent[x]: parent in the DSU forest.
 *      - parity[x]: color difference (0 or 1) between vertex x and parent[x]
 *                   (0: same color, 1: opposite color).
 *      - rank[x]  : tree height upper bound for union by rank.
 * 3. During find(x), path compression is applied, recursively updating parity:
 *      parity[x] = parity[x] ^ parity[old_parent].
 * 4. When an online edge (u, v) arrives:
 *    - Find roots: rootU = find(u), rootV = find(v).
 *    - If rootU == rootV:
 *        - If parity[u] == parity[v], u and v have the same partition color.
 *          Connecting them introduces an odd-length cycle, violating bipartiteness.
 *          The edge is rejected.
 *        - If parity[u] != parity[v], u and v have opposite colors. Adding the edge
 *          forms an even-length cycle, so bipartiteness is maintained.
 *    - If rootU != rootV:
 *        - Connect the two trees via union by rank.
 *        - Assign relative parity to link the roots:
 *          parity[rootU] = parity[u] ^ parity[v] ^ 1.
 *
 * Complexity Analysis:
 * - Time Complexity:
 *   - Initialization: O(V) to initialize parent, parity, and rank arrays.
 *   - Edge Processing: Each edge performs 2 find operations and at most 1 union operation.
 *     With path compression and union by rank, each operation takes O(alpha(V)) amortized
 *     time, where alpha is the Inverse Ackermann function.
 *   - Total Time for E online edges: O(V + E * alpha(V)) ~ O(V + E).
 * - Space Complexity:
 *   - O(V) auxiliary space for parent, parity, and rank arrays.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *parent;
    int *parity;
    int *rank;
    int n;
} DSU;

DSU* initDSU(int n) {
    DSU* dsu = (DSU*)malloc(sizeof(DSU));
    dsu->n = n;
    dsu->parent = (int*)malloc(n * sizeof(int));
    dsu->parity = (int*)calloc(n, sizeof(int));
    dsu->rank = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        dsu->parent[i] = i;
    }
    return dsu;
}

int find(DSU* dsu, int x) {
    if (dsu->parent[x] != x) {
        int p = dsu->parent[x];
        dsu->parent[x] = find(dsu, p);
        dsu->parity[x] ^= dsu->parity[p];
    }
    return dsu->parent[x];
}

bool addEdge(DSU* dsu, int u, int v) {
    int rootU = find(dsu, u);
    int rootV = find(dsu, v);

    if (rootU == rootV) {
        if (dsu->parity[u] == dsu->parity[v]) {
            return false;
        }
        return true;
    }

    if (dsu->rank[rootU] < dsu->rank[rootV]) {
        dsu->parent[rootU] = rootV;
        dsu->parity[rootU] = dsu->parity[u] ^ dsu->parity[v] ^ 1;
    } else {
        dsu->parent[rootV] = rootU;
        dsu->parity[rootV] = dsu->parity[u] ^ dsu->parity[v] ^ 1;
        if (dsu->rank[rootU] == dsu->rank[rootV]) {
            dsu->rank[rootU]++;
        }
    }
    return true;
}

void freeDSU(DSU* dsu) {
    free(dsu->parent);
    free(dsu->parity);
    free(dsu->rank);
    free(dsu);
}

int main(void) {
    int V, E;
    printf("Enter number of vertices (V) and edges (E): ");
    if (scanf("%d %d", &V, &E) != 2 || V <= 0) {
        return 1;
    }

    DSU* dsu = initDSU(V);

    printf("Enter %d edges (u v):\n", E);
    for (int i = 1; i <= E; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) break;

        if (u >= 1 && u <= V && v >= 1 && v <= V) {
            u--; v--;
        }

        if (addEdge(dsu, u, v)) {
            printf("Edge (%d, %d): Added (Bipartite maintained)\n", u + 1, v + 1);
        } else {
            printf("Edge (%d, %d): Rejected (Odd cycle detected)\n", u + 1, v + 1);
        }
    }

    freeDSU(dsu);
    return 0;
}
