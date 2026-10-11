/*
Question 4: [Minimum Cost to Connect Sticks]
You have sticks of lengths L1, L2, ..., Ln. Connecting two sticks of lengths x
and y costs x + y, resulting in a single stick of length x + y. Find the minimum
total cost to connect all sticks into one. By choosing the proper input
representation, write a program in C to validate your algorithm and derive the
complexity analysis of your algorithm.

Algorithm:
1. To minimize total cost, sticks merged earlier should be the shortest ones so
   their lengths are added into fewer future sums.
2. Store sticks in an array or min-heap.
3. In each step:
   - Pick the two smallest stick lengths.
   - Sum them up to form a new combined stick.
   - Add the sum to the running total cost.
   - Insert the new stick length back into the collection.
4. Repeat until only one stick is left.

Time Complexity:
- If using simple sorting / insertion: O(n^2)
- If using binary min-heap: O(n log n)
Overall Time Complexity: O(n log n) or O(n^2)
Space Complexity: O(n)
*/

#include <stdio.h>

void sortArray(int a[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, i;
    int sticks[100];

    printf("Enter number of sticks: ");
    scanf("%d", &n);

    printf("Enter lengths of %d sticks:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &sticks[i]);
    }

    int size = n;
    long long totalCost = 0;

    while (size > 1) {
        // sort so the two smallest are always at index 0 and 1
        sortArray(sticks, size);

        int first = sticks[0];
        int second = sticks[1];
        int combined = first + second;

        totalCost += combined;

        // replace first with combined, and shift remaining left
        sticks[0] = combined;
        for (i = 1; i < size - 1; i++) {
            sticks[i] = sticks[i + 1];
        }
        size--;

        printf("Connected sticks %d and %d -> cost %d (Running total: %lld)\n", 
               first, second, combined, totalCost);
    }

    printf("\nMinimum cost to connect all sticks = %lld\n", totalCost);

    return 0;
}
