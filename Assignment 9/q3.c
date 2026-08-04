/*3. Merging k sorted arrays: Suppose you are given k sorted arrays, each with n elements,
and you want to combine them into a single sorted array of kn elements.

(a) [Method 1] One approach is to use the merge subroutine repeatedly, merging the first
two arrays, then merging the result with the third array, then with the fourth array,
and so on until you merge in the kth and final input array. Write a program to validate
this idea. Also, find the worst-case running time of this method.

(b) [Method 2] Consider the algorithm that first divides the k arrays into k
2 pairs of arrays
and uses the merge subroutine to combine each pair, resulting in k
2 sorted-length2n
arrays. The algorithm repeats this step until there is only one length-kn sorted array.

Write a C program to validate this idea. What is the running time of this method as a
function of n and k?*/

/*
ALGORITHMS FOR MERGING k SORTED ARRAYS (EACH OF SIZE n)


1. METHOD 1: SEQUENTIAL / ITERATIVE MERGING

• Input:  An array of k sorted arrays `Arrays[0...k-1]`, each containing n elements.
• Output: A single sorted array `Result` of size (k * n).

• Algorithm Steps:
  1. Initialize `Result` as a copy of `Arrays[0]`.
  2. Set `current_size = n`.
  3. Loop `i` from 1 to `k - 1`:
     a. Allocate a temporary array `Temp` of size `(current_size + n)`.
     b. Merge sorted arrays `Result` (size `current_size`) and `Arrays[i]` (size `n`) into `Temp`.
     c. Update `Result = Temp`.
     d. Update `current_size = current_size + n`.
  4. Return `Result`.


2. METHOD 2: DIVIDE AND CONQUER / PAIRWISE MERGING

• Input:  An array of k sorted arrays `Arrays[0...k-1]`, each containing n elements.
• Output: A single sorted array `Result` of size (k * n).

• Algorithm Steps:
  1. Place all k arrays into a working list of arrays `CurrentList`.
  2. While size of `CurrentList` > 1:
     a. Create an empty list of arrays `NextList`.
     b. Loop `i` from 0 to `length(CurrentList) - 1` with step size 2:
        - If `(i + 1) < length(CurrentList)`:
            Merge `CurrentList[i]` and `CurrentList[i+1]` using standard 2-way merge.
            Append the merged result to `NextList`.
        - Else (odd array left out):
            Append `CurrentList[i]` directly to `NextList`.
     c. Set `CurrentList = NextList`.
  3. Return the single remaining array in `CurrentList`.*/

#include <stdio.h>
#include <stdlib.h>

// Standard 2-way merge subroutine
void merge(const int A[], int sizeA, const int B[], int sizeB, int result[]) {
    int i = 0, j = 0, k = 0;
    while (i < sizeA && j < sizeB) {
        if (A[i] <= B[j]) {
            result[k++] = A[i++];
        } else {
            result[k++] = B[j++];
        }
    }
    while (i < sizeA) result[k++] = A[i++];
    while (j < sizeB) result[k++] = B[j++];
}

// Utility function to print array
void printArray(const int arr[], int total_size) {
    for (int i = 0; i < total_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// METHOD 1: SEQUENTIAL / ITERATIVE MERGING

int* mergeKArraysMethod1(int** arrays, int k, int n) {
    int current_size = n;
    
    // Step 1: Initialize Result with first array
    int* result = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        result[i] = arrays[0][i];
    }

    // Step 2 & 3: Merge sequentially
    for (int i = 1; i < k; i++) {
        int next_size = current_size + n;
        int* temp = (int*)malloc(next_size * sizeof(int));
        
        merge(result, current_size, arrays[i], n, temp);
        
        free(result);
        result = temp;
        current_size = next_size;
    }

    return result;
}

// METHOD 2: DIVIDE AND CONQUER / PAIRWISE MERGING

int* mergeKArraysMethod2(int** arrays, int k, int n) {
    // Step 1: Initialize working list of buffers
    int** current_buffers = (int**)malloc(k * sizeof(int*));
    int* sizes = (int*)malloc(k * sizeof(int));

    for (int i = 0; i < k; i++) {
        current_buffers[i] = (int*)malloc(n * sizeof(int));
        sizes[i] = n;
        for (int j = 0; j < n; j++) {
            current_buffers[i][j] = arrays[i][j];
        }
    }

    int active_k = k;

    // Step 2: Pairwise reduction loop
    while (active_k > 1) {
        int next_k = (active_k + 1) / 2;
        int** next_buffers = (int**)malloc(next_k * sizeof(int*));
        int* next_sizes = (int*)malloc(next_k * sizeof(int));

        int out_idx = 0;
        for (int i = 0; i < active_k; i += 2) {
            if (i + 1 < active_k) {
                // Merge pair (i, i+1)
                int merged_size = sizes[i] + sizes[i + 1];
                next_buffers[out_idx] = (int*)malloc(merged_size * sizeof(int));
                next_sizes[out_idx] = merged_size;

                merge(current_buffers[i], sizes[i], current_buffers[i + 1], sizes[i + 1], next_buffers[out_idx]);

                free(current_buffers[i]);
                free(current_buffers[i + 1]);
                out_idx++;
            } else {
                // Odd array left out, pass to next round
                next_buffers[out_idx] = current_buffers[i];
                next_sizes[out_idx] = sizes[i];
                out_idx++;
            }
        }

        free(current_buffers);
        free(sizes);

        current_buffers = next_buffers;
        sizes = next_sizes;
        active_k = next_k;
    }

    // Step 3: Return final result
    int* final_result = current_buffers[0];
    free(current_buffers);
    free(sizes);

    return final_result;
}

// MAIN EXECUTION

int main(void) {
    int k = 4; // Number of sorted arrays
    int n = 3; // Elements per array

    // Example Input: 4 sorted arrays of size 3
    int a0[] = {1, 5, 9};
    int a1[] = {2, 6, 10};
    int a2[] = {3, 4, 7};
    int a3[] = {0, 8, 11};

    int* arrays[4] = {a0, a1, a2, a3};

    printf("Input Arrays:\n");
    for (int i = 0; i < k; i++) {
        printf("Array %d: ", i + 1);
        printArray(arrays[i], n);
    }
    printf("\n");

    // Execute Method 1
    int* res1 = mergeKArraysMethod1(arrays, k, n);
    printf("Method 1 Result (Sequential): ");
    printArray(res1, k * n);

    // Execute Method 2
    int* res2 = mergeKArraysMethod2(arrays, k, n);
    printf("Method 2 Result (Pairwise):   ");
    printArray(res2, k * n);

    // Cleanup
    free(res1);
    free(res2);

    return 0;
}

/*
TIME COMPLEXITY ANALYSIS FOR MERGING k SORTED ARRAYS (k ARRAYS, EACH OF SIZE n)


1. METHOD 1: SEQUENTIAL / ITERATIVE MERGING

• Analysis:
  - Step 1: Merge Array 1 (size n) and Array 2 (size n)      -> at most 2n comparisons.
  - Step 2: Merge Result (size 2n) and Array 3 (size n)     -> at most 3n comparisons.
  - Step 3: Merge Result (size 3n) and Array 4 (size n)     -> at most 4n comparisons.
  - ...
  - Step i: Merge Result (size i*n) and Array i+1 (size n)  -> at most (i + 1)n comparisons.
  - Step k-1: Merge Result (size (k-1)n) and Array k (n)    -> at most kn comparisons.

• Total Comparisons Formula:
  Sum_{i=2}^{k} (i * n) = n * [ (k * (k + 1) / 2) - 1 ]

• Worst-Case Time Complexity:
  O(n * k^2)   - Quadratic with respect to k.

• Best-Case Time Complexity:
  O(n * k^2)   - Even if elements are ordered ideally, intermediate arrays must still be fully copied.


2. METHOD 2: DIVIDE AND CONQUER / PAIRWISE MERGING

• Analysis:
  - Level 1: Merge k/2 pairs of arrays of size n            -> (k/2) * (2n) = k * n total operations.
  - Level 2: Merge k/4 pairs of arrays of size 2n           -> (k/4) * (4n) = k * n total operations.
  - Level 3: Merge k/8 pairs of arrays of size 4n           -> (k/8) * (8n) = k * n total operations.
  - ...
  - Tree Height: Total recursion/iteration depth is log_2(k) levels.

• Total Comparisons Formula:
  (Work per level) * (Tree Height) = (k * n) * ceil(log_2 k)

• Worst-Case Time Complexity:
  O(n * k * log k)   - Logarithmic with respect to k.

• Best-Case Time Complexity:
  O(n * k * log k)   - Structural height of the reduction tree remains log_2(k) for any array content.


3. SUMMARY COMPARISON
• Method 1 Running Time: O(n * k^2)       - Inefficient for large k due to re-scanning growing arrays.
• Method 2 Running Time: O(n * k log k)   - Optimal time complexity using balanced pairwise merges.*/