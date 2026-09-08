/*
 * DAA Lab - 07 | Problem 7
 *
 * QUESTION:
 * 7. [Matrix Chain Multiplication (MCM) problem]
 *    Consider the matrix chain multiplication problem. Write a program in C to implement
 *    the dynamic programming solution of the MCM problem in order to find the minimum
 *    number of scalar multiplications involved and the corresponding ordering to obtain
 *    the final result.
 *
 * DYNAMIC PROGRAMMING FORMULATION:
 * Given n matrices <A_1, A_2, ..., A_n>, where A_i has dimension p_{i-1} x p_i.
 *
 * 1. Subproblem Definition:
 *    Let m[i][j] be the minimum scalar multiplications needed to compute A_i ... A_j
 *    for 1 <= i <= j <= n.
 *
 * 2. Recurrence Relation:
 *    - Base Case:
 *        m[i][i] = 0   for all 1 <= i <= n
 *    - Recursive Step (for chain length L = 2 to n, j = i + L - 1):
 *        m[i][j] = min_{i <= k < j} { m[i][k] + m[k+1][j] + p_{i-1} * p_k * p_j }
 *
 * 3. Split Table s[i][j]:
 *    s[i][j] stores the optimal index k that achieves the minimum cost.
 *
 * 4. Reconstruction:
 *    A recursive function printOptimalParens prints the optimal parenthesization using s.
 *
 * COMPLEXITY ANALYSIS:
 * - Time Complexity:  O(n^3) due to three nested loops (L, i, k)
 * - Space Complexity: O(n^2) to store tables m and s
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_MATRICES 100

static long long m[MAX_MATRICES + 1][MAX_MATRICES + 1];
static int s[MAX_MATRICES + 1][MAX_MATRICES + 1];

void printOptimalParens(int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParens(i, s[i][j]);
        printf(" x ");
        printOptimalParens(s[i][j] + 1, j);
        printf(")");
    }
}

void matrixChainOrder(int p[], int n) {
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = LLONG_MAX;

            for (int k = i; k <= j - 1; k++) {
                long long cost = m[i][k] + m[k + 1][j] + (long long)p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
}

void solveMCM(int p[], int n, const char *testLabel) {
    printf("%s\n", testLabel);
    printf("Number of matrices: %d\n", n);
    printf("Dimensions:\n");
    for (int i = 1; i <= n; i++) {
        printf("  A%d: %d x %d\n", i, p[i - 1], p[i]);
    }
    printf("Dimension vector p: [ ");
    for (int i = 0; i <= n; i++) printf("%d ", p[i]);
    printf("]\n\n");

    matrixChainOrder(p, n);

    printf("DP Cost Table m[i][j] (Minimum Scalar Multiplications):\n");
    printf("       ");
    for (int j = 1; j <= n; j++) {
        printf("      j=%d", j);
    }
    printf("\n");
    for (int i = 1; i <= n; i++) {
        printf("  i=%d: ", i);
        for (int j = 1; j <= n; j++) {
            if (j < i) {
                printf("         -");
            } else {
                printf("%10lld", m[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("Optimal Split Table s[i][j]:\n");
    printf("       ");
    for (int j = 1; j <= n; j++) {
        printf("   j=%d", j);
    }
    printf("\n");
    for (int i = 1; i <= n; i++) {
        printf("  i=%d: ", i);
        for (int j = 1; j <= n; j++) {
            if (j <= i) {
                printf("      -");
            } else {
                printf("%7d", s[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("Results:\n");
    printf("  Minimum Scalar Multiplications : %lld\n", m[1][n]);
    printf("  Optimal Parenthesization Order : ");
    printOptimalParens(1, n);
    printf("\n\n");
}

int main(void) {
    printf("DAA Lab 07 - Question 7: Matrix Chain Multiplication (MCM)\n\n");

    // Test Case 1: Standard textbook example
    // A1: 30x35, A2: 35x15, A3: 15x5, A4: 5x10, A5: 10x20, A6: 20x25
    int p1[] = {30, 35, 15, 5, 10, 20, 25};
    int n1 = sizeof(p1) / sizeof(p1[0]) - 1;
    solveMCM(p1, n1, "Test Case 1 (Standard 6-Matrix Chain)");

    // Test Case 2: 4 matrices
    // A1: 10x20, A2: 20x30, A3: 30x40, A4: 40x30
    int p2[] = {10, 20, 30, 40, 30};
    int n2 = sizeof(p2) / sizeof(p2[0]) - 1;
    solveMCM(p2, n2, "Test Case 2 (4-Matrix Chain)");

    return 0;
}
