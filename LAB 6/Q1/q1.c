/*
================================================================================
Design and Analysis of Algorithm (DAA), Lab-06
Question 1: 1D Array Operations and Complexity Analysis
================================================================================

QUESTION:
1. 1D array operations and their complexities: Given an array with n unsorted integer
elements, what is the worst-case complexity of the following problems in terms of n:
(i) Finding the maximum element.
(ii) Finding the first and second largest elements.
(iii) Finding the mean.
(iv) Finding the median.
(v) Finding the standard deviation.
(vi) Finding the mode.
(vii) Removing all duplicates.
(viii) Reversing the elements of the array.
(ix) Partitioning the array with respect to a given random pivot element so that all elements 
     less than the pivot appear after all the elements greater than or equal to the pivot.

By choosing the proper input representation, write a program in C to validate your procedures
and derive the corresponding complexity analysis.

--------------------------------------------------------------------------------
WORST-CASE COMPLEXITY ANALYSIS:
--------------------------------------------------------------------------------
(i)   Maximum Element:
      - Algorithm: Linear scan through array maintaining the current maximum.
      - Comparisons: Exactly (n - 1).
      - Time Complexity: O(n), Auxiliary Space: O(1).

(ii)  First & Second Largest Elements:
      - Algorithm: Single pass tracking max1 and max2. Update max2 when a new max1
        is found or an element lies between max1 and max2.
      - Comparisons: At most 2(n - 1).
      - Time Complexity: O(n), Auxiliary Space: O(1).

(iii) Mean:
      - Algorithm: Compute sum = sum_{i=0}^{n-1} a[i], return sum / n.
      - Arithmetic: n additions and 1 division.
      - Time Complexity: O(n), Auxiliary Space: O(1).

(iv)  Median:
      - Algorithm: Sort copy in O(n log n) and return element at n/2 (or avg if even).
        (Note: Quickselect / BFPRT Median-of-Medians achieves linear O(n) time).
      - Time Complexity: O(n log n) [O(n) via Quickselect], Auxiliary Space: O(1) in-place / O(n) copy.

(v)   Standard Deviation:
      - Algorithm: Two passes: (1) Compute mean mu, (2) compute sum of (a[i] - mu)^2, sqrt(sum/n).
      - Time Complexity: O(n), Auxiliary Space: O(1).

(vi)  Mode (Most Frequent Element):
      - Algorithm: Sort array in O(n log n), then a single O(n) linear scan to track
        the longest contiguous run of equal elements.
      - Time Complexity: O(n log n), Auxiliary Space: O(1) auxiliary.

(vii) Removing All Duplicates:
      - Algorithm: Sort array in O(n log n), then use a two-pointer compaction in O(n)
        to keep only unique elements in-place.
      - Time Complexity: O(n log n), Auxiliary Space: O(1) in-place.

(viii)Reversing the Array:
      - Algorithm: Two-pointer swap from both ends inward (left = 0, right = n - 1).
      - Swaps: Exactly floor(n / 2).
      - Time Complexity: O(n), Auxiliary Space: O(1).

(ix)  Partitioning with Random Pivot (elements >= pivot appear before elements < pivot):
      - Algorithm: Two-pointer Hoare-style partitioning.
        Left pointer advances while a[left] >= pivot; right pointer advances backward
        while a[right] < pivot. Swap when out of order.
      - Time Complexity: O(n), Auxiliary Space: O(1).
================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

// Comparison function for qsort
int cmp(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

// (i) Maximum element: O(n) time, O(1) space
int find_max(const int a[], int n) {
    int max_val = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max_val) max_val = a[i];
    }
    return max_val;
}

// (ii) First and second largest elements: O(n) time, O(1) space
void find_first_second(const int a[], int n, int *m1, int *m2) {
    *m1 = *m2 = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (a[i] > *m1) {
            *m2 = *m1;
            *m1 = a[i];
        } else if (a[i] > *m2 && a[i] < *m1) {
            *m2 = a[i];
        }
    }
}

// (iii) Mean: O(n) time, O(1) space
double find_mean(const int a[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) sum += a[i];
    return sum / n;
}

// (iv) Median: O(n log n) via sorting (or O(n) via Quickselect), O(n) space
double find_median(const int a[], int n) {
    int *t = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) t[i] = a[i];
    qsort(t, n, sizeof(int), cmp);
    double med = (n % 2) ? t[n / 2] : (t[n / 2 - 1] + t[n / 2]) / 2.0;
    free(t);
    return med;
}

// (v) Standard Deviation: O(n) time, O(1) space
double find_std_dev(const int a[], int n) {
    double mean = find_mean(a, n);
    double sum_sq = 0.0;
    for (int i = 0; i < n; i++) sum_sq += (a[i] - mean) * (a[i] - mean);
    return sqrt(sum_sq / n);
}

// (vi) Mode: O(n log n) time, O(n) space
int find_mode(const int a[], int n, int *freq) {
    int *t = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) t[i] = a[i];
    qsort(t, n, sizeof(int), cmp);

    int mode = t[0], max_c = 1, cur_c = 1;
    for (int i = 1; i < n; i++) {
        cur_c = (t[i] == t[i - 1]) ? cur_c + 1 : 1;
        if (cur_c > max_c) {
            max_c = cur_c;
            mode = t[i];
        }
    }
    *freq = max_c;
    free(t);
    return mode;
}

// (vii) Remove Duplicates: O(n log n) time, O(1) auxiliary space
int remove_duplicates(int a[], int n) {
    if (n <= 1) return n;
    qsort(a, n, sizeof(int), cmp);
    int k = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] != a[k - 1]) a[k++] = a[i];
    }
    return k; // New length of deduplicated array
}

// (viii) Reverse Array in-place: O(n) time, O(1) space
void reverse_array(int a[], int n) {
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}

// (ix) Partition array: elements >= pivot appear before elements < pivot: O(n) time, O(1) space
int partition_pivot(int a[], int n, int pivot) {
    int i = 0, j = n - 1;
    while (i <= j) {
        while (i <= j && a[i] >= pivot) i++;
        while (i <= j && a[j] < pivot) j--;
        if (i < j) {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }
    return i; // Split point
}

// Helper to print an array
void print_array(const int a[], int n, const char *label) {
    printf("%-30s: [", label);
    for (int i = 0; i < n; i++) printf("%d%s", a[i], (i == n - 1) ? "" : ", ");
    printf("]\n");
}

int main() {
    printf("==================================================================\n");
    printf("        DAA Lab 06 - Question 1: 1D Array Operations & Complexities\n");
    printf("==================================================================\n\n");

    int a[] = {29, 10, 14, 37, 14, 29, 14, 8, 45, 10, 29, 3};
    int n = sizeof(a) / sizeof(a[0]);

    print_array(a, n, "Original Array");
    printf("\n--- Computed Operations ---\n");

    // (i) Maximum
    printf("(i)   Max Element                  : %d  [O(n) time, O(1) space]\n", find_max(a, n));

    // (ii) 1st and 2nd Largest
    int m1, m2;
    find_first_second(a, n, &m1, &m2);
    printf("(ii)  1st Largest: %d, 2nd Largest: %d  [O(n) time, O(1) space]\n", m1, m2);

    // (iii) Mean
    printf("(iii) Mean                         : %.4f  [O(n) time, O(1) space]\n", find_mean(a, n));

    // (iv) Median
    printf("(iv)  Median                       : %.4f  [O(n log n) Sort / O(n) Quickselect]\n", find_median(a, n));

    // (v) Standard Deviation
    printf("(v)   Standard Deviation           : %.4f  [O(n) time, O(1) space]\n", find_std_dev(a, n));

    // (vi) Mode
    int freq = 0;
    int mode = find_mode(a, n, &freq);
    printf("(vi)  Mode                         : %d (Frequency = %d)  [O(n log n) time]\n", mode, freq);

    // (vii) Remove Duplicates
    int dup[n]; for (int i = 0; i < n; i++) dup[i] = a[i];
    int new_n = remove_duplicates(dup, n);
    print_array(dup, new_n, "(vii) After Removing Duplicates");
    printf("      [New Length = %d, O(n log n) time, O(1) space]\n", new_n);

    // (viii) Reverse Array
    int rev[n]; for (int i = 0; i < n; i++) rev[i] = a[i];
    reverse_array(rev, n);
    print_array(rev, n, "(viii)After Reversing Array");
    printf("      [O(n) time, O(1) space]\n");

    // (ix) Partition Array (>= pivot first, then < pivot)
    int part[n]; for (int i = 0; i < n; i++) part[i] = a[i];
    int pivot = 14;
    int split = partition_pivot(part, n, pivot);
    print_array(part, n, "(ix)  Partitioned (Pivot = 14)");
    printf("      [Split Index = %d (0..%d >= 14, %d..%d < 14), O(n) time, O(1) space]\n\n",
           split, split - 1, split, n - 1);

    printf("==================================================================\n");
    return 0;
}
