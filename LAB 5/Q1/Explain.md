# 1. Find Median Without Sorting (QuickSelect)

### Algorithm
1. **Partition:** Choose a random pivot and partition the array (elements $\le$ pivot on left, $>$ pivot on right)[cite: 1].
2. **Check Target:** If pivot index equals required index, return it[cite: 1]. If required index is smaller, search left half[cite: 1]. Else, search right half[cite: 1].
3. **Resolve Median:** If $N$ is odd, search for index $N/2$[cite: 1]. If $N$ is even, search for indices $(N/2 - 1)$ and $N/2$, then average them[cite: 1].

### Time Complexity
* **Average Case:** $O(N)$ (the subproblem size halves on average)[cite: 1]
* **Worst Case:** $O(N^2)$ (highly improbable due to random pivot)[cite: 1]
