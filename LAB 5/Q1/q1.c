/*
1. Find the median of a list of N numbers without sorting the list. Do the complexity analysis of your algorithm.
*/

/*======================================================================
ALGORITHM: QUICKSELECT (HOARE'S SELECTION ALGORITHM) FOR MEDIAN FINDING
======================================================================

1. Problem Definition:
   - Given an unsorted array of N numbers, find its median without 
     sorting the entire array (which would take O(N log N)).
   - If N is odd : Median is the element at index N / 2 (0-indexed).
   - If N is even: Median is the average of elements at indices (N/2 - 1) 
                   and (N/2).

2. Core Idea / Intuition:
   - QuickSelect is a selection algorithm based on the QuickSort partitioning mechanism.
   - In QuickSort, we partition the array around a pivot and recursively sort 
     BOTH subarrays on either side of the pivot.
   - In QuickSelect, after partitioning around a pivot (which lands at index 'p'):
       * If p == target_index (k): The pivot is the k-th smallest element!
       * If k < p: The desired element lies in the left subarray (left to p - 1).
       * If k > p: The desired element lies in the right subarray (p + 1 to right).
   - We only explore ONE subarray instead of both, achieving linear average time.

3. Step-by-Step Algorithm:
   ------------------------------------------------------------------
   Algorithm: Partition(A, low, high)
   ------------------------------------------------------------------
   Step 1: Choose a pivot (e.g., A[high] or randomized pivot swapped with A[high]).
   Step 2: Initialize index of smaller element: i = low - 1.
   Step 3: For j = low to high - 1:
             If A[j] <= pivot:
               i = i + 1
               Swap A[i] and A[j]
   Step 4: Swap A[i + 1] and A[high] (place pivot in its correct sorted position).
   Step 5: Return i + 1 as pivotIndex.

   ------------------------------------------------------------------
   Algorithm: QuickSelect(A, low, high, k)   [Iterative Version]
   ------------------------------------------------------------------
   Step 1: While low <= high:
             a. pivotIndex = Partition(A, low, high)
             b. If pivotIndex == k:
                  Return A[pivotIndex]
             c. Else if k < pivotIndex:
                  high = pivotIndex - 1
             d. Else:
                  low = pivotIndex + 1
   Step 2: Return A[low]

   ------------------------------------------------------------------
   Algorithm: FindMedian(A, N)
   ------------------------------------------------------------------
   Step 1: If N is odd:
             median = QuickSelect(A, 0, N - 1, N / 2)
             Return median
   Step 2: If N is even:
             mid1 = QuickSelect(A, 0, N - 1, N / 2 - 1)
             mid2 = QuickSelect(A, 0, N - 1, N / 2)
             median = (mid1 + mid2) / 2.0
             Return median

======================================================================
COMPLEXITY ANALYSIS
======================================================================

1. Time Complexity:
   - Best Case: O(N)
     Occurs when the pivot chosen at the first step is exactly at index k.
     Partitioning takes O(N) comparisons.

   - Average Case: O(N)
     On average, a good pivot roughly halves the search space at each step.
     Recurrence Relation:
         T(N) = T(N / 2) + O(N)
     Sum of geometric series:
         T(N) = N + N/2 + N/4 + N/8 + ... = N * (1 / (1 - 1/2)) = 2N = O(N).
     Using Master Theorem:
         T(N) = a * T(N/b) + f(N), where a = 1, b = 2, f(N) = O(N)
         log_b(a) = log_2(1) = 0
         Since f(N) = Omega(N^(0 + 1)), by Case 3: T(N) = Theta(N) = O(N).

   - Worst Case: O(N^2)
     Occurs when the pivot is always the maximum or minimum element 
     (e.g., already sorted array with extreme pivot choice without randomization),
     reducing subarray size by only 1 each step.
     Recurrence Relation:
         T(N) = T(N - 1) + O(N)
         T(N) = N + (N - 1) + (N - 2) + ... + 1 = N(N + 1)/2 = O(N^2).
     Mitigation: Randomized pivot selection reduces the probability of 
     worst-case behavior to near zero in practical scenarios.

2. Space Complexity:
   - Auxiliary Space: O(1)
     The iterative implementation operates directly in-place with no 
     extra memory or recursion stack.
   - If implemented recursively, stack space is O(log N) average, O(N) worst case.
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

// Partition function (Lomuto Partition Scheme with optional randomized pivot)
int partition(int arr[], int low, int high) {
    // Randomized pivot selection for optimal average-case performance
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

// Iterative QuickSelect to find the element at 0-indexed position 'k'
// (i.e., (k + 1)-th smallest element) in O(N) average time and O(1) extra space.
int quickSelect(int arr[], int low, int high, int k) {
    while (low <= high) {
        if (low == high) {
            return arr[low];
        }

        int pivotIndex = partition(arr, low, high);

        if (pivotIndex == k) {
            return arr[pivotIndex];
        } else if (k < pivotIndex) {
            high = pivotIndex - 1;
        } else {
            low = pivotIndex + 1;
        }
    }
    return -1;
}

// Function to find median of an array without sorting
double findMedian(int arr[], int n) {
    if (n <= 0) return 0.0;

    if (n % 2 != 0) {
        // Odd number of elements: median is at index n/2
        int medianVal = quickSelect(arr, 0, n - 1, n / 2);
        return (double)medianVal;
    } else {
        // Even number of elements: median is average of elements at n/2 - 1 and n/2
        int mid1 = quickSelect(arr, 0, n - 1, n / 2 - 1);
        int mid2 = quickSelect(arr, 0, n - 1, n / 2);
        return (mid1 + mid2) / 2.0;
    }
}

int main() {
    // Seed random number generator
    srand((unsigned int)time(NULL));

    int n;
    printf("====================================================\n");
    printf("  FIND MEDIAN WITHOUT SORTING (QUICKSELECT O(N))   \n");
    printf("====================================================\n\n");

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

    printf("\nOriginal Array:\n");
    printArray(arr, n);

    // Compute median
    double median = findMedian(arr, n);

    printf("\n----------------------------------------------------\n");
    printf("Array Size (N)       : %d (%s)\n", n, (n % 2 == 0) ? "Even" : "Odd");
    if (n % 2 != 0) {
        printf("Median (middle element) : %.2f\n", median);
    } else {
        printf("Median (avg of 2 middle elements) : %.2f\n", median);
    }
    printf("----------------------------------------------------\n");

    free(arr);
    return 0;
}