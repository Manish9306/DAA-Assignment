
### Question 3: Minimum Initial Fuel (Reverse Greedy)

**Algorithm:**
1. Sort fuel stations in ascending order of their distances from the origin[cite: 3].
2. Maintain available fuel and keep moving forward from the current position[cite: 3].
3. Keep track of all gas stations that we have already crossed but haven't used yet[cite: 3].
4. If fuel is not enough to reach the next station (or target D), greedily pick the station with maximum fuel from our passed-by pool[cite: 3].
5. If the pool is empty and we still cannot reach the next mark, it is impossible[cite: 3].
6. Count how many times we had to take fuel[cite: 3].

**Complexity:**
*   **Time Complexity:** O(n^2) or O(n log n) overall[cite: 3]. Sorting stations takes O(n log n)[cite: 3]. Greedy selection takes O(n log n) with a priority queue or O(n^2) with an array pool[cite: 3].
*   **Space Complexity:** O(n)[cite: 3].
