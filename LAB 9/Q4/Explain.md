### Question 4: Minimum Cost to Connect Sticks

**Algorithm:**
1. To minimize total cost, sticks merged earlier should be the shortest ones so their lengths are added into fewer future sums[cite: 4].
2. Store sticks in an array or min-heap[cite: 4].
3. In each step:
   - Pick the two smallest stick lengths[cite: 4].
   - Sum them up to form a new combined stick[cite: 4].
   - Add the sum to the running total cost[cite: 4].
   - Insert the new stick length back into the collection[cite: 4].
4. Repeat until only one stick is left[cite: 4].

**Complexity:**
*   **Time Complexity:** O(n log n) or O(n^2) overall[cite: 4]. Using a binary min-heap takes O(n log n)[cite: 4]. Using simple sorting / insertion takes O(n^2)[cite: 4].
*   **Space Complexity:** O(n)[cite: 4].
