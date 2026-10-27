/*
1. [Shortest Path on Parity-Constrained Graphs via 0-1 BFS] You are given a directed
graph G = (V, E), a designated source vertex S ∈ V, and an extra penalty cost C ≥ 0.
Every directed edge (u, v) ∈ E has a weight w(u, v) ∈ {0, 1}.
For any path P from S to a vertex v:
1. Let W(P) denote the sum of all edge weights along P.
2. Let k1(P) denote the total count of weight-1 edges traversed in P.
3. The effective cost of path P is defined as:
Cost(P) = W(P) + { 0, if k1(P) is even
                 { C, if k1(P) is odd

Objective: For every vertex v ∈ V, compute the minimum possible Cost(P) among all valid
paths from S to v. If a node v cannot be reached from S, report that it is unreachable. By
choosing the proper input representation, write a program in C to validate your algorithm
and derive the complexity analysis of your algorithm.
*/

#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

struct Edge {
    int to;
    int weight;
    struct Edge* next;
};

struct State {
    int u;
    int parity;
};

struct Deque {
    struct State* arr;
    int front;
    int rear;
    int size;
    int cap;
};

struct Deque* createDeque(int cap) {
    struct Deque* dq = (struct Deque*)malloc(sizeof(struct Deque));
    dq->arr = (struct State*)malloc(sizeof(struct State) * cap);
    dq->front = 0;
    dq->rear = 0;
    dq->size = 0;
    dq->cap = cap;
    return dq;
}

int isEmpty(struct Deque* dq) {
    return dq->size == 0;
}

void push_front(struct Deque* dq, struct State s) {
    dq->front = (dq->front - 1 + dq->cap) % dq->cap;
    dq->arr[dq->front] = s;
    dq->size++;
}

void push_back(struct Deque* dq, struct State s) {
    dq->arr[dq->rear] = s;
    dq->rear = (dq->rear + 1) % dq->cap;
    dq->size++;
}

struct State pop_front(struct Deque* dq) {
    struct State s = dq->arr[dq->front];
    dq->front = (dq->front + 1) % dq->cap;
    dq->size--;
    return s;
}

void addEdge(struct Edge** adj, int u, int v, int w) {
    struct Edge* e = (struct Edge*)malloc(sizeof(struct Edge));
    e->to = v;
    e->weight = w;
    e->next = adj[u];
    adj[u] = e;
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges (V E): ");
    if (scanf("%d %d", &V, &E) != 2 || V <= 0) return 0;

    int S, C;
    printf("Enter source vertex S and penalty cost C: ");
    if (scanf("%d %d", &S, &C) != 2) return 0;

    struct Edge** adj = (struct Edge**)calloc(V + 1, sizeof(struct Edge*));
    printf("Enter %d edges (u v w) where w is 0 or 1:\n", E);
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(adj, u, v, w);
    }

    int dist[V + 1][2];
    for (int i = 0; i <= V; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }

    int cap = (2 * E + 2 * V + 10);
    struct Deque* dq = createDeque(cap);

    dist[S][0] = 0;
    struct State start = {S, 0};
    push_back(dq, start);

    while (!isEmpty(dq)) {
        struct State cur = pop_front(dq);
        int u = cur.u;
        int p = cur.parity;

        struct Edge* e = adj[u];
        while (e != NULL) {
            int v = e->to;
            int w = e->weight;
            int next_p = (p + w) % 2;
            int new_d = dist[u][p] + w;

            if (new_d < dist[v][next_p]) {
                dist[v][next_p] = new_d;
                struct State nxt = {v, next_p};
                if (w == 0) {
                    push_front(dq, nxt);
                } else {
                    push_back(dq, nxt);
                }
            }
            e = e->next;
        }
    }

    int start_node = 1;
    if (S == 0 || dist[0][0] != INF || dist[0][1] != INF) {
        start_node = 0;
    }

    printf("\nVertex\tMinimum Cost\n");
    printf("--------------------\n");
    int end_node = (start_node == 0) ? V - 1 : V;
    for (int v = start_node; v <= end_node; v++) {
        int cost0 = dist[v][0];
        int cost1 = (dist[v][1] == INF) ? INF : dist[v][1] + C;
        int ans = cost0 < cost1 ? cost0 : cost1;

        if (ans >= INF) {
            printf("%d\tUnreachable\n", v);
        } else {
            printf("%d\t%d\n", v, ans);
        }
    }

    for (int i = 0; i <= V; i++) {
        struct Edge* cur = adj[i];
        while (cur != NULL) {
            struct Edge* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(adj);
    free(dq->arr);
    free(dq);

    return 0;
}
