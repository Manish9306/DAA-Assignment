/*
 * Lab 10 - Question 3: Maximum Weight Component with Size Constraints (<= K)
 * 
 * Problem Statement:
 * Given a graph where each vertex v has weight wv, edges are added sequentially
 * with weights. At any point, compute the maximum total vertex weight of any
 * connected component whose size does not exceed a threshold K. By choosing the
 * proper input representation, write a program in C to validate your algorithm
 * and derive the complexity analysis of your algorithm.
 *
 * Algorithm:
 * 1. Data Structure Representation:
 *    - DSU arrays:
 *        parent[v]     : parent pointer in DSU forest.
 *        sz[root]      : number of vertices in connected component.
 *        compWeight[r] : sum of vertex weights in connected component.
 *        version[r]    : monotonic version counter used to invalidate outdated heap entries.
 *    - Binary Max-Heap:
 *        Stores tuples (weight, root, version) for active components whose size <= K.
 * 2. Dynamic Component Merging & Maintenance:
 *    - Initially, every single vertex forms a component of size 1 with weight wv.
 *      If 1 <= K, each initial component is pushed to the Max-Heap with version 1.
 *    - When an edge (u, v) arrives:
 *        a. Find component roots rootU = find(u), rootV = find(v).
 *        b. If rootU != rootV, merge smaller component into larger (union by size).
 *        c. Let rootU be the merged root:
 *             sz[rootU] += sz[rootV]
 *             compWeight[rootU] += compWeight[rootV]
 *             version[rootU]++, version[rootV]++
 *        d. If sz[rootU] <= K, push the newly formed component (compWeight[rootU], rootU, version[rootU])
 *           into the Max-Heap.
 * 3. Querying the Maximum Valid Weight:
 *    - Inspect the top of the Max-Heap using Lazy Deletion:
 *      Pop elements where parent[root] != root (no longer a root), version[root] != top.version
 *      (stale component data), or sz[root] > K (exceeded threshold).
 *    - The first valid element at the top gives the maximum component weight.
 *
 * Complexity Analysis:
 * - Time Complexity:
 *   - Initialization: O(V) to initialize arrays and push V elements into heap.
 *   - DSU Operations: Path compression and union by size take O(alpha(V)) per edge.
 *   - Max-Heap Operations: Each edge causes at most 1 push into the heap. Across all
 *     operations, at most (V + E) items are inserted and popped from the heap.
 *     Each heap push/pop takes O(log(V + E)).
 *   - Total Time Complexity: O(V + E * log(V + E)) ~ O((V + E) log V).
 * - Space Complexity:
 *   - DSU arrays: O(V) space.
 *   - Max-Heap storage: O(V + E) space.
 *   - Total Auxiliary Space: O(V + E).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int weight;
    int root;
    int version;
} HeapNode;

HeapNode *heap;
int heapSize = 0;

void swap(HeapNode *a, HeapNode *b) {
    HeapNode t = *a;
    *a = *b;
    *b = t;
}

void pushHeap(int weight, int root, int version) {
    int i = heapSize++;
    heap[i].weight = weight;
    heap[i].root = root;
    heap[i].version = version;

    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[i].weight > heap[p].weight) {
            swap(&heap[i], &heap[p]);
            i = p;
        } else {
            break;
        }
    }
}

void popHeap() {
    heap[0] = heap[--heapSize];
    int i = 0;
    while (2 * i + 1 < heapSize) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < heapSize && heap[left].weight > heap[largest].weight) {
            largest = left;
        }
        if (right < heapSize && heap[right].weight > heap[largest].weight) {
            largest = right;
        }
        if (largest != i) {
            swap(&heap[i], &heap[largest]);
            i = largest;
        } else {
            break;
        }
    }
}

int *parent;
int *sz;
int *compWeight;
int *version;

int find(int i) {
    if (parent[i] != i) {
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

int main(void) {
    int V, E, K;
    printf("Enter V, E and size threshold K: ");
    if (scanf("%d %d %d", &V, &E, &K) != 3 || V <= 0 || K <= 0) {
        return 1;
    }

    parent = (int*)malloc(V * sizeof(int));
    sz = (int*)malloc(V * sizeof(int));
    compWeight = (int*)malloc(V * sizeof(int));
    version = (int*)malloc(V * sizeof(int));
    heap = (HeapNode*)malloc((V + 2 * E + 5) * sizeof(HeapNode));

    printf("Enter vertex weights (w_1 to w_%d):\n", V);
    for (int i = 0; i < V; i++) {
        scanf("%d", &compWeight[i]);
        parent[i] = i;
        sz[i] = 1;
        version[i] = 1;

        if (1 <= K) {
            pushHeap(compWeight[i], i, version[i]);
        }
    }

    printf("Enter %d edges (u v weight):\n", E);
    for (int step = 1; step <= E; step++) {
        int u, v, w;
        if (scanf("%d %d %d", &u, &v, &w) != 3) break;

        if (u >= 1 && u <= V && v >= 1 && v <= V) {
            u--; v--;
        }

        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            if (sz[rootU] < sz[rootV]) {
                int temp = rootU;
                rootU = rootV;
                rootV = temp;
            }

            parent[rootV] = rootU;
            sz[rootU] += sz[rootV];
            compWeight[rootU] += compWeight[rootV];
            version[rootU]++;
            version[rootV]++;

            if (sz[rootU] <= K) {
                pushHeap(compWeight[rootU], rootU, version[rootU]);
            }
        }

        while (heapSize > 0) {
            int r = heap[0].root;
            if (parent[r] == r && version[r] == heap[0].version && sz[r] <= K) {
                break;
            }
            popHeap();
        }

        if (heapSize > 0) {
            printf("Step %d: Edge (%d, %d) added -> Max Weight (size <= %d): %d\n",
                   step, u + 1, v + 1, K, heap[0].weight);
        } else {
            printf("Step %d: Edge (%d, %d) added -> No component has size <= %d\n",
                   step, u + 1, v + 1, K);
        }
    }

    free(parent);
    free(sz);
    free(compWeight);
    free(version);
    free(heap);
    return 0;
}
