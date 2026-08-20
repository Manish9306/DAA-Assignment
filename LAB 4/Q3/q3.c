/*3. Application of sorting-III: Given a set S of n integers and an integer T, give an O(nk−1 ·
log n) algorithm to test whether k of the integers in S add up to T. By choosing the proper
input representation, write a program in C to validate your algorithm.*/

/*======================================================================
k-SUM SEARCH ALGORITHM (Sorting + (k-1) Loops + Binary Search)
======================================================================

Input  : A set/array S of n integers, target sum T, and an integer k (k >= 1).
Output : Returns true if there exist k distinct elements in S that add 
         up to T; otherwise returns false.

----------------------------------------------------------------------
Intuitive Idea:
----------------------------------------------------------------------
1. If we sort the array S, we can search for any element in O(log n) 
   time using Binary Search.
2. To find if k numbers add up to T:
   - Pick the first (k - 1) numbers using (k - 1) nested loops.
   - Let their sum be: current_sum = S[i1] + S[i2] + ... + S[i_{k-1}].
   - The required k-th number must be: needed = T - current_sum.
3. Use Binary Search to look for 'needed' in the remaining part of 
   the sorted array (to the right of i_{k-1} to avoid reusing elements).
4. If found, return TRUE. If all combinations are checked with no match, 
   return FALSE.

----------------------------------------------------------------------
Formal Step-by-Step Algorithm:
----------------------------------------------------------------------
Step 1: Sort array S in ascending order using Quick Sort or Merge Sort.
        - Time: O(n log n)

Step 2: Use recursive helper function (or k-1 nested loops) to choose 
        (k - 1) elements at distinct indices:
        - Outer Loop 1: i1 from 0 to n - k
        - Outer Loop 2: i2 from i1 + 1 to n - k + 1
        ...
        - Loop (k - 1): i_{k-1} from i_{k-2} + 1 to n - 1

Step 3: In the innermost step:
        - Compute: needed = T - (S[i1] + S[i2] + ... + S[i_{k-1}])
        - Perform Binary Search for 'needed' in subarray S[i_{k-1} + 1 ... n - 1].

Step 4: If Binary Search finds 'needed':
        - Return TRUE (found k elements that sum to T).

Step 5: If all combinations are exhausted without success:
        - Return FALSE.
======================================================================*/

#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort (Quick Sort)
int compare(const void* a, const void* b) {
    int val1 = *(const int*)a;
    int val2 = *(const int*)b;
    if (val1 < val2) return -1;
    if (val1 > val2) return 1;
    return 0;
}

// Standard Binary Search in sorted array - O(log n)
int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid; // Target found
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Target not found
}

// Recursive function to pick (k-1) elements and binary search the k-th element
int kSumCheck(int S[], int n, int k, int target, int startIndex, int chosenCount, int currentSum, int chosenIndices[]) {
    // Base Case: We have already chosen (k - 1) elements
    if (chosenCount == k - 1) {
        int needed = target - currentSum;
        // Binary search for 'needed' in the remaining elements to the right
        int foundIndex = binarySearch(S, startIndex, n - 1, needed);

        if (foundIndex != -1) {
            chosenIndices[chosenCount] = foundIndex;
            return 1; // Solution found
        }
        return 0;
    }

    // Try choosing the next element from startIndex onwards
    for (int i = startIndex; i <= n - (k - chosenCount); i++) {
        chosenIndices[chosenCount] = i;
        if (kSumCheck(S, n, k, target, i + 1, chosenCount + 1, currentSum + S[i], chosenIndices)) {
            return 1; // Solution found deeper in recursion
        }
    }

    return 0; // No combination found
}

int main() {
    int S[] = {14, 2, 7, 29, 5, 1, 9, 11};
    int n = sizeof(S) / sizeof(S[0]);
    int k = 3;       // Find if 3 elements sum to target
    int target = 23; // Example: 5 + 7 + 11 = 23 or 1 + 9 + 13 ...

    printf("Original Array S: { ");
    for (int i = 0; i < n; i++) {
        printf("%d%s", S[i], (i < n - 1) ? ", " : " }\n");
    }
    printf("Target Sum (T)  : %d\n", target);
    printf("Count of items(k): %d\n\n", k);

    // Step 1: Sort array in ascending order - O(n log n)
    qsort(S, n, sizeof(int), compare);

    printf("Sorted Array S  : { ");
    for (int i = 0; i < n; i++) {
        printf("%d%s", S[i], (i < n - 1) ? ", " : " }\n");
    }

    int chosenIndices[20]; // Array to store indices of chosen elements
    int found = kSumCheck(S, n, k, target, 0, 0, 0, chosenIndices);

    if (found) {
        printf("\nResult: Found %d elements that sum to %d!\nElements: ", k, target);
        int sumVerify = 0;
        for (int i = 0; i < k; i++) {
            int val = S[chosenIndices[i]];
            sumVerify += val;
            printf("%d%s", val, (i < k - 1) ? " + " : "");
        }
        printf(" = %d\n", sumVerify);
    } else {
        printf("\nResult: No %d elements found that sum to %d.\n", k, target);
    }

    return 0;
}

/*======================================================================
TIME COMPLEXITY ANALYSIS
======================================================================

Overall Time Complexity: O(n^(k-1) * log n)

----------------------------------------------------------------------
Step-by-Step Breakdown:
----------------------------------------------------------------------

1. Sorting the Array S:
   - Sorting n elements using Quick Sort / Merge Sort:
     Time = O(n log n)

2. Choosing (k - 1) Elements:
   - We choose (k - 1) elements using (k - 1) nested loops.
   - Number of combinations is bounded by O(n^(k-1)).

3. Binary Search for the k-th Element:
   - For each combination of (k - 1) elements, we do a Binary Search 
     in the remaining sorted array of size <= n.
   - Binary Search takes O(log n) time per combination.

----------------------------------------------------------------------
Total Time Complexity Calculation:
----------------------------------------------------------------------

Total Time = [Sorting Time] + [Number of (k-1) Combinations * Binary Search Time]
           = O(n log n) + O(n^(k-1)) * O(log n)
           = O(n^(k-1) * log n)

----------------------------------------------------------------------
Final Verdict:
----------------------------------------------------------------------
- Worst-Case Time Complexity   : O(n^(k-1) * log n)
- Best-Case Time Complexity    : O(n log n)  (if found on first combination)
- Average-Case Time Complexity : O(n^(k-1) * log n)
- Space Complexity             : O(1) auxiliary space (if using iterative/in-place sort)
======================================================================*/