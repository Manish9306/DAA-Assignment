/*
 * DAA Lab - 07 | Problem 4
 *
 * QUESTION:
 * 4. [Security switches]
 *    There is a row of n security switches protecting a military installation entrance.
 *    The switches can be manipulated as follows:
 *    (i)   The rightmost switch may be turned on or off at will.
 *    (ii)  Any other switch may be turned on or off only if the switch to its immediate right
 *          is on and all the other switches to its right, if any, are off.
 *    (iii) Only one switch may be toggled at a time.
 *
 *    Devise an algorithm to turn off all the switches, which are initially all on, in the
 *    minimum number of moves. (Toggling one switch is considered one move.)
 *
 *    By choosing the proper input representation, write a program in C to validate your
 *    algorithm and derive the complexity analysis of your algorithm.
 *
 * MATHEMATICAL MODEL & ALGORITHM:
 * Number switches 1 to n from RIGHT TO LEFT:
 *   - Switch 1 is rightmost: toggled freely (Rule i).
 *   - Switch k (k > 1): toggled iff switch k-1 is ON and switches 1..k-2 are OFF (Rule ii).
 *
 * Mutual Recursion:
 *   turnOff(k):
 *     turnOff(k - 2)
 *     toggle(k)
 *     turnOn(k - 2)
 *     turnOff(k - 1)
 *
 *   turnOn(k):
 *     turnOn(k - 1)
 *     turnOff(k - 2)
 *     toggle(k)
 *     turnOn(k - 2)
 *
 * Minimum Moves Closed-Form Formula:
 *   F(n) = floor( 2^(n + 1) / 3 )
 *        = (2^(n+1) - 1) / 3   for odd n
 *        = (2^(n+1) - 2) / 3   for even n
 *
 * COMPLEXITY ANALYSIS:
 * - Time Complexity:  Theta(2^n)
 * - Space Complexity: O(n) call stack and state array
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SWITCHES 32

static int switchState[MAX_SWITCHES + 1];
static int totalMoves = 0;
static int totalN = 0;

void turnOff(int k);
void turnOn(int k);

long long minMovesFormula(int n) {
    long long two_pow = 1LL << (n + 1);
    return two_pow / 3;
}

void printState(void) {
    printf("[ ");
    for (int i = totalN; i >= 1; i--) {
        printf("%d ", switchState[i]);
    }
    printf("]");
}

void toggle(int k) {
    if (k == 1) {
        // Rule (i)
    } else {
        // Rule (ii)
        if (switchState[k - 1] != 1) {
            printf("Error: Switch %d cannot toggle because switch %d is OFF.\n", k, k - 1);
            exit(1);
        }
        for (int j = 1; j < k - 1; j++) {
            if (switchState[j] != 0) {
                printf("Error: Switch %d cannot toggle because switch %d is ON.\n", k, j);
                exit(1);
            }
        }
    }

    switchState[k] ^= 1;
    totalMoves++;
    printf("  Step %2d: Toggle switch %2d (%s) -> State: ",
           totalMoves, k, switchState[k] ? "ON " : "OFF");
    printState();
    printf("\n");
}

void turnOff(int k) {
    if (k <= 0) return;
    if (k == 1) {
        toggle(1);
        return;
    }
    if (k == 2) {
        toggle(2);
        toggle(1);
        return;
    }
    turnOff(k - 2);
    toggle(k);
    turnOn(k - 2);
    turnOff(k - 1);
}

void turnOn(int k) {
    if (k <= 0) return;
    if (k == 1) {
        toggle(1);
        return;
    }
    if (k == 2) {
        toggle(1);
        toggle(2);
        return;
    }
    turnOn(k - 1);
    turnOff(k - 2);
    toggle(k);
    turnOn(k - 2);
}

void solveSecuritySwitches(int n) {
    totalN = n;
    totalMoves = 0;

    for (int i = 1; i <= n; i++) {
        switchState[i] = 1;
    }

    printf("Security Switches Deactivation (n = %d switches)\n", n);
    printf("  Expected Minimum Moves: %lld\n", minMovesFormula(n));
    printf("  Initial State (All ON) : ");
    printState();
    printf("\n\nMove Sequence:\n");

    turnOff(n);

    printf("\n  Final State (All OFF)  : ");
    printState();
    printf("\n  Total Moves Executed   : %d\n\n", totalMoves);
}

int main(void) {
    printf("DAA Lab 07 - Question 4: Security Switches Puzzle\n\n");

    printf("Formula Validation for 1 <= n <= 8:\n");
    for (int i = 1; i <= 8; i++) {
        printf("  n = %d switches: %3lld moves\n", i, minMovesFormula(i));
    }
    printf("\n");

    solveSecuritySwitches(4);
    solveSecuritySwitches(3);

    return 0;
}
