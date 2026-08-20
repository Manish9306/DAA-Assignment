/*2. Application of sorting-II: Given two sets S1 and S2 (each of size n), and a number x,
describe an O(n · log n) algorithm for finding whether there exists a pair of elements, one
from S1 and one from S2, that add up to x. By choosing the proper input representation,
write a program in C to validate your algorithm.*/

/*======================================================================
PAIR SUM SEARCH ALGORITHM (Two Pointers Approach)
======================================================================

Input  : Two sets/arrays S1 and S2, each of size n, and a target sum x.
Output : Returns true (and the pair) if there exist a in S1 and b in S2 
         such that a + b = x; otherwise returns false.

----------------------------------------------------------------------
Intuitive Idea:
----------------------------------------------------------------------
1. Sort array S1 in ascending order and array S2 in descending order 
   (or use two pointers on both sorted in ascending order).
2. Start with:
   - Pointer i at the smallest element of S1 (leftmost, index 0).
   - Pointer j at the largest element of S2 (rightmost, index n-1).
3. Check the sum = S1[i] + S2[j]:
   - If sum == x: Found the pair!
   - If sum < x : Need a larger sum -> move i to the right (i++).
   - If sum > x : Need a smaller sum -> move j to the left (j--).
4. If pointers go out of bounds without finding a match, no such pair exists.

----------------------------------------------------------------------
Formal Step-by-Step Algorithm:
----------------------------------------------------------------------
Step 1: Sort array S1 in ascending order using Merge Sort or Quick Sort.
        - Time: O(n log n)

Step 2: Sort array S2 in ascending order using Merge Sort or Quick Sort.
        - Time: O(n log n)

Step 3: Initialize two pointers:
        - i = 0     (points to the start of S1)
        - j = n - 1 (points to the end of S2)

Step 4: While (i < n AND j >= 0):
        current_sum = S1[i] + S2[j]

        - If current_sum == x:
            Return TRUE with pair (S1[i], S2[j])
        - Else If current_sum < x:
            i = i + 1   (Increase the sum)
        - Else (current_sum > x):
            j = j - 1   (Decrease the sum)

Step 5: If the loop finishes without returning, return FALSE (pair not found).
======================================================================*/

#include <stdio.h>
#include <stdlib.h>

// Comparison function needed for standard C library qsort (Quick Sort)
int compare(const void* a, const void* b) {
    int val1 = *(const int*)a;
    int val2 = *(const int*)b;
    if (val1 < val2) return -1;
    if (val1 > val2) return 1;
    return 0;
}

// Function to find pair with sum x in O(n log n) time
int findPairWithSum(int S1[], int S2[], int n, int x, int* pair1, int* pair2) {
    // Step 1: Sort both arrays - O(n log n)
    qsort(S1, n, sizeof(int), compare);
    qsort(S2, n, sizeof(int), compare);

    // Step 2: Two-pointer scan - O(n)
    int i = 0;      // Start of S1 (smallest elements)
    int j = n - 1;  // End of S2 (largest elements)

    while (i < n && j >= 0) {
        int current_sum = S1[i] + S2[j];

        if (current_sum == x) {
            *pair1 = S1[i];
            *pair2 = S2[j];
            return 1; // Pair found
        } else if (current_sum < x) {
            i++; // Need a larger sum, so move to larger element in S1
        } else {
            j--; // Need a smaller sum, so move to smaller element in S2
        }
    }

    return 0; // No such pair exists
}

void printArray(int arr[], int n) {
    printf("{ ");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf(" }\n");
}

int main() {
    int S1[] = {12, 3, 5, 8, 20};
    int S2[] = {4, 15, 1, 9, 7};
    int n = sizeof(S1) / sizeof(S1[0]);
    int x = 24; // Target sum (e.g., 20 from S1 + 4 from S2 = 24, or 9 + 15 = 24)

    printf("Set S1 : ");
    printArray(S1, n);

    printf("Set S2 : ");
    printArray(S2, n);

    printf("Target Sum (x): %d\n\n", x);

    int pair1, pair2;
    int found = findPairWithSum(S1, S2, n, x, &pair1, &pair2);

    if (found) {
        printf("Result: Pair found!\n");
        printf("Element from S1 = %d\n", pair1);
        printf("Element from S2 = %d\n", pair2);
        printf("Verification   : %d + %d = %d\n", pair1, pair2, pair1 + pair2);
    } else {
        printf("Result: No pair found in S1 and S2 that adds up to %d.\n", x);
    }

    return 0;
}

/*======================================================================
TIME COMPLEXITY ANALYSIS
======================================================================

Overall Time Complexity: O(n log n)

----------------------------------------------------------------------
Step-by-Step Breakdown:
----------------------------------------------------------------------

1. Sorting Array S1:
   - Using a standard comparison-based sort like Merge Sort or Quick Sort:
     Time = O(n log n)

2. Sorting Array S2:
   - Sorting the second array using Merge Sort or Quick Sort:
     Time = O(n log n)

3. Two-Pointer Search:
   - Pointer i moves from 0 up to n (at most n steps).
   - Pointer j moves from n-1 down to 0 (at most n steps).
   - In each step, we do constant-time comparisons and increments/decrements O(1).
   - Total loop iterations <= 2n:
     Time = O(n)

----------------------------------------------------------------------
Total Time Complexity Calculation:
----------------------------------------------------------------------

Total Time = O(n log n) [Sort S1] + O(n log n) [Sort S2] + O(n) [Two-Pointer Search]
           = O(2 * n log n + n)
           = O(n log n)

----------------------------------------------------------------------
Final Verdict:
----------------------------------------------------------------------
- Worst-Case Time Complexity   : O(n log n)
- Best-Case Time Complexity    : O(n log n) (due to sorting)
- Average-Case Time Complexity : O(n log n)

Space Complexity:
- O(1) auxiliary space if in-place sorting (like Heap Sort or Quick Sort) is used.
- O(n) if Merge Sort is used.
======================================================================*/