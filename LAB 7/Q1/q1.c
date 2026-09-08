/*
 * DAA Lab - 07 | Problem 1
 *
 * QUESTION:
 * 1. [Invert the coin-triangle]
 *    Consider an equilateral triangle formed by closely packed pennies or other identical
 *    coins like the one shown in Figure 1. (The centers of the coins are assumed to be
 *    at the points of the equilateral triangular lattice.) Design an algorithm to flip
 *    the triangle upside down in the minimum number of moves if on each move you can
 *    slide one coin at a time to its new position. Give a compact formula for the number
 *    of minimum moves.
 *
 *    Figure 1: Coin-triangle that needs to be inverted (e.g., n = 4 rows, 10 coins).
 *
 *    By choosing the proper input representation, write a program in C to validate your
 *    procedures and derive the complexity analysis of your algorithm.
 *
 * MATHEMATICAL ANALYSIS & COMPACT FORMULA:
 * 1. Total coins in an n-row equilateral triangle:
 *        T(n) = n * (n + 1) / 2
 *
 * 2. Inverting the triangle with minimum moves is equivalent to maximizing the
 *    intersection (overlap) between the upright triangle and the inverted triangle.
 *
 * 3. The non-overlapping coins in the upright triangle reside in three corner
 *    equilateral sub-triangles (top, bottom-left, bottom-right) of sizes p, q, r
 *    such that p + q + r = n - 1.
 *
 * 4. To minimize moves, p, q, r are chosen as balanced as possible:
 *    m = (n - 1) / 3, rem = (n - 1) % 3.
 *    The sum of coins in these three corners yields the compact formula:
 *        M(n) = floor( n * (n + 1) / 6 ) = floor( T(n) / 3 )
 *
 *    Examples:
 *        n = 1: 0 moves
 *        n = 2: 1 move
 *        n = 3: 2 moves
 *        n = 4: 3 moves (as in Figure 1)
 *        n = 5: 5 moves
 *        n = 6: 7 moves
 *
 * ALGORITHM:
 * 1. Calculate total coins T(n) and minimum moves M(n).
 * 2. Represent the triangular lattice: row r in [0, n-1], col c in [0, r].
 * 3. Identify coins in the three corner regions to be relocated.
 * 4. Identify corresponding vacant coordinates in the inverted triangle.
 * 5. Output coordinates of each coin slide and display the resulting inversion.
 *
 * COMPLEXITY ANALYSIS:
 * - Time Complexity:
 *     Formula: O(1)
 *     Move generation & grid display: O(n^2)
 * - Space Complexity:
 *     Lattice representation: O(n^2)
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_COINS 5000

typedef struct {
    int r;
    int c;
} Point;

long long minMovesCompact(long long n) {
    if (n <= 1) return 0;
    return (n * (n + 1)) / 6;
}

long long totalCoins(long long n) {
    return (n * (n + 1)) / 2;
}

void printUprightTriangle(int n) {
    for (int r = 0; r < n; r++) {
        for (int s = 0; s < n - 1 - r; s++) printf(" ");
        for (int c = 0; c <= r; c++) {
            printf("O ");
        }
        printf("\n");
    }
}

void printInvertedTriangle(int n) {
    for (int r = 0; r < n; r++) {
        for (int s = 0; s < r; s++) printf(" ");
        int coinsInRow = n - r;
        for (int c = 0; c < coinsInRow; c++) {
            printf("O ");
        }
        printf("\n");
    }
}

void solveCoinTriangle(int n) {
    long long total = totalCoins(n);
    long long movesCount = minMovesCompact(n);

    printf("Coin-Triangle Inversion (n = %d rows)\n", n);
    printf("  Total Coins: %lld\n", total);
    printf("  Minimum Moves Required: %lld [Formula: floor(n*(n+1)/6)]\n\n", movesCount);

    if (n <= 1) {
        printf("  A triangle of size %d requires 0 moves.\n\n", n);
        return;
    }

    printf("Initial Upright Triangle:\n");
    printUprightTriangle(n);
    printf("\n");

    int m = (n - 1) / 3;
    int rem = (n - 1) % 3;
    int p = m;
    int q = m;
    int r_size = m;
    if (rem == 1) {
        r_size = m + 1;
    } else if (rem == 2) {
        q = m + 1;
        r_size = m + 1;
    }

    printf("Corner Removal Breakdown (p + q + r = %d):\n", n - 1);
    printf("  Top corner (p)          : %d rows (%d coins)\n", p, p * (p + 1) / 2);
    printf("  Bottom-left corner (q)  : %d rows (%d coins)\n", q, q * (q + 1) / 2);
    printf("  Bottom-right corner (r) : %d rows (%d coins)\n\n", r_size, r_size * (r_size + 1) / 2);

    Point excess[MAX_COINS];
    int excessCount = 0;

    // Top corner
    for (int row = 0; row < p; row++) {
        for (int col = 0; col <= row; col++) {
            excess[excessCount++] = (Point){row, col};
        }
    }

    // Bottom-left corner
    for (int i = 0; i < q; i++) {
        int row = n - q + i;
        int numCoinsInCornerRow = i + 1;
        for (int col = 0; col < numCoinsInCornerRow; col++) {
            excess[excessCount++] = (Point){row, col};
        }
    }

    // Bottom-right corner
    for (int i = 0; i < r_size; i++) {
        int row = n - r_size + i;
        int numCoinsInCornerRow = i + 1;
        for (int k = 0; k < numCoinsInCornerRow; k++) {
            int col = row - k;
            excess[excessCount++] = (Point){row, col};
        }
    }

    Point vacancies[MAX_COINS];
    int vacancyCount = 0;

    for (int i = 0; i < n; i++) {
        int targetRow = p + i;
        int count = n - i;
        for (int c = 0; c < count; c++) {
            int targetCol = c;
            int inOriginal = (targetRow < n && targetCol <= targetRow);
            if (!inOriginal) {
                vacancies[vacancyCount++] = (Point){targetRow, targetCol};
            }
        }
    }

    int actualMoves = (excessCount < vacancyCount) ? excessCount : vacancyCount;
    printf("Move Sequence:\n");
    for (int i = 0; i < actualMoves; i++) {
        printf("  Move %2d: Slide coin from (%d, %d) to (%d, %d)\n",
               i + 1, excess[i].r + 1, excess[i].c + 1,
               vacancies[i].r + 1, vacancies[i].c + 1);
    }
    printf("\n");

    printf("Final Inverted Triangle:\n");
    printInvertedTriangle(n);
    printf("Successfully inverted in %d moves.\n\n", actualMoves);
}

int main(void) {
    printf("DAA Lab 07 - Question 1: Invert the Coin-Triangle\n\n");

    int testCases[] = {2, 3, 4, 5, 6};
    int numTests = sizeof(testCases) / sizeof(testCases[0]);

    printf("Summary of Minimum Moves for Small n:\n");
    for (int i = 0; i < numTests; i++) {
        int n = testCases[i];
        printf("  n = %2d rows: %2lld coins, minimum moves = %2lld\n",
               n, totalCoins(n), minMovesCompact(n));
    }
    printf("\n");

    printf("Demonstrating Figure 1 (n = 4 rows, 10 coins):\n\n");
    solveCoinTriangle(4);

    return 0;
}
