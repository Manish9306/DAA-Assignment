/*
 * DAA Lab - 07 | Problem 3
 *
 * QUESTION:
 * 3. Reve’s puzzle:
 *    There are eight disks of different sizes and four pegs. Initially, all the disks
 *    are on the first peg in order of size, the largest on the bottom and the smallest
 *    on the top. The objective is to transfer all the disks to another peg by a sequence
 *    of moves. Only one disk can be moved at a time, and it is forbidden to place a larger
 *    disk on top of a smaller one. Devise an algorithm that solves the puzzle in 33 moves.
 *    Generalize your algorithm for an n-disk problem.
 *
 *    By choosing the proper input representation, write a program in C to validate your
 *    algorithm and derive the complexity analysis of your algorithm.
 *
 * BACKGROUND & THE FRAME-STEWART ALGORITHM:
 * Reve's puzzle (4-peg Tower of Hanoi) is solved using the Frame-Stewart algorithm (1941):
 * 1. Choose an optimal partition integer k (1 <= k < n).
 * 2. Recursively transfer top (n - k) smallest disks from Source A to Aux B using 4 pegs.
 * 3. Transfer remaining k largest disks from Source A to Dest D using 3 pegs (standard Hanoi: 2^k - 1 moves).
 * 4. Recursively transfer (n - k) smallest disks from Aux B to Dest D using 4 pegs.
 *
 * Recurrence:
 *     R(0) = 0, R(1) = 1
 *     R(n) = min_{1 <= k < n} { 2 * R(n - k) + 2^k - 1 }
 *
 * For n = 8:
 *     k = 4 yields R(8) = 2 * R(4) + (2^4 - 1) = 2(9) + 15 = 33 moves.
 *
 * COMPLEXITY ANALYSIS:
 * - Time Complexity:  O(2^(sqrt(2*n))) moves
 * - Space Complexity: O(n) auxiliary stack space
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_DISKS 64

typedef struct {
    int disks[MAX_DISKS];
    int top;
    char name;
} Peg;

static Peg pegs[4];
static int totalMovesCount = 0;
static int dpR[MAX_DISKS + 1];
static int optK[MAX_DISKS + 1];

void initPegs(int n) {
    totalMovesCount = 0;
    char names[4] = {'A', 'B', 'C', 'D'};
    for (int i = 0; i < 4; i++) {
        pegs[i].top = -1;
        pegs[i].name = names[i];
    }
    for (int d = n; d >= 1; d--) {
        pegs[0].disks[++pegs[0].top] = d;
    }
}

int getPegIndex(char name) {
    return name - 'A';
}

void moveDisk(char from, char to) {
    int u = getPegIndex(from);
    int v = getPegIndex(to);

    if (pegs[u].top < 0) {
        printf("Error: Peg %c is empty.\n", from);
        exit(1);
    }

    int disk = pegs[u].disks[pegs[u].top--];

    if (pegs[v].top >= 0 && pegs[v].disks[pegs[v].top] < disk) {
        printf("Violation: Disk %d cannot be placed on disk %d on peg %c.\n",
               disk, pegs[v].disks[pegs[v].top], to);
        exit(1);
    }

    pegs[v].disks[++pegs[v].top] = disk;
    totalMovesCount++;
    printf("  Move %2d: Disk %d from Peg %c to Peg %c\n", totalMovesCount, disk, from, to);
}

void hanoi3(int count, char from, char to, char aux) {
    if (count == 0) return;
    if (count == 1) {
        moveDisk(from, to);
        return;
    }
    hanoi3(count - 1, from, aux, to);
    moveDisk(from, to);
    hanoi3(count - 1, aux, to, from);
}

void computeOptimalK(int maxN) {
    dpR[0] = 0;
    dpR[1] = 1;
    optK[1] = 1;

    for (int i = 2; i <= maxN; i++) {
        long long best = 1LL << 60;
        int best_k = 1;
        for (int k = 1; k < i; k++) {
            long long two_pow_k_minus_1 = (1LL << k) - 1;
            long long cost = 2LL * dpR[i - k] + two_pow_k_minus_1;
            if (cost <= best) {
                best = cost;
                best_k = k;
            }
        }
        dpR[i] = (int)best;
        optK[i] = best_k;
    }
}

void reve4(int n, char from, char to, char aux1, char aux2) {
    if (n == 0) return;
    if (n == 1) {
        moveDisk(from, to);
        return;
    }

    int k = optK[n];
    reve4(n - k, from, aux1, aux2, to);
    hanoi3(k, from, to, aux2);
    reve4(n - k, aux1, to, from, aux2);
}

void printPegState(void) {
    for (int i = 0; i < 4; i++) {
        printf("  Peg %c: [ ", pegs[i].name);
        for (int j = 0; j <= pegs[i].top; j++) {
            printf("%d ", pegs[i].disks[j]);
        }
        printf("]\n");
    }
}

int main(void) {
    printf("DAA Lab 07 - Question 3: Reve's Puzzle (Frame-Stewart Algorithm)\n\n");

    computeOptimalK(20);

    printf("Theoretical Moves Comparison (4 Pegs vs 3 Pegs):\n");
    for (int i = 1; i <= 8; i++) {
        long long h3 = (1LL << i) - 1;
        printf("  n = %d disks: 4-peg moves = %2d (split k = %d), 3-peg moves = %3lld\n",
               i, dpR[i], optK[i], h3);
    }
    printf("\n");

    int n = 8;
    printf("Solving Reve's Puzzle for n = %d disks (Target: 33 moves):\n", n);
    initPegs(n);

    printf("Initial Peg State:\n");
    printPegState();
    printf("\nMove Sequence:\n");

    reve4(n, 'A', 'D', 'B', 'C');

    printf("\nFinal Peg State:\n");
    printPegState();

    printf("\nVerification:\n");
    printf("  Expected Moves : %d\n", dpR[n]);
    printf("  Executed Moves : %d\n", totalMovesCount);
    printf("  Status         : %s\n", (totalMovesCount == 33) ? "Validated (Solved in exactly 33 moves)" : "Completed");

    return 0;
}
