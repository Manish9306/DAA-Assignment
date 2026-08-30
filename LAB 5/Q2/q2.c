/*
2. Find the K'th smallest element in a given list of N numbers without sorting the list. Do the complexity analysis of your algorithm.
*/

/*======================================================================
ALGORITHM: QUICKSELECT (HOARE'S SELECTION) FOR K-TH SMALLEST ELEMENT
======================================================================

1. Problem Definition:
   - Given an unsorted array of N numbers and an integer K (where 1 <= K <= N),
     find the K-th smallest element without sorting the entire array.
   - Sorting would take O(N log N) time; QuickSelect solves this in O(N) average time.

2. Core Idea / Intuition:
   - QuickSelect leverages the divide-and-conquer partition technique of QuickSort.
   - The array is partitioned around a chosen pivot element:
       * All elements smaller than or equal to the pivot are placed to its left.
       * All elements greater than the pivot are placed to its right.
       * The pivot ends up at its exact sorted position (index 'pivotIndex').
   - We target 0-based index targetIndex = K - 1:
       * If pivotIndex == targetIndex: The pivot IS the K-th smallest element.
       * If targetIndex < pivotIndex: The target is in the left subarray [low ... pivotIndex - 1].
       * If targetIndex > pivotIndex: The target is in the right subarray [pivotIndex + 1 ... high].
   - Crucially, we discard the other partition and recurse/iterate ONLY into the half 
     containing the target, reducing problem size geometrically.

3. Step-by-Step Algorithm:
   ------------------------------------------------------------------
   Algorithm: Partition(A, low, high)
   ------------------------------------------------------------------
   Step 1: Pick a pivot (e.g., randomized pivot to prevent worst case).
           Swap A[randomIdx] with A[high].
           pivot = A[high]
   Step 2: Initialize i = low - 1.
   Step 3: For j = low to high - 1:
             If A[j] <= pivot:
               i = i + 1
               Swap A[i] with A[j]
   Step 4: Swap A[i + 1] with A[high] (place pivot in its final sorted position).
   Step 5: Return i + 1 as pivotIndex.

   ------------------------------------------------------------------
   Algorithm: FindKthSmallest(A, N, K)
   ------------------------------------------------------------------
   Step 1: targetIndex = K - 1 (converting 1-based K to 0-based index).
   Step 2: low = 0, high = N - 1.
   Step 3: While low <= high:
             a. If low == high: Return A[low].
             b. pivotIndex = Partition(A, low, high)
             c. If pivotIndex == targetIndex:
                  Return A[pivotIndex] (found K-th smallest element).
             d. Else if targetIndex < pivotIndex:
                  high = pivotIndex - 1 (search left side).
             e. Else:
                  low = pivotIndex + 1 (search right side).
   Step 4: Return -1 (if K is out of range).

======================================================================
COMPLEXITY ANALYSIS
======================================================================

1. Time Complexity:
   - Best Case: O(N)
     Occurs when the pivot picked during the very first partitioning step
     happens to be the element at targetIndex = K - 1.
     Partitioning takes O(N) operations.

   - Average Case: O(N)
     Assuming roughly balanced partitions at each step (e.g., 50-50 or 90-10 split):
     The subproblem size decreases geometrically: N, N/2, N/4, N/8, ...
     Recurrence Relation:
         T(N) = T(N / 2) + O(N)
     Solving by expansion:
         T(N) = N + N/2 + N/4 + N/8 + ... <= N * (1 / (1 - 1/2)) = 2N = O(N).
     Using Master Theorem:
         T(N) = a * T(N/b) + f(N) where a = 1, b = 2, f(N) = Theta(N)
         Since log_b(a) = log_2(1) = 0, and f(N) = Omega(N^(0 + 1)),
         by Master Theorem Case 3: T(N) = Theta(N) = O(N).

   - Worst Case: O(N^2)
     Occurs when the chosen pivot is always the maximum or minimum element in the current range
     (e.g., unbalanced partitions of sizes 1 and N - 1 at every step).
     Recurrence Relation:
         T(N) = T(N - 1) + O(N)
         T(N) = N + (N - 1) + (N - 2) + ... + 1 = N(N + 1)/2 = O(N^2).
     Mitigation: Using a Randomized Pivot Selection scheme (picking a random index between low
     and high) ensures that the probability of encountering the worst-case is practically 0.

2. Space Complexity:
   - Auxiliary Space: O(1)
     The iterative implementation modifies the array in-place and requires no extra memory 
     or recursion call stack.
   - If implemented recursively, the auxiliary stack space is O(log N) average, O(N) worst case.
======================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Utility function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to print array elements
void printArray(int arr[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

// Partition function using Lomuto scheme with randomized pivot
int partition(int arr[], int low, int high) {
    // Pick a random pivot index between low and high
    int randomIdx = low + rand() % (high - low + 1);
    swap(&arr[randomIdx], &arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Iterative QuickSelect function to find the K-th smallest element (1-based index K)
int findKthSmallest(int arr[], int n, int k) {
    if (k < 1 || k > n) {
        printf("Error: K is out of valid range (1 to %d)!\n", n);
        return -1;
    }

    int targetIndex = k - 1; // Convert 1-based rank to 0-based array index
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        if (low == high) {
            return arr[low];
        }

        int pivotIndex = partition(arr, low, high);

        if (pivotIndex == targetIndex) {
            return arr[pivotIndex];
        } else if (targetIndex < pivotIndex) {
            high = pivotIndex - 1; // Search in the left partition
        } else {
            low = pivotIndex + 1;  // Search in the right partition
        }
    }

    return -1;
}

int main() {
    // Seed random number generator for randomized partition
    srand((unsigned int)time(NULL));

    int n, k;
    printf("========================================================\n");
    printf("  FIND K-TH SMALLEST ELEMENT (QUICKSELECT O(N))         \n");
    printf("========================================================\n\n");

    printf("Enter the number of elements (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input size!\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter %d integers separated by spaces:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input value!\n");
            free(arr);
            return 1;
        }
    }

    printf("Enter the value of K (1 <= K <= %d): ", n);
    if (scanf("%d", &k) != 1 || k < 1 || k > n) {
        printf("Invalid value of K! K must be between 1 and %d.\n", n);
        free(arr);
        return 1;
    }

    printf("\nOriginal Array:\n");
    printArray(arr, n);

    // Find K-th smallest element
    int result = findKthSmallest(arr, n, k);

    printf("\n--------------------------------------------------------\n");
    printf("Array Size (N)            : %d\n", n);
    printf("Rank (K)                  : %d\n", k);
    printf("The %d-th smallest element : %d\n", k, result);
    printf("--------------------------------------------------------\n");

    free(arr);
    return 0;
}
