# 2. Find K-th Smallest Element (QuickSelect)

### Algorithm
1. **Define Target:** Convert 1-based $K$ to 0-based target index $(K - 1)$[cite: 1].
2. **Partition:** Pick a random pivot and partition the array[cite: 1].
3. **Select:** If pivot ends up at target index, return it[cite: 1]. If target is less than pivot index, iterate left; otherwise iterate right[cite: 1].

### Time Complexity
* **Average Case:** $O(N)$ (search space decreases geometrically)[cite: 1]
* **Worst Case:** $O(N^2)$[cite: 1]
