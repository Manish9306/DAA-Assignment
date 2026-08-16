/*2. Merge sort vs. modified merge sort: Consider the following modification to merge
sort: divide the input array into thirds (rather than halves), recursively sort each third,
and finally combine the results using a three-way merge subroutine. What is the worst-case
running time of this modified merge sort?

Write a C program to validate your claim by plotting the order of growth for both the
merge sort (discussed in the class) and the modified merge sort described above.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 1. STANDARD 2-WAY MERGE SORT

void merge2(int arr[], int low, int mid, int high, int temp[]) {
    int i = low, j = mid, k = low;

    while (i < mid && j < high) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i < mid)  temp[k++] = arr[i++];
    while (j < high) temp[k++] = arr[j++];

    for (i = low; i < high; i++) {
        arr[i] = temp[i];
    }
}

void mergeSort2Way(int arr[], int low, int high, int temp[]) {
    if (high - low <= 1) return;

    int mid = low + (high - low) / 2;
    mergeSort2Way(arr, low, mid, temp);
    mergeSort2Way(arr, mid, high, temp);
    merge2(arr, low, mid, high, temp);
}


// 2. MODIFIED 3-WAY MERGE SORT

void merge3(int arr[], int low, int mid1, int mid2, int high, int temp[]) {
    int i = low, j = mid1, k = mid2, l = low;

    // Merge elements while all three ranges have remaining items
    while (i < mid1 && j < mid2 && k < high) {
        if (arr[i] <= arr[j]) {
            if (arr[i] <= arr[k]) temp[l++] = arr[i++];
            else                 temp[l++] = arr[k++];
        } else {
            if (arr[j] <= arr[k]) temp[l++] = arr[j++];
            else                 temp[l++] = arr[k++];
        }
    }

    // Merge remaining elements from two non-empty ranges
    while (i < mid1 && j < mid2) {
        if (arr[i] <= arr[j]) temp[l++] = arr[i++];
        else                 temp[l++] = arr[j++];
    }
    while (j < mid2 && k < high) {
        if (arr[j] <= arr[k]) temp[l++] = arr[j++];
        else                 temp[l++] = arr[k++];
    }
    while (i < mid1 && k < high) {
        if (arr[i] <= arr[k]) temp[l++] = arr[i++];
        else                 temp[l++] = arr[k++];
    }

    // Copy remaining elements from a single non-empty range
    while (i < mid1) temp[l++] = arr[i++];
    while (j < mid2) temp[l++] = arr[j++];
    while (k < high) temp[l++] = arr[k++];

    // Copy back to original array
    for (i = low; i < high; i++) {
        arr[i] = temp[i];
    }
}

void mergeSort3Way(int arr[], int low, int high, int temp[]) {
    if (high - low <= 1) return;

    int len = high - low;
    int mid1 = low + len / 3;
    int mid2 = low + 2 * (len / 3);

    mergeSort3Way(arr, low, mid1, temp);
    mergeSort3Way(arr, mid1, mid2, temp);
    mergeSort3Way(arr, mid2, high, temp);

    merge3(arr, low, mid1, mid2, high, temp);
}


// UTILITIES & BENCHMARK DRIVER

void fillRandom(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }
}

void copyArray(const int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int main(void) {
    srand((unsigned int)time(NULL));

    // Array sizes to benchmark
    int sizes[] = {10000, 50000, 100000, 500000, 1000000, 2000000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("   ORDER OF GROWTH BENCHMARK: 2-WAY vs 3-WAY MERGE SORT          \n");
    printf("%-12s | %-18s | %-18s\n", "Array Size (N)", "2-Way Time (sec)", "3-Way Time (sec)");

    for (int idx = 0; idx < num_sizes; idx++) {
        int n = sizes[idx];

        int *original = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));
        int *arr3 = (int *)malloc(n * sizeof(int));
        int *temp = (int *)malloc(n * sizeof(int));

        if (!original || !arr2 || !arr3 || !temp) {
            fprintf(stderr, "Memory allocation failed for size %d\n", n);
            return 1;
        }

        fillRandom(original, n);

        // Measure 2-Way Merge Sort
        copyArray(original, arr2, n);
        clock_t start2 = clock();
        mergeSort2Way(arr2, 0, n, temp);
        clock_t end2 = clock();
        double time2 = (double)(end2 - start2) / CLOCKS_PER_SEC;

        // Measure 3-Way Merge Sort
        copyArray(original, arr3, n);
        clock_t start3 = clock();
        mergeSort3Way(arr3, 0, n, temp);
        clock_t end3 = clock();
        double time3 = (double)(end3 - start3) / CLOCKS_PER_SEC;

        printf("%-12d | %-18.6f | %-18.6f\n", n, time2, time3);

        free(original);
        free(arr2);
        free(arr3);
        free(temp);
    }

    printf("\n");
    return 0;
}


