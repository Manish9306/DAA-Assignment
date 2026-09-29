/*
8. [Optimal Binary Search Trees (OBST)] Given a set of n distinct sorted keys K =
<k1, k2, ..., kn> with search probabilities p1, p2, ..., pn, and n + 1 dummy keys d0, d1, ..., dn
representing searches not in K with probabilities q0, q1, ..., qn, find the minimum expected
search cost of a binary search tree. By choosing the proper input representation, write
a program in C to validate your procedures and derive the complexity analysis of your
algorithm.
*/
/*ALGORITHM:
----------
OptimalBST(p[], q[], n):
1. Create tables e[1..n+1][0..n], w[1..n+1][0..n], root[1..n][1..n]
2. For i = 1 to n+1: e[i][i-1] = q[i-1], w[i][i-1] = q[i-1]
3. For l = 1 to n:              // chain length
     For i = 1 to n-l+1:
       j = i + l - 1
       e[i][j] = INF
       w[i][j] = w[i][j-1] + p[j] + q[j]
       For r = i to j:          // try each root
         cost = e[i][r-1] + e[r+1][j] + w[i][j]
         If cost < e[i][j]:
           e[i][j] = cost
           root[i][j] = r
4. Return e[1][n]

TIME COMPLEXITY:  O(n^3)
SPACE COMPLEXITY: O(n^2)
*/

#include <stdio.h>
#include <float.h>

#define MAXN 20

double e[MAXN + 2][MAXN + 1];
double w[MAXN + 2][MAXN + 1];
int root[MAXN + 1][MAXN + 1];

void optimalBST(double p[], double q[], int n) {
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = DBL_MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; r++) {
                double cost = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (cost < e[i][j]) {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }
}

void printTree(int i, int j, int parent, int dir) {
    if (i > j) {
        if (dir == 0) printf("  d%d is root's left child\n", j);
        else if (dir == -1) printf("  d%d is k%d's left child\n", j, parent);
        else printf("  d%d is k%d's right child\n", j, parent);
        return;
    }
    int r = root[i][j];
    if (dir == 0) printf("  k%d is the root\n", r);
    else if (dir == -1) printf("  k%d is k%d's left child\n", r, parent);
    else printf("  k%d is k%d's right child\n", r, parent);
    printTree(i, r - 1, r, -1);
    printTree(r + 1, j, r, 1);
}

int main() {
    int n;
    printf("Enter number of keys: ");
    scanf("%d", &n);

    double p[n + 1], q[n + 1];
    printf("Enter probabilities p1..p%d: ", n);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &p[i]);
    printf("Enter dummy probabilities q0..q%d: ", n);
    for (int i = 0; i <= n; i++)
        scanf("%lf", &q[i]);

    optimalBST(p, q, n);

    printf("\nMinimum expected search cost: %.4f\n", e[1][n]);
    printf("\nOptimal BST structure:\n");
    printTree(1, n, 0, 0);

    return 0;
}

