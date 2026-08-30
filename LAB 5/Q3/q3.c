/*
3. Impliment Quick sort of N random elements store in a file.
*/

/*======================================================================
ALGORITHM: QUICKSORT ON N RANDOMLY GENERATED ELEMENTS STORED IN A FILE
======================================================================

1. Problem Definition:
   - Generate N random integer elements and write them to an input file.
   - Read the elements from the input file into memory.
   - Sort the elements using the QuickSort divide-and-conquer algorithm.
   - Write the sorted output to a destination file and display results.

2. Core Idea / Intuition:
   - QuickSort is an efficient, in-place, divide-and-conquer sorting algorithm.
   - A pivot element is selected from the array.
   - The array is partitioned into two sub-arrays around the pivot:
       * Left sub-array  : Elements <= Pivot
       * Right sub-array : Elements > Pivot
   - The pivot reaches its final sorted position.
   - Recursively apply QuickSort to both the left and right sub-arrays until 
     base cases (sub-arrays of size 0 or 1) are reached.

3. Step-by-Step Algorithm:
   ------------------------------------------------------------------
   Algorithm: Partition(A, low, high)
   ------------------------------------------------------------------
   Step 1: Choose pivot = A[high] (or randomized pivot swapped with A[high]).
   Step 2: Initialize i = low - 1 (index of smaller element).
   Step 3: For j = low to high - 1:
             If A[j] <= pivot:
               i = i + 1
               Swap A[i] with A[j]
   Step 4: Swap A[i + 1] with A[high] (place pivot at its correct sorted index).
   Step 5: Return i + 1 as pivotIndex.

   ------------------------------------------------------------------
   Algorithm: QuickSort(A, low, high)
   ------------------------------------------------------------------
   Step 1: If low < high:
             a. pivotIndex = Partition(A, low, high)
             b. QuickSort(A, low, pivotIndex - 1)   // Recursively sort left subarray
             c. QuickSort(A, pivotIndex + 1, high)  // Recursively sort right subarray

   ------------------------------------------------------------------
   Algorithm: File-Based Workflow
   ------------------------------------------------------------------
   Step 1: Prompt user for number of elements (N).
   Step 2: Generate N random numbers and save to "input_q3.txt".
   Step 3: Open "input_q3.txt" and load elements into an array.
   Step 4: Execute QuickSort on the array.
   Step 5: Write sorted array into "output_q3.txt".
   Step 6: Display confirmation, execution time, and data preview.

======================================================================
COMPLEXITY ANALYSIS
======================================================================

1. Time Complexity:
   - Best Case: O(N log N)
     Occurs when the partition process always picks the middle element 
     as pivot, dividing the array into two equal halves.
     Recurrence Relation:
         T(N) = 2 * T(N / 2) + Theta(N)
     By Master Theorem:
         a = 2, b = 2, f(N) = Theta(N)
         log_b(a) = log_2(2) = 1
         Since f(N) = Theta(N^1), by Case 2: T(N) = Theta(N log N).

   - Average Case: O(N log N)
     For randomly distributed inputs and pivots, the average depth of the 
     recursion tree is log_2(N), and each level takes O(N) partitioning time.
     Total Average Time = O(N log N).

   - Worst Case: O(N^2)
     Occurs when the partitioning always results in maximally unbalanced 
     subarrays of size 0 and N - 1 (e.g. already sorted array with extreme pivot).
     Recurrence Relation:
         T(N) = T(N - 1) + T(0) + Theta(N) = T(N - 1) + Theta(N)
         T(N) = N + (N - 1) + (N - 2) + ... + 1 = N(N + 1)/2 = O(N^2).
     Mitigation: Randomized pivot selection ensures worst-case is rarely hit.

2. Space Complexity:
   - Auxiliary Space:
     * Best / Average Case: O(log N) due to recursive call stack.
     * Worst Case: O(N) call stack frames.
     * Array is sorted in-place without extra data structures.
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

// Partition function (Lomuto Scheme with randomized pivot)
int partition(int arr[], int low, int high) {
    // Pick a random pivot to avoid worst-case O(N^2)
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

// Recursive QuickSort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
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

    const char *inputFile = "input_q3.txt";
    const char *outputFile = "output_q3.txt";
    int n;

    printf("========================================================\n");
    printf("     QUICKSORT ON N RANDOM ELEMENTS STORED IN FILE     \n");
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

    // Step 3: Sort using QuickSort and measure execution time
    printf("3. Executing QuickSort...\n");
    clock_t start = clock();
    quickSort(arr, 0, readCount - 1);
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
