/*
Question 7: [Minimise Deviation in Array (Two-Way Greedy with Max-Heap)]
Given an array of positive integers, you can perform two operations: multiply
any odd element by 2, or divide any even element by 2. The deviation is
(max(A) - min(A)). Minimise the deviation after any number of operations. By
choosing the proper input representation, write a program in C to validate your
procedures and derive the complexity analysis of your algorithm.

Algorithm:
1. Since odd numbers can only be multiplied by 2 at most once (because they become
   even), multiply every odd number by 2 first. Now every number is at its maximum
   possible value and is even.
2. Track the minimum element in the array.
3. In a loop:
   - Find the current maximum element in the array.
   - Calculate deviation = current_max - current_min, and update min_deviation.
   - If current_max is odd, we cannot divide it anymore, so we must stop.
   - Otherwise, divide current_max by 2, update current_min if needed, and continue.

Time Complexity:
- If using simple linear search: O(n * log(max_val))
- If using max heap: O(n log(max_val) * log n)
Overall Time Complexity: O(n log M) where M is maximum value
Space Complexity: O(n)
*/

#include <stdio.h>

int main() {
    int n, i;
    int a[100];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter array elements: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        // bring odd numbers to their upper bound
        if (a[i] % 2 != 0) {
            a[i] *= 2;
        }
    }

    int curMin = a[0];
    for (i = 1; i < n; i++) {
        if (a[i] < curMin) {
            curMin = a[i];
        }
    }

    int minDeviation = 1000000000;

    while (1) {
        // find current max index
        int maxIdx = 0;
        for (i = 1; i < n; i++) {
            if (a[i] > a[maxIdx]) {
                maxIdx = i;
            }
        }

        int diff = a[maxIdx] - curMin;
        if (diff < minDeviation) {
            minDeviation = diff;
        }

        // if maximum is odd, we cannot decrease it further
        if (a[maxIdx] % 2 != 0) {
            break;
        }

        // reduce maximum by half
        a[maxIdx] /= 2;

        if (a[maxIdx] < curMin) {
            curMin = a[maxIdx];
        }
    }

    printf("Minimum deviation possible = %d\n", minDeviation);

    return 0;
}
