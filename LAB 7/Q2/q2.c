/*
 * DAA Lab - 07 | Problem 2
 *
 * QUESTION:
 * 2. [Super egg testing experiment]
 *    A firm has invented a super-strong egg. For publicity purposes, it wants to determine
 *    the highest floor in a 100-storey building from which such an egg can fall without
 *    breaking. The firm has given a tester two identical eggs to experiment with. Of course,
 *    the same egg can be dropped multiple times unless it breaks. What is the minimum
 *    number of droppings that is guaranteed to determine the highest safe floor in all
 *    cases? Design a dynamic programming generalized solution for E eggs and F floors.
 *
 *    By choosing the proper input representation, write a program in C to validate your
 *    algorithm and derive the complexity analysis of your algorithm.
 *
 * ANALYTICAL SOLUTION FOR 2 EGGS & 100 FLOORS:
 * 1. Let x be the first floor to test. If egg 1 breaks, egg 2 must test floors 1 to x-1
 *    linearly (at most x-1 drops). Total = 1 + (x-1) = x drops.
 * 2. If egg 1 survives, the next interval is chosen as x-1 to keep total worst-case drops
 *    constant at x.
 * 3. Total floors covered with x drops:
 *        x + (x - 1) + (x - 2) + ... + 1 = x * (x + 1) / 2 >= 100
 *    Solving gives x = ceil((-1 + sqrt(1 + 800)) / 2) = 14 drops.
 *    Optimal drop sequence: 14, 27, 39, 50, 60, 69, 77, 84, 90, 95, 99, 100.
 *
 * GENERALIZED DYNAMIC PROGRAMMING FORMULATION (E EGGS, F FLOORS):
 * Let DP[e][f] be the minimum drops in the worst case for e eggs and f floors.
 *
 * Base Cases:
 *   DP[e][0] = 0,  DP[e][1] = 1   for all e >= 1
 *   DP[1][f] = f                  for all f >= 1
 *
 * Recurrence:
 *   For e > 1, f > 1:
 *   DP[e][f] = 1 + min_{1 <= k <= f} { max(DP[e - 1][k - 1], DP[e][f - k]) }
 *
 * COMPLEXITY ANALYSIS:
 * - Time Complexity:  O(E * F^2)
 * - Space Complexity: O(E * F)
 */

#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int max(int a, int b) {
    return (a > b) ? a : b;
}

void solveEggDropping(int E, int F) {
    int **dp = (int **)malloc((E + 1) * sizeof(int *));
    int **drop = (int **)malloc((E + 1) * sizeof(int *));
    for (int i = 0; i <= E; i++) {
        dp[i] = (int *)malloc((F + 1) * sizeof(int));
        drop[i] = (int *)malloc((F + 1) * sizeof(int));
    }

    for (int i = 1; i <= E; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
        drop[i][0] = 0;
        drop[i][1] = 1;
    }

    for (int j = 1; j <= F; j++) {
        dp[1][j] = j;
        drop[1][j] = 1;
    }

    for (int i = 2; i <= E; i++) {
        for (int j = 2; j <= F; j++) {
            dp[i][j] = INF;
            for (int k = 1; k <= j; k++) {
                int res = 1 + max(dp[i - 1][k - 1], dp[i][j - k]);
                if (res < dp[i][j]) {
                    dp[i][j] = res;
                    drop[i][j] = k;
                }
            }
        }
    }

    printf("Configuration: E = %d eggs, F = %d floors\n", E, F);
    printf("  Minimum drops guaranteed in worst case: %d\n", dp[E][F]);
    printf("  Optimal first drop floor: %d\n", drop[E][F]);

    if (E == 2) {
        printf("  Drop sequence when egg survives:\n");
        int current_floor = 0;
        int remaining_floors = F;
        int step = 1;
        while (remaining_floors > 0 && current_floor < F) {
            int step_jump = drop[2][remaining_floors];
            current_floor += step_jump;
            if (current_floor > F) current_floor = F;
            printf("    Step %2d: Test floor %3d (jump +%2d, %d remaining)\n",
                   step, current_floor, step_jump, remaining_floors);
            remaining_floors -= step_jump;
            step++;
        }
    }
    printf("\n");

    for (int i = 0; i <= E; i++) {
        free(dp[i]);
        free(drop[i]);
    }
    free(dp);
    free(drop);
}

int main(void) {
    printf("DAA Lab 07 - Question 2: Super Egg Testing Experiment\n\n");

    printf("Problem Specification: 2 Eggs, 100 Floors\n");
    solveEggDropping(2, 100);

    printf("Generalization Examples:\n");
    solveEggDropping(3, 100);
    solveEggDropping(2, 36);

    return 0;
}
