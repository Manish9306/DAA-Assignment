/*4. Application of sorting-IV: A camera at the door tracks the entry time ai and exit time bi
(assume bi > ai) for each of n the persons pi attending a party. Give an O(n·log n) algorithm
that analyses this data to determine the time when the most people were simultaneously
present at the party. Assume that all entry and exit times are distinct (no ties). By choosing
the proper input representation, write a program in C to validate your algorithm.*/

/*======================================================================
MAXIMUM SIMULTANEOUS GUESTS ALGORITHM (Sweep-Line / Event Sorting)
======================================================================

Input  : An array of n intervals representing entry time a[i] and exit 
         time b[i] for n persons, where b[i] > a[i] and all times are distinct.
Output : The time at which the maximum number of people were present, 
         along with the peak count of people.

----------------------------------------------------------------------
Intuitive Idea:
----------------------------------------------------------------------
1. Treat each person's entry and exit as individual timestamped "events":
   - An 'ENTRY' event increases the count of people present by +1.
   - An 'EXIT' event decreases the count of people present by -1.
2. We have n people, which creates 2n total events (n entries, n exits).
3. Sort all 2n events in ascending order of their time.
4. Scan through the sorted events chronologically while maintaining a 
   running counter:
   - When an 'ENTRY' happens: current_count++
   - When an 'EXIT' happens : current_count--
5. Keep track of the maximum value of current_count and the time it occurred.

----------------------------------------------------------------------
Formal Step-by-Step Algorithm:
----------------------------------------------------------------------
Step 1: Create an array 'events' of size 2n.

Step 2: For each person i from 0 to n - 1:
        - events[2*i]     = { time: a[i], type: ENTRY (+1) }
        - events[2*i + 1] = { time: b[i], type: EXIT  (-1) }

Step 3: Sort the 'events' array of size 2n in ascending order of time 
        using Quick Sort or Merge Sort.
        - Time: O(2n * log(2n)) = O(n log n)

Step 4: Initialize tracking variables:
        - current_guests = 0
        - max_guests = 0
        - peak_time = -1

Step 5: Traverse the sorted events array from index 0 to 2n - 1:
        - If events[i].type == ENTRY:
            current_guests = current_guests + 1
            If current_guests > max_guests:
                max_guests = current_guests
                peak_time = events[i].time
        - Else If events[i].type == EXIT:
            current_guests = current_guests - 1

Step 6: Return peak_time and max_guests.
======================================================================*/

#include <stdio.h>
#include <stdlib.h>

// Event types: ENTRY adds a person (+1), EXIT removes a person (-1)
typedef enum {
    ENTRY = 1,
    EXIT = -1
} EventType;

// Structure to represent a single timestamped event
typedef struct {
    int time;
    EventType type;
} Event;

// Comparator function to sort events chronologically by time
int compareEvents(const void* a, const void* b) {
    Event* event1 = (Event*)a;
    Event* event2 = (Event*)b;
    
    if (event1->time < event2->time) return -1;
    if (event1->time > event2->time) return 1;
    return 0;
}

// Function to find the time with the maximum guests present
void findMaxGuestsTime(int arrival[], int exit[], int n) {
    int total_events = 2 * n;
    Event* events = (Event*)malloc(total_events * sizeof(Event));

    if (events == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Step 1: Populate 2n events (n arrivals and n exits)
    for (int i = 0; i < n; i++) {
        events[2 * i].time = arrival[i];
        events[2 * i].type = ENTRY;

        events[2 * i + 1].time = exit[i];
        events[2 * i + 1].type = EXIT;
    }

    // Step 2: Sort all 2n events by time - O(n log n)
    qsort(events, total_events, sizeof(Event), compareEvents);

    // Step 3: Sweep-line scan to track simultaneous guests - O(n)
    int current_guests = 0;
    int max_guests = 0;
    int peak_time = events[0].time;

    for (int i = 0; i < total_events; i++) {
        if (events[i].type == ENTRY) {
            current_guests++;
            // Update peak record when a new maximum is reached
            if (current_guests > max_guests) {
                max_guests = current_guests;
                peak_time = events[i].time;
            }
        } else if (events[i].type == EXIT) {
            current_guests--;
        }
    }

    // Print the final result
    printf("Maximum guests present simultaneously: %d\n", max_guests);
    printf("Peak time when this occurred          : Time %d\n", peak_time);

    free(events);
}

int main() {
    // Entry and exit times for n = 5 people
    // Person 0: [1, 5], Person 1: [2, 8], Person 2: [6, 10], Person 3: [3, 7], Person 4: [9, 12]
    int arrival[] = {1, 2, 6, 3, 9};
    int exit[]    = {5, 8, 10, 7, 12};
    int n = sizeof(arrival) / sizeof(arrival[0]);

    printf("Party Guest Intervals:\n");
    for (int i = 0; i < n; i++) {
        printf("Person %d: Entry = %2d, Exit = %2d\n", i + 1, arrival[i], exit[i]);
    }
    printf("----------------------------------------\n");

    findMaxGuestsTime(arrival, exit, n);

    return 0;
}

/*======================================================================
TIME COMPLEXITY ANALYSIS
======================================================================

Overall Time Complexity: O(n log n)

----------------------------------------------------------------------
Step-by-Step Breakdown:
----------------------------------------------------------------------

1. Creating Events Array:
   - Creating 2n events from n (entry, exit) intervals takes linear time:
     Time = O(n)

2. Sorting the Events Array:
   - There are 2n event items.
   - Sorting 2n items using Quick Sort / Merge Sort takes:
     Time = O(2n * log(2n)) = O(n log n)

3. Linear Sweep (Chronological Scan):
   - Traversing the 2n sorted events once and updating counters takes:
     Time = O(2n) = O(n)

----------------------------------------------------------------------
Total Time Complexity Calculation:
----------------------------------------------------------------------

Total Time = O(n) [Creation] + O(n log n) [Sorting] + O(n) [Sweep]
           = O(n log n + 2n)
           = O(n log n)

----------------------------------------------------------------------
Final Verdict:
----------------------------------------------------------------------
- Worst-Case Time Complexity   : O(n log n)
- Best-Case Time Complexity    : O(n log n) (dominated by sorting)
- Average-Case Time Complexity : O(n log n)

Space Complexity:
- Auxiliary Space = O(n) to store the 2n event elements.
======================================================================*/