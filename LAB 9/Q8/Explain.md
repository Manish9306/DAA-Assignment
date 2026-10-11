### Question 8: Minimum Number of Meeting Rooms

**Algorithm:**
1. Extract all start times into one array and all end times into another array[cite: 8].
2. Sort both start times and end times in ascending order[cite: 8].
3. Use two pointers, one for start times (i) and one for end times (j):
   - If start[i] < end[j], it means a meeting started before another meeting ended, so an additional room is needed (rooms++). Move pointer i[cite: 8].
   - Otherwise, a meeting ended and a room became free (rooms--). Move pointer j[cite: 8].
4. Keep track of the maximum value of rooms seen at any point[cite: 8].

**Complexity:**
*   **Time Complexity:** O(n log n) overall[cite: 8]. Sorting start and end times takes O(n log n)[cite: 8]. The two-pointer sweep takes O(n)[cite: 8].
*   **Space Complexity:** O(n)[cite: 8].
