/*
2. [Multi-Source BFS for Radius-Constrained Voronoi Cell Partitioning] You are
given:
- An unweighted, undirected graph G = (V, E).
- A set of K designated hub vertices H = {h1, h2, ..., hK} ⊆ V, indexed from 1 to K.
- An integer radius threshold R ≥ 0.

Let dist(u, v) denote the shortest path distance (minimum number of edges) between vertices
u and v in G.

For every vertex v ∈ V, assign an ownership label owner[v] ∈ {1, 2, ..., K} ∪ {-1} according
to the following rules:
1. Distance Metric: Find the distance from v to each service hub: di = dist(v, hi) for all
   i ∈ {1, ..., K}. Let dmin(v) = min_{1≤i≤K} di.
2. Reachability Threshold (R): If dmin(v) > R, vertex v lies outside the service coverage
   area. Set owner[v] = -1.
3. Closest Hub Assignment: If dmin(v) ≤ R, assign v to the hub hi that minimizes di.
4. Deterministic Tie-Breaking: If multiple hubs achieve the exact same minimum distance
   dmin(v), choose the hub with the smallest numerical index i.

Objective: Output the array owner[1 ... |V|] containing the assigned hub index (or -1
if unassigned) and the corresponding shortest distance to that hub for every vertex. By
choosing the proper input representation, write a program in C to validate your algorithm
and derive the complexity analysis of your algorithm.
*/

#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

struct Node {
    int v;
    struct Node* next;
};

void addEdge(struct Node** adj, int u, int v) {
    struct Node* n1 = (struct Node*)malloc(sizeof(struct Node));
    n1->v = v;
    n1->next = adj[u];
    adj[u] = n1;

    struct Node* n2 = (struct Node*)malloc(sizeof(struct Node));
    n2->v = u;
    n2->next = adj[v];
    adj[v] = n2;
}

struct Queue {
    int* arr;
    int front;
    int rear;
    int size;
    int cap;
};

struct Queue* createQueue(int cap) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->arr = (int*)malloc(cap * sizeof(int));
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->cap = cap;
    return q;
}

int isEmpty(struct Queue* q) {
    return q->size == 0;
}

void enqueue(struct Queue* q, int val) {
    q->arr[q->rear] = val;
    q->rear = (q->rear + 1) % q->cap;
    q->size++;
}

int dequeue(struct Queue* q) {
    int val = q->arr[q->front];
    q->front = (q->front + 1) % q->cap;
    q->size--;
    return val;
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges (V E): ");
    if (scanf("%d %d", &V, &E) != 2 || V <= 0) return 0;

    struct Node** adj = (struct Node**)calloc(V + 1, sizeof(struct Node*));
    printf("Enter %d edges (u v):\n", E);
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(adj, u, v);
    }

    int K;
    printf("Enter number of hubs (K): ");
    if (scanf("%d", &K) != 1 || K <= 0) return 0;

    int* hubs = (int*)malloc((K + 1) * sizeof(int));
    printf("Enter %d hub vertices:\n", K);
    for (int i = 1; i <= K; i++) {
        scanf("%d", &hubs[i]);
    }

    int R;
    printf("Enter radius threshold (R): ");
    if (scanf("%d", &R) != 1 || R < 0) return 0;

    int* dist = (int*)malloc((V + 1) * sizeof(int));
    int* owner = (int*)malloc((V + 1) * sizeof(int));
    for (int i = 1; i <= V; i++) {
        dist[i] = INF;
        owner[i] = -1;
    }

    struct Queue* q = createQueue(V + 5);

    for (int i = 1; i <= K; i++) {
        int h = hubs[i];
        if (h >= 1 && h <= V) {
            if (dist[h] == INF) {
                dist[h] = 0;
                owner[h] = i;
                enqueue(q, h);
            }
        }
    }

    while (!isEmpty(q)) {
        int u = dequeue(q);

        if (dist[u] == R) {
            continue;
        }

        struct Node* curr = adj[u];
        while (curr != NULL) {
            int v = curr->v;
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                owner[v] = owner[u];
                enqueue(q, v);
            }
            curr = curr->next;
        }
    }

    printf("\nVertex\towner\tdist\n");
    printf("---------------------------\n");
    for (int v = 1; v <= V; v++) {
        if (owner[v] == -1) {
            printf("%d\t-1\t-1\n", v);
        } else {
            printf("%d\t%d\t%d\n", v, owner[v], dist[v]);
        }
    }

    for (int i = 1; i <= V; i++) {
        struct Node* curr = adj[i];
        while (curr != NULL) {
            struct Node* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(adj);
    free(hubs);
    free(dist);
    free(owner);
    free(q->arr);
    free(q);

    return 0;
}
