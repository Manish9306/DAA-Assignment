/*
3. [Bidirectional BFS for Shortest Transformation Sequence in a Word Graph] You
are given:
- A dictionary D containing N unique words, where every word has the exact same
  length L.
- A starting word A and a target word B, both of length L.

A valid mutation step consists of changing exactly one character of a word such that the
resulting word exists in dictionary D. A transformation sequence from A to B is an
ordered sequence of words:
W0, W1, W2, ..., Wk
such that:
1. W0 = A and Wk = B.
2. Every intermediate word Wi ∈ D for all 1 ≤ i ≤ k. (Note: whether A must initially
   be in D is typically specified by the input constraints, but B must always be in D.)
3. For every adjacent pair (Wi-1, Wi), the two words differ by exactly one character (i.e.,
   their Hamming distance is 1).

Objective: Compute the minimum number of mutations k required to transform A into B.
If A cannot be transformed into B through valid intermediate words in D, return -1 (or
report that no valid path exists). Keep in mind to consider the following constraints for
this problem during implementation:
- N ≤ 10^5 (number of dictionary words)
- L ≤ 10 (length of each word)
- All words consist solely of lowercase English letters ('a' to 'z').

By choosing the proper input representation, write a program in C to validate your algo-
rithm and derive the complexity analysis of your algorithm.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 200003

struct HashNode {
    char word[16];
    int dist_fwd;
    int dist_bwd;
    struct HashNode* next;
};

struct HashNode* buckets[TABLE_SIZE];

unsigned int hash(const char* str) {
    unsigned long h = 5381;
    int c;
    while ((c = *str++)) {
        h = ((h << 5) + h) + c;
    }
    return (unsigned int)(h % TABLE_SIZE);
}

struct HashNode* insertOrGet(const char* word) {
    unsigned int idx = hash(word);
    struct HashNode* curr = buckets[idx];
    while (curr != NULL) {
        if (strcmp(curr->word, word) == 0) return curr;
        curr = curr->next;
    }
    struct HashNode* n = (struct HashNode*)malloc(sizeof(struct HashNode));
    strcpy(n->word, word);
    n->dist_fwd = -1;
    n->dist_bwd = -1;
    n->next = buckets[idx];
    buckets[idx] = n;
    return n;
}

struct HashNode* lookup(const char* word) {
    unsigned int idx = hash(word);
    struct HashNode* curr = buckets[idx];
    while (curr != NULL) {
        if (strcmp(curr->word, word) == 0) return curr;
        curr = curr->next;
    }
    return NULL;
}

struct Queue {
    struct HashNode** arr;
    int front;
    int rear;
    int size;
    int cap;
};

struct Queue* createQueue(int cap) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->arr = (struct HashNode**)malloc(cap * sizeof(struct HashNode*));
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->cap = cap;
    return q;
}

int isEmpty(struct Queue* q) {
    return q->size == 0;
}

void enqueue(struct Queue* q, struct HashNode* n) {
    q->arr[q->rear] = n;
    q->rear = (q->rear + 1) % q->cap;
    q->size++;
}

struct HashNode* dequeue(struct Queue* q) {
    struct HashNode* n = q->arr[q->front];
    q->front = (q->front + 1) % q->cap;
    q->size--;
    return n;
}

int solve(char* A, char* B, int L, int N) {
    if (strcmp(A, B) == 0) return 0;

    struct HashNode* nodeB = lookup(B);
    if (nodeB == NULL) return -1;

    struct HashNode* nodeA = insertOrGet(A);

    nodeA->dist_fwd = 0;
    nodeB->dist_bwd = 0;

    struct Queue* qA = createQueue(N + 10);
    struct Queue* qB = createQueue(N + 10);

    enqueue(qA, nodeA);
    enqueue(qB, nodeB);

    char temp[16];

    while (!isEmpty(qA) && !isEmpty(qB)) {
        struct Queue* curQ;
        int forward;

        if (qA->size <= qB->size) {
            curQ = qA;
            forward = 1;
        } else {
            curQ = qB;
            forward = 0;
        }

        int count = curQ->size;
        for (int i = 0; i < count; i++) {
            struct HashNode* cur = dequeue(curQ);
            int d = forward ? cur->dist_fwd : cur->dist_bwd;
            strcpy(temp, cur->word);

            for (int p = 0; p < L; p++) {
                char orig = temp[p];
                for (char c = 'a'; c <= 'z'; c++) {
                    if (c == orig) continue;
                    temp[p] = c;

                    struct HashNode* nbr = lookup(temp);
                    if (nbr != NULL) {
                        if (forward) {
                            if (nbr->dist_bwd != -1) {
                                int ans = d + 1 + nbr->dist_bwd;
                                free(qA->arr); free(qA);
                                free(qB->arr); free(qB);
                                return ans;
                            }
                            if (nbr->dist_fwd == -1) {
                                nbr->dist_fwd = d + 1;
                                enqueue(qA, nbr);
                            }
                        } else {
                            if (nbr->dist_fwd != -1) {
                                int ans = d + 1 + nbr->dist_fwd;
                                free(qA->arr); free(qA);
                                free(qB->arr); free(qB);
                                return ans;
                            }
                            if (nbr->dist_bwd == -1) {
                                nbr->dist_bwd = d + 1;
                                enqueue(qB, nbr);
                            }
                        }
                    }
                }
                temp[p] = orig;
            }
        }
    }

    free(qA->arr); free(qA);
    free(qB->arr); free(qB);
    return -1;
}

int main() {
    int N, L;
    printf("Enter number of dictionary words (N) and word length (L): ");
    if (scanf("%d %d", &N, &L) != 2 || N <= 0 || L <= 0) return 0;

    char A[16], B[16];
    printf("Enter start word A and target word B: ");
    scanf("%s %s", A, B);

    for (int i = 0; i < TABLE_SIZE; i++) {
        buckets[i] = NULL;
    }

    printf("Enter %d dictionary words:\n", N);
    for (int i = 0; i < N; i++) {
        char word[16];
        scanf("%s", word);
        insertOrGet(word);
    }

    int ans = solve(A, B, L, N);
    printf("\nMinimum mutations: %d\n", ans);

    for (int i = 0; i < TABLE_SIZE; i++) {
        struct HashNode* curr = buckets[i];
        while (curr != NULL) {
            struct HashNode* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }

    return 0;
}
