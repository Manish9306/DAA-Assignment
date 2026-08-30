/*
4. Implement Heap Sort to sort N randomly generated elements stored in a file. Do the complexity analysis of your algorithm.
*/

/*======================================================================
ALGORITHM: HEAP SORT ON N RANDOMLY GENERATED ELEMENTS STORED IN A FILE
======================================================================

1. Problem Definition:
   - Generate N random integer elements and save them in an input file.
   - Read the elements from the file into memory.
   - Implement the Heap Sort algorithm using a Max-Heap data structure.
   - Sort the array in ascending order and write the sorted data to an output file.
   - Provide a formal time and space complexity analysis.

2. Core Idea / Intuition:
   - A Binary Max-Heap is a complete binary tree where each parent node's key
     is greater than or equal to the keys of its children (Heap Property).
   - Heap Sort works in two distinct phases:
     Phase 1: Build-Max-Heap from the unsorted array in O(N) time.
              The maximum element is now at the root (index 0).
     Phase 2: Repeatedly swap the root (current maximum) with the last element 
              of the heap, decrease heap size by 1, and call Max-Heapify on the root 
              to restore the Max-Heap property in O(log N) time.
   - Repeating Phase 2 for all N - 1 elements produces a completely sorted array.

3. Step-by-Step Algorithm:
   ------------------------------------------------------------------
   Algorithm: MaxHeapify(A, heapSize, i)
   ------------------------------------------------------------------
   Step 1: largest = i
   Step 2: leftChild  = 2 * i + 1
   Step 3: rightChild = 2 * i + 2
   Step 4: If leftChild < heapSize AND A[leftChild] > A[largest]:
             largest = leftChild
   Step 5: If rightChild < heapSize AND A[rightChild] > A[largest]:
             largest = rightChild
   Step 6: If largest != i:
             Swap A[i] and A[largest]
             MaxHeapify(A, heapSize, largest) // Recursively fix affected subtree

   ------------------------------------------------------------------
   Algorithm: BuildMaxHeap(A, N)
   ------------------------------------------------------------------
   Step 1: Leaf nodes are at indices from (N/2) to (N - 1) and already satisfy heap property.
   Step 2: For i = (N / 2 - 1) down to 0:
             MaxHeapify(A, N, i)

   ------------------------------------------------------------------
   Algorithm: HeapSort(A, N)
   ------------------------------------------------------------------
   Step 1: BuildMaxHeap(A, N)  // Converts input array into Max-Heap
   Step 2: For i = N - 1 down to 1:
             a. Swap A[0] (maximum element) with A[i] (current end of heap)
             b. MaxHeapify(A, i, 0) // Restore max-heap for reduced size i

======================================================================
COMPLEXITY ANALYSIS
======================================================================

1. Time Complexity:
   - MaxHeapify():
     At each node at height h, comparisons and potential recursive calls
     traverse down at most h levels.
     Time Complexity = O(h) = O(log N).

   - BuildMaxHeap():
     An array of N elements has at most ceil(N / 2^(h+1)) nodes at height h.
     Total cost = Sum_{h=0}^{floor(log N)} ceil(N / 2^(h+1)) * O(h)
                = O(N * Sum_{h=0}^{infinity} (h / 2^h))
     Since Sum_{h=0}^{infinity} (h / 2^h) converges to 2:
     Total cost = O(N * 2) = O(N) linear time!

   - HeapSort Extraction Loop:
     The loop executes (N - 1) times, each invoking MaxHeapify() costing O(log N).
     Extraction Time = (N - 1) * O(log N) = O(N log N).

   - Overall Time Complexity:
     * Best Case    : O(N log N)
     * Average Case : O(N log N)
     * Worst Case   : O(N log N)
     Unlike QuickSort, HeapSort GUARANTEES O(N log N) upper bound in ALL cases.

2. Space Complexity:
   - Auxiliary Space: O(1)
     HeapSort is an in-place sorting algorithm. It utilizes the array itself 
     as an implicit binary tree representation (Left child = 2i+1, Right child = 2i+2).
     Iterative heapify achieves strict O(1) space (recursive heapify uses O(log N) stack frames).
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

// Max-Heapify function to maintain the max heap property (iterative for O(1) auxiliary space)
void maxHeapify(int arr[], int n, int i) {
    int largest = i;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        largest = i;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(&arr[i], &arr[largest]);
            i = largest; // Continue down the tree
        } else {
            break;
        }
    }
}

// Function to build a max-heap from an unsorted array in O(N) time
void buildMaxHeap(int arr[], int n) {
    // Start from the last non-leaf node and heapify each node up to root
    for (int i = (n / 2) - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

// Main HeapSort function
void heapSort(int arr[], int n) {
    // Step 1: Build max heap
    buildMaxHeap(arr, n);

    // Step 2: Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root (maximum element) to end
        swap(&arr[0], &arr[i]);

        // Call maxHeapify on the reduced heap
        maxHeapify(arr, i, 0);
    }
}

// Function to generate N random integers and store in a file
int generateRandomFile(const char *filename, int n, int maxVal) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not open file %s for writing!\n", filename);
        return 0;
    }

    fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++) {
        int num = (rand() % maxVal) + 1; // Random number in range [1, maxVal]
        fprintf(fp, "%d ", num);
    }
    fprintf(fp, "\n");

    fclose(fp);
    return 1;
}

// Function to read N elements from a file into an array
int readArrayFromFile(const char *filename, int arr[], int *n) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Could not open file %s for reading!\n", filename);
        return 0;
    }

    if (fscanf(fp, "%d", n) != 1 || *n <= 0) {
        printf("Error: Invalid array size in file!\n");
        fclose(fp);
        return 0;
    }

    for (int i = 0; i < *n; i++) {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            printf("Error reading element at index %d from file!\n", i);
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);
    return 1;
}

// Function to write sorted array to an output file
int writeArrayToFile(const char *filename, int arr[], int n) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not open file %s for writing!\n", filename);
        return 0;
    }

    fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d ", arr[i]);
        if ((i + 1) % 10 == 0) {
            fprintf(fp, "\n");
        }
    }
    fprintf(fp, "\n");

    fclose(fp);
    return 1;
}

// Function to display preview of array
void displayArrayPreview(const char *label, int arr[], int n) {
    printf("%s (Total: %d):\n[ ", label, n);
    int limit = (n < 20) ? n : 20;
    for (int i = 0; i < limit; i++) {
        printf("%d ", arr[i]);
    }
    if (n > 20) {
        printf("... (and %d more)", n - 20);
    }
    printf(" ]\n\n");
}

int main() {
    srand((unsigned int)time(NULL));

    const char *inputFile = "input_q4.txt";
    const char *outputFile = "output_q4.txt";
    int n;

    printf("========================================================\n");
    printf("      HEAP SORT ON N RANDOM ELEMENTS STORED IN FILE     \n");
    printf("========================================================\n\n");

    printf("Enter the number of random elements (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input size!\n");
        return 1;
    }

    // Step 1: Generate N random numbers and write to input file
    printf("\n1. Generating %d random numbers into '%s'...\n", n, inputFile);
    if (!generateRandomFile(inputFile, n, 1000)) {
        return 1;
    }
    printf("   -> Done writing random elements to file.\n");

    // Step 2: Allocate memory and read back from file
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    int readCount = 0;
    printf("\n2. Reading elements from '%s'...\n", inputFile);
    if (!readArrayFromFile(inputFile, arr, &readCount)) {
        free(arr);
        return 1;
    }
    printf("   -> Successfully read %d elements.\n\n", readCount);

    displayArrayPreview("Original Unsorted Array", arr, readCount);

    // Step 3: Sort using Heap Sort and measure execution time
    printf("3. Executing Heap Sort...\n");
    clock_t start = clock();
    heapSort(arr, readCount);
    clock_t end = clock();
    double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("   -> Sorting completed in %f seconds.\n\n", timeTaken);

    displayArrayPreview("Sorted Array", arr, readCount);

    // Step 4: Write sorted array into output file
    printf("4. Writing sorted elements into '%s'...\n", outputFile);
    if (!writeArrayToFile(outputFile, arr, readCount)) {
        free(arr);
        return 1;
    }
    printf("   -> Successfully saved sorted elements to '%s'.\n", outputFile);

    printf("\n========================================================\n");
    printf("                    PROCESS COMPLETED                   \n");
    printf("========================================================\n");

    free(arr);
    return 0;
}
