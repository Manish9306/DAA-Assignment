/*6. Application of sorting-VI: You are given a set S of n intervals on a line, with the ith
interval described by its left and right endpoints (li, ri). Give an O(n · log n) algorithm to
identify a point p on the line that is in the largest number of intervals. As an example, for
S = {(10, 40), (20, 60), (50, 90), (15, 70)} no point exists in all four intervals, but p = 50 is
an example of a point in three intervals. You can assume an endpoint counts as being in
its interval. By choosing a suitable input and output representation, write a program in C
to validate your algorithm.*/

/*======================================================================
MAXIMUM OVERLAPPING POINT ALGORITHM (Sweep-Line Approach)
======================================================================

Input  : A set S of n closed intervals, where each interval i is 
         defined by endpoints [l_i, r_i]. (Endpoints count as inside).
Output : A point p on the line that is contained in the maximum number 
         of intervals, along with that maximum overlap count.

----------------------------------------------------------------------
Intuitive Idea:
----------------------------------------------------------------------
1. Every interval [l_i, r_i] starts at point l_i and ends at point r_i.
2. We treat these endpoints as 2n distinct events:
   - A START event at l_i (+1 interval).
   - An END event at r_i (-1 interval).
3. Sort all 2n events in ascending order of coordinate.
   - Tie-breaking rule: Since endpoints are inclusive (closed intervals),
     if a START and an END event occur at the exact same coordinate,
     process the START event first so the point at that coordinate gets 
     counted for both intervals.
4. Sweep from left to right along the sorted events:
   - When encountering START: active_count++
   - Check and record if active_count beats max_count (and update point p).
   - When encountering END: active_count--

----------------------------------------------------------------------
Formal Step-by-Step Algorithm:
----------------------------------------------------------------------
Step 1: Create an array 'events' of size 2n.

Step 2: For each interval i from 0 to n - 1:
        - events[2*i]     = { point: l_i, type: START }
        - events[2*i + 1] = { point: r_i, type: END }

Step 3: Sort 'events' in ascending order of point value.
        - If events[i].point == events[j].point, place START before END.
        - Time: O(2n * log(2n)) = O(n log n)

Step 4: Initialize:
        - current_overlap = 0
        - max_overlap = 0
        - best_point = events[0].point

Step 5: Traverse 'events' from index 0 to 2n - 1:
        - If events[i].type == START:
            current_overlap = current_overlap + 1
            If current_overlap > max_overlap:
                max_overlap = current_overlap
                best_point = events[i].point
        - Else If events[i].type == END:
            current_overlap = current_overlap - 1

Step 6: Return best_point and max_overlap.
======================================================================*/

#include <stdio.h>
#include <stdlib.h>

// START is defined as +1, END as -1
// By setting START = -1 and END = 1 for sorting comparison,
// START will sort before END when points have identical coordinates.
typedef enum {
    START = 0,
    END = 1
} PointType;

// Structure for an endpoint event
typedef struct {
    int coordinate;
    PointType type;
} Event;

// Structure for an interval
typedef struct {
    int l;
    int r;
} Interval;

// Comparator function to sort events chronologically
int compareEvents(const void* a, const void* b) {
    Event* e1 = (Event*)a;
    Event* e2 = (Event*)b;

    // Primary sort: by coordinate in ascending order
    if (e1->coordinate != e2->coordinate) {
        return (e1->coordinate < e2->coordinate) ? -1 : 1;
    }

    // Secondary sort: if coordinates are identical, START comes before END
    // (since intervals are closed and endpoints are inclusive)
    if (e1->type == START && e2->type == END) return -1;
    if (e1->type == END && e2->type == START) return 1;
    return 0;
}

// Function to find the point in the maximum number of intervals
void findMaxOverlapPoint(Interval intervals[], int n) {
    int total_events = 2 * n;
    Event* events = (Event*)malloc(total_events * sizeof(Event));

    if (events == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Step 1: Create 2n events from n intervals
    for (int i = 0; i < n; i++) {
        events[2 * i].coordinate = intervals[i].l;
        events[2 * i].type = START;

        events[2 * i + 1].coordinate = intervals[i].r;
        events[2 * i + 1].type = END;
    }

    // Step 2: Sort all 2n events - O(n log n)
    qsort(events, total_events, sizeof(Event), compareEvents);

    // Step 3: Sweep-line scan - O(n)
    int current_overlap = 0;
    int max_overlap = 0;
    int best_point = events[0].coordinate;

    for (int i = 0; i < total_events; i++) {
        if (events[i].type == START) {
            current_overlap++;
            if (current_overlap > max_overlap) {
                max_overlap = current_overlap;
                best_point = events[i].coordinate;
            }
        } else if (events[i].type == END) {
            current_overlap--;
        }
    }

    // Print result
    printf("Optimal Point (p)               : %d\n", best_point);
    printf("Maximum Number of Overlaps      : %d\n", max_overlap);

    free(events);
}

void printIntervals(Interval arr[], int n) {
    printf("{ ");
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)", arr[i].l, arr[i].r);
        if (i < n - 1) printf(", ");
    }
    printf(" }\n");
}

int main() {
    // Example from the problem description:
    // S = {(10, 40), (20, 60), (50, 90), (15, 70)}
    Interval S[] = {
        {10, 40},
        {20, 60},
        {50, 90},
        {15, 70}
    };
    int n = sizeof(S) / sizeof(S[0]);

    printf("Input Intervals:\n");
    printIntervals(S, n);
    printf("----------------------------------------\n");

    findMaxOverlapPoint(S, n);

    return 0;
}

/*======================================================================
TIME COMPLEXITY ANALYSIS
======================================================================

Overall Time Complexity: O(n log n)

----------------------------------------------------------------------
Step-by-Step Breakdown:
----------------------------------------------------------------------

1. Constructing Events Array:
   - Extracting 2n endpoints from n intervals takes linear time:
     Time = O(n)

2. Sorting 2n Events:
   - Sorting an array of size 2n using Quick Sort or Merge Sort:
     Time = O(2n * log(2n)) = O(n log n)

3. Linear Sweep Scan:
   - Traversing the 2n sorted events once and updating the running sum:
     Time = O(2n) = O(n)

----------------------------------------------------------------------
Total Time Complexity Calculation:
----------------------------------------------------------------------

Total Time = O(n) [Array Creation] + O(n log n) [Sorting] + O(n) [Sweep]
           = O(n log n + 2n)
           = O(n log n)

----------------------------------------------------------------------
Final Verdict:
----------------------------------------------------------------------
- Worst-Case Time Complexity   : O(n log n)
- Best-Case Time Complexity    : O(n log n) (dominated by sorting)
- Average-Case Time Complexity : O(n log n)

Space Complexity:
- Auxiliary Space = O(n) to store 2n event points.
======================================================================*/
