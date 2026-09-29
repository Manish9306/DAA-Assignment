/*
9. [Collatz Conjecture] The Collatz Conjecture defines a recurrence relation for any
strictly positive integer n:
   T(n) = n/2       if n is even
          3n + 1    if n is odd
The sequence repeatedly applies this function until n = 1.

Write a modular C program to analyse the trajectory of a user-provided starting value
n >= 1 and across an interval [a, b].

ALGORITHM:
----------
CollatzTrajectory(n):
1. count = 0
2. While n != 1:
     Print n
     If n is even: n = n / 2
     Else: n = 3*n + 1
     count++
3. Print 1, return count

AnalyseInterval(a, b):
1. For each n in [a, b]:
     Compute CollatzTrajectory length (stopping time)
2. Track and print the number with the longest trajectory

TIME COMPLEXITY:  Not proven bounded (conjecture is open!)
                  Empirically each trajectory takes O(log n) to O(n) steps.
SPACE COMPLEXITY: O(1) per trajectory
*/

#include <stdio.h>

int collatz(long long n, int printPath) {
    int steps = 0;
    if (printPath) printf("  %lld", n);
    while (n != 1) {
        if (n % 2 == 0)
            n = n / 2;
        else
            n = 3 * n + 1;
        steps++;
        if (printPath) printf(" -> %lld", n);
    }
    if (printPath) printf("\n");
    return steps;
}

void analyseInterval(int a, int b) {
    int maxSteps = 0;
    long long maxN = a;
    printf("\n  n\t| Steps\n  ------+------\n");
    for (long long i = a; i <= b; i++) {
        int s = collatz(i, 0);
        printf("  %lld\t| %d\n", i, s);
        if (s > maxSteps) {
            maxSteps = s;
            maxN = i;
        }
    }
    printf("\n  Longest trajectory in [%d, %d]: n = %lld with %d steps\n", a, b, maxN, maxSteps);
}

int main() {
    int choice;
    printf("1. Single value trajectory\n");
    printf("2. Interval analysis [a, b]\n");
    printf("3. Both\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1 || choice == 3) {
        long long n;
        printf("Enter starting value n: ");
        scanf("%lld", &n);
        printf("Trajectory:\n");
        int steps = collatz(n, 1);
        printf("Stopping time: %d steps\n", steps);
    }

    if (choice == 2 || choice == 3) {
        int a, b;
        printf("Enter interval [a, b]: ");
        scanf("%d %d", &a, &b);
        analyseInterval(a, b);
    }

    return 0;
}
