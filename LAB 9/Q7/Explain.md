### Question 7: Minimise Deviation in Array (Two-Way Greedy with Max-Heap)

**Algorithm:**
1. Since odd numbers can only be multiplied by 2 at most once (because they become even), multiply every odd number by 2 first. Now every number is at its maximum possible value and is even[cite: 7].
2. Track the minimum element in the array[cite: 7].
3. In a loop:
   - Find the current maximum element in the array[cite: 7].
   - Calculate deviation = current_max - current_min, and update min_deviation[cite: 7].
   - If current_max is odd, we cannot divide it anymore, so we must stop[cite: 7].
   - Otherwise, divide current_max by 2, update current_min if needed, and continue[cite: 7].

**Complexity:**
*   **Time Complexity:** O(n log M) where M is the maximum value[cite: 7]. Using simple linear search takes O(n * log(max_val))[cite: 7]. Using a max heap takes O(n log(max_val) * log n)[cite: 7].
*   **Space Complexity:** O(n)[cite: 7].
