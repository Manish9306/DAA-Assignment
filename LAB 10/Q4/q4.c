/*
 * Lab 10 - Question 4: Reverse Time-Step DSU Application (Sequential Vertex Deletions)
 * 
 * Problem Statement:
 * Given a vertex-weighted undirected graph, vertices are sequentially deleted
 * one by one in an order P = [p1, p2, . . . , pV]. After each vertex deletion,
 * compute the maximum sum of vertex values among all remaining connected components.
 * Note that deleting a vertex in a graph means removing that specific vertex and
 * all edges connected (incident) to it from the graph structure. By choosing the
 * proper input representation, write a program in C to validate your algorithm
 * and derive the complexity analysis of your algorithm.
 *
 * Algorithm:
 * 1. Graph Input Representation:
 *    - An Adjacency List is used to represent the graph in O(V + E) space, allowing
 *      iteration over incident edges of any vertex u in O(deg(u)) time.
 * 2. Offline Reverse Time-Step Strategy:
 *    - Deleting vertices splits components, which is expensive to maintain dynamically.
 *    - However, vertex deletions in forward order P = [p1, p2, ..., pV] can be modeled
 *      in reverse as sequential vertex additions from an initially empty graph.
 *    - After all V vertices are deleted, the graph is empty (max component sum = 0).
 *    - We iterate backwards from i = V - 1 down to 0:
 *        a. The answer after deleting vertices {p1, ..., pi} equals the current
 *           maximum component sum among already restored vertices {p_{i+1}, ..., pV}.
 *           Record ans[i + 1] = curMax.
 *        b. Activate vertex u = p[i]:
 *           Mark active[u] = true, set compWeight[u] = weight[u], and update
 *           curMax = max(curMax, compWeight[u]).
 *        c. Traverse all neighbors v of u in the adjacency list.
 *           If active[v] is true and find(u) != find(v):
 *             Unite the components of u and v using union by rank.
 *             Update the merged root's weight: compWeight[newRoot] = compWeight[rootU] + compWeight[rootV].
 *             Update curMax = max(curMax, compWeight[newRoot]).
 *    - Print the recorded answers in forward order for each deletion step 1 to V.
 *
 * Complexity Analysis:
 * - Time Complexity:
 *   - Adjacency List Construction: O(V + E) time.
 *   - Reverse DSU Processing:
 *       Each vertex is activated exactly once.
 *       Each edge (u, v) is checked at most twice (when each endpoint is activated).
 *       With path compression and union by rank, DSU find and union operations
 *       take amortized O(alpha(V)) time.
 *   - Total Time Complexity: O(V + E * alpha(V)) ~ O(V + E), which is nearly linear.
 * - Space Complexity:
 *   - Adjacency list: O(V + E) space.
 *   - DSU arrays (parent, rank, compWeight), active flags, and ans array: O(V) space.
 *   - Total Auxiliary Space: O(V + E).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int dest;
    struct Node* next;
} Node;

Node** adj;

void addEdge(int u, int v) {
    Node* n1 = (Node*)malloc(sizeof(Node));
    n1->dest = v;
    n1->next = adj[u];
    adj[u] = n1;

    Node* n2 = (Node*)malloc(sizeof(Node));
    n2->dest = u;
    n2->next = adj[v];
    adj[v] = n2;
}

int *parent;
int *rankArr;
int *compWeight;
bool *active;

int find(int i) {
    if (parent[i] != i) {
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

int unite(int i, int j) {
    int rootI = find(i);
    int rootJ = find(j);
    if (rootI == rootJ) return rootI;

    if (rankArr[rootI] < rankArr[rootJ]) {
        parent[rootI] = rootJ;
        compWeight[rootJ] += compWeight[rootI];
        return rootJ;
    } else if (rankArr[rootI] > rankArr[rootJ]) {
        parent[rootJ] = rootI;
        compWeight[rootI] += compWeight[rootJ];
        return rootI;
    } else {
        parent[rootJ] = rootI;
        compWeight[rootI] += compWeight[rootJ];
        rankArr[rootI]++;
        return rootI;
    }
}

int main(void) {
    int V, E;
    printf("Enter number of vertices (V) and edges (E): ");
    if (scanf("%d %d", &V, &E) != 2 || V <= 0) {
        return 1;
    }

    int *weight = (int*)malloc(V * sizeof(int));
    printf("Enter weights of vertices 1 to %d:\n", V);
    for (int i = 0; i < V; i++) {
        scanf("%d", &weight[i]);
    }

    adj = (Node**)calloc(V, sizeof(Node*));
    printf("Enter %d edges (u v):\n", E);
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 1 && u <= V && v >= 1 && v <= V) {
            u--; v--;
        }
        addEdge(u, v);
    }

    int *p = (int*)malloc(V * sizeof(int));
    printf("Enter deletion sequence of %d vertices:\n", V);
    for (int i = 0; i < V; i++) {
        scanf("%d", &p[i]);
        if (p[i] >= 1 && p[i] <= V) {
            p[i]--;
        }
    }

    parent = (int*)malloc(V * sizeof(int));
    rankArr = (int*)calloc(V, sizeof(int));
    compWeight = (int*)malloc(V * sizeof(int));
    active = (bool*)calloc(V, sizeof(bool));

    for (int i = 0; i < V; i++) {
        parent[i] = i;
        compWeight[i] = weight[i];
    }

    int *ans = (int*)malloc((V + 1) * sizeof(int));
    int curMax = 0;
    ans[V] = 0;

    for (int i = V - 1; i >= 0; i--) {
        ans[i + 1] = curMax;

        int u = p[i];
        active[u] = true;
        if (compWeight[u] > curMax) {
            curMax = compWeight[u];
        }

        Node* cur = adj[u];
        while (cur) {
            int v = cur->dest;
            if (active[v]) {
                int r1 = find(u);
                int r2 = find(v);
                if (r1 != r2) {
                    int nr = unite(r1, r2);
                    if (compWeight[nr] > curMax) {
                        curMax = compWeight[nr];
                    }
                }
            }
            cur = cur->next;
        }
    }

    printf("\n--- Results ---\n");
    for (int i = 1; i <= V; i++) {
        printf("After deleting vertex %d: Max component sum = %d\n", p[i - 1] + 1, ans[i]);
    }

    for (int i = 0; i < V; i++) {
        Node* cur = adj[i];
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(adj);
    free(weight);
    free(p);
    free(ans);
    free(parent);
    free(rankArr);
    free(compWeight);
    free(active);

    return 0;
}
