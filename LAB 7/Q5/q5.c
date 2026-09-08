/*
 * DAA Lab - 07 | Problem 5
 *
 * QUESTION:
 * 5. [Hitting a moving target]
 *    A computer game has a shooter and a moving target. The shooter can hit any of
 *    n > 1 hiding spots located along a straight line in which the target can hide.
 *    The shooter can never see the target; all he knows is that the target moves to
 *    an adjacent hiding spot between every two consecutive shots. Design an algorithm that
 *    guarantees hitting the target or prove that no such algorithm exists.
 *
 *    If any such algorithm exists, by choosing the proper input representation, write
 *    a program in C to validate your algorithm and derive the complexity analysis of
 *    your algorithm.
 *
 * PROOF OF EXISTENCE & PARITY-PRESERVING ALGORITHM:
 * An algorithm guaranteeing a hit always exists.
 *
 * 1. Parity Invariant:
 *    Moving between adjacent spots strictly alternates the position's parity:
 *        pos(t + 1) = pos(t) + 1 (mod 2)
 *
 * 2. Two-Phase Sweep Strategy (n >= 3):
 *    - Phase 1 (Forward Sweep): Shoot spots 2, 3, ..., n - 1.
 *      If target started at an EVEN spot, its position parity matches the shot at every
 *      step. The target cannot cross over the shooter without being hit.
 *    - Phase 2 (Backward Sweep): Shoot spots n - 1, n - 2, ..., 2.
 *      If target started at an ODD spot, after (n - 2) steps its parity matches
 *      spot n - 1. Sweeping leftward corners the target against the right boundary.
 *
 * 3. Total Shots:
 *    - For n = 2: 2 shots ([1, 1])
 *    - For n >= 3: 2 * n - 4 shots
 *
 * 4. Validation via Belief-State Tracking:
 *    Maintain an array of possible candidate spots. After each shot and subsequent move,
 *    update candidate spots. The candidate set reduces to empty, formally verifying that
 *    no target trajectory can survive.
 *
 * COMPLEXITY ANALYSIS:
 * - Time Complexity:  O(n) shots; O(n^2) belief-state simulation
 * - Space Complexity: O(n) candidate state tracking
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int generateShootingSequence(int n, int shots[]) {
    if (n <= 1) return 0;
    if (n == 2) {
        shots[0] = 1;
        shots[1] = 1;
        return 2;
    }

    int len = 0;
    for (int s = 2; s <= n - 1; s++) {
        shots[len++] = s;
    }
    for (int s = n - 1; s >= 2; s--) {
        shots[len++] = s;
    }
    return len;
}

void validateAlgorithm(int n) {
    int shots[MAX_N * 2];
    int numShots = generateShootingSequence(n, shots);

    printf("Validation for n = %d spots:\n", n);
    printf("  Total shots: %d\n", numShots);
    printf("  Shooting sequence: [ ");
    for (int i = 0; i < numShots; i++) printf("%d ", shots[i]);
    printf("]\n\n");

    int possible[MAX_N + 1];
    for (int p = 1; p <= n; p++) possible[p] = 1;

    printf("Belief-State Tracking:\n");
    for (int t = 0; t < numShots; t++) {
        int s = shots[t];
        possible[s] = 0;

        int countAfterShot = 0;
        for (int p = 1; p <= n; p++) {
            if (possible[p]) countAfterShot++;
        }

        printf("  Step %2d: Shot at spot %2d | Remaining candidates: %2d [ ",
               t + 1, s, countAfterShot);
        for (int p = 1; p <= n; p++) {
            if (possible[p]) printf("%d ", p);
        }
        printf("]\n");

        if (countAfterShot == 0) {
            printf("  Target hit at step %d.\n", t + 1);
            break;
        }

        int next_possible[MAX_N + 1] = {0};
        for (int p = 1; p <= n; p++) {
            if (possible[p]) {
                if (p - 1 >= 1) next_possible[p - 1] = 1;
                if (p + 1 <= n) next_possible[p + 1] = 1;
            }
        }
        for (int p = 1; p <= n; p++) possible[p] = next_possible[p];
    }

    int finalCount = 0;
    for (int p = 1; p <= n; p++) {
        if (possible[p]) finalCount++;
    }

    printf("  Verification: %s\n\n",
           (finalCount == 0) ? "Validated (All candidate paths eliminated)" : "Incomplete");
}

int main(void) {
    printf("DAA Lab 07 - Question 5: Hitting a Moving Target\n\n");

    printf("Guaranteed Shots for Various n (Formula: 2n - 4 for n >= 3):\n");
    for (int n = 2; n <= 8; n++) {
        int shots[64];
        int len = generateShootingSequence(n, shots);
        printf("  n = %d: %2d shots, sequence = [ ", n, len);
        for (int i = 0; i < len; i++) printf("%d ", shots[i]);
        printf("]\n");
    }
    printf("\n");

    validateAlgorithm(5);
    validateAlgorithm(4);

    return 0;
}
