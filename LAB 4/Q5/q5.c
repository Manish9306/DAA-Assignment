/*5. Application of sorting-V: Given a list I of n intervals, specified as (xi, yi) pairs, return
a list where the overlapping intervals are merged. For I = {(1, 3), (2, 6), (8, 10), (7, 18)} the
output should be {(1, 6), (7, 18)}. Your algorithm should run in worst-case O(n· log n) time
complexity. By choosing a suitable input and output representation, write a program in C
to validate your algorithm.*/

/*======================================================================
MERGE OVERLAPPING INTERVALS ALGORITHM
======================================================================

Input  : A list I of n intervals, each given as (start, end) = (x_i, y_i).
Output : A list of merged, non-overlapping intervals.

----------------------------------------------------------------------
Intuitive Idea:
----------------------------------------------------------------------
1. Sort all intervals in ascending order based on their start times (x_i).
2. Start by placing the very first sorted interval into our merged list.
3. Traverse through the remaining intervals one by one:
   - Let the last merged interval be [curr_start, curr_end].
   - Let the next interval be [next_start, next_end].
   - If next_start <= curr_end:
       They overlap! Merge them by updating:
       curr_end = max(curr_end, next_end)
   - Else (next_start > curr_end):
       No overlap! Append the next interval as a brand new interval 
       in the merged list.
4. Continue until all intervals are processed.

----------------------------------------------------------------------
Formal Step-by-Step Algorithm:
----------------------------------------------------------------------
Step 1: If n <= 0, return an empty list.

Step 2: Sort the array of n intervals in ascending order based on 
        the start time (x_i) using Quick Sort or Merge Sort.
        - Time: O(n log n)

Step 3: Initialize:
        - merged_count = 0
        - merged[0] = intervals[0] (place the first interval)

Step 4: Traverse the sorted intervals from i = 1 to n - 1:
        - If intervals[i].start <= merged[merged_count].end:
            // Overlapping case: expand the end time if needed
            merged[merged_count].end = max(merged[merged_count].end, intervals[i].end)
        - Else:
            // Non-overlapping case: add as a new interval
            merged_count = merged_count + 1
            merged[merged_count] = intervals[i]

Step 5: Return the merged list containing (merged_count + 1) intervals.
======================================================================*/

#include <stdio.h>
#include <stdlib.h>

// Structure to represent an interval (start, end)
typedef struct {
    int start;
    int end;
} Interval;

// Comparator function to sort intervals by start time in ascending order
int compareIntervals(const void* a, const void* b) {
    Interval* int1 = (Interval*)a;
    Interval* int2 = (Interval*)b;

    if (int1->start < int2->start) return -1;
    if (int1->start > int2->start) return 1;
    return 0;
}

// Helper function to find maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to merge overlapping intervals in O(n log n) time
int mergeIntervals(Interval intervals[], int n, Interval merged[]) {
    if (n <= 0) return 0;

    // Step 1: Sort intervals based on starting time - O(n log n)
    qsort(intervals, n, sizeof(Interval), compareIntervals);

    // Step 2: Initialize merged list with the first interval
    int count = 0;
    merged[count] = intervals[0];

    // Step 3: Traverse through the sorted intervals - O(n)
    for (int i = 1; i < n; i++) {
        // If current interval overlaps with the previous merged interval
        if (intervals[i].start <= merged[count].end) {
            merged[count].end = max(merged[count].end, intervals[i].end);
        } else {
            // No overlap, add as a new merged interval
            count++;
            merged[count] = intervals[i];
        }
    }

    // Return the number of merged intervals
    return count + 1;
}

void printIntervals(Interval arr[], int n) {
    printf("{ ");
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)", arr[i].start, arr[i].end);
        if (i < n - 1) printf(", ");
    }
    printf(" }\n");
}

int main() {
    // Input list of intervals given in the question:
    // I = {(1, 3), (2, 6), (8, 10), (7, 18)}
    Interval intervals[] = {
        {1, 3},
        {2, 6},
        {8, 10},
        {7, 18}
    };
    int n = sizeof(intervals) / sizeof(intervals[0]);

    printf("Original Intervals:\n");
    printIntervals(intervals, n);

    // Array to store the merged intervals (at most n intervals)
    Interval merged[100];
    int merged_size = mergeIntervals(intervals, n, merged);

    printf("\nMerged Intervals (Non-overlapping):\n");
    printIntervals(merged, merged_size);

    return 0;
}

/*======================================================================
TIME COMPLEXITY ANALYSIS
======================================================================

Overall Time Complexity: O(n log n)

----------------------------------------------------------------------
Step-by-Step Breakdown:
----------------------------------------------------------------------

1. Sorting the Intervals:
   - Sorting n intervals by their starting times using Quick Sort / Merge Sort:
     Time = O(n log n)

2. Linear Scan & Merge (Pass):
   - We iterate through the remaining (n - 1) intervals once.
   - For each interval, we do a constant-time comparison and assignment: O(1).
   - Total time for the merge pass:
     Time = O(n)

----------------------------------------------------------------------
Total Time Complexity Calculation:
----------------------------------------------------------------------

Total Time = O(n log n) [Sorting] + O(n) [Merging Scan]
           = O(n log n + n)
           = O(n log n)

----------------------------------------------------------------------
Final Verdict:
----------------------------------------------------------------------
- Worst-Case Time Complexity   : O(n log n)
- Best-Case Time Complexity    : O(n log n) (dominated by sorting)
- Average-Case Time Complexity : O(n log n)

Space Complexity:
- Auxiliary Space: O(n) to store the output merged intervals.
======================================================================*/