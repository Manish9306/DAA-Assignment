### Question 1: Fractional Knapsack with Deterioration Rate

**Algorithm:**
1. Sort items in descending order of decay rate lambda. By exchange argument, items that lose value faster per second must be processed earlier[cite: 1].
2. Initialize remaining knapsack capacity as W, current time step t = 0, and total_val = 0[cite: 1].
3. Traverse through sorted items:
   - Calculate current value density = (v[i] / w[i]) - lambda[i] * t[cite: 1].
   - If density <= 0, the item has completely spoiled, so ignore it[cite: 1].
   - Take min(w[i], remaining capacity)[cite: 1].
   - Add taken_weight * density to total_val, decrement remaining capacity, and increment t by 1[cite: 1].
4. Stop when the knapsack is full or all items are visited[cite: 1].

**Complexity:**
*   **Time Complexity:** O(n log n) overall[cite: 1]. Sorting items by lambda takes O(n log n)[cite: 1]. The greedy selection loop takes O(n)[cite: 1].
*   **Space Complexity:** O(n)[cite: 1].
