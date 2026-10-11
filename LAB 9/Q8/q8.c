/*
Question 8: [Minimum Number of Meeting Rooms]
Given an array of meeting time intervals consisting of start and end times
[[s1, e1], [s2, e2], ...], find the minimum number of conference rooms required.
By choosing the proper input representation, write a program in C to validate
your procedures and derive the complexity analysis of your algorithm.

Algorithm:
1. Extract all start times into one array and all end times into another array.
2. Sort both start times and end times in ascending order.
3. Use two pointers, one for start times (i) and one for end times (j):
   - If start[i] < end[j], it means a meeting started before another meeting ended,
     so an additional room is needed (rooms++). Move pointer i.
   - Otherwise, a meeting ended and a room became free (rooms--). Move pointer j.
4. Keep track of the maximum value of rooms seen at any point.

Time Complexity:
- Sorting start and end times: O(n log n)
- Two pointer sweep: O(n)
Overall Time Complexity: O(n log n)
Space Complexity: O(n)
*/

#include <stdio.h>

void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, i;
    int start[100], end[100];

    printf("Enter number of meetings: ");
    scanf("%d", &n);

    printf("Enter start and end times for each meeting:\n");
    for (i = 0; i < n; i++) {
        printf("Meeting %d: ", i + 1);
        scanf("%d %d", &start[i], &end[i]);
    }

    sort(start, n);
    sort(end, n);

    int iPtr = 0, jPtr = 0;
    int curRooms = 0;
    int maxRooms = 0;

    while (iPtr < n && jPtr < n) {
        if (start[iPtr] < end[jPtr]) {
            curRooms++;
            if (curRooms > maxRooms) {
                maxRooms = curRooms;
            }
            iPtr++;
        } else {
            curRooms--;
            jPtr++;
        }
    }

    printf("\nMinimum number of meeting rooms required: %d\n", maxRooms);

    return 0;
}
