# Merge Overlapping Intervals (Sorting + Linear Scan)

## Problem Description
Given a list $I$ of $n$ intervals specified as $(x_i, y_i)$ pairs, return a list where all overlapping intervals are merged into disjoint intervals in worst-case $O(n \log n)$ time.

---

## Algorithm

### Intuition
By sorting all intervals in ascending order based on their start times ($x_i$), any intervals that can potentially overlap will appear contiguously. We maintain a running active interval: if the next interval starts before the current one ends, they overlap and can be merged by taking the maximum of their end boundaries; otherwise, the current interval is complete, and we start tracking a new one.

### Step-by-Step Procedure
1. **Base Case:** If $n \le 0$, return an empty list.
2. **Sort Intervals:** Sort the array of $n$ intervals in ascending order by start time ($x_i$) using Quick Sort or Merge Sort &rarr; $O(n \log n)$.
3. **Initialize Output:**
   - Set `count = 0`
   - Insert the first interval into the output buffer: `merged[0] = intervals[0]`
4. **Linear Merge Scan:** Traverse the sorted intervals from index $i = 1$ to $n - 1$:
   - If `intervals[i].start <= merged[count].end` (Overlapping):
     - Extend boundary: `merged[count].end = max(merged[count].end, intervals[i].end)`
   - Else (Disjoint):
     - Increment: `count = count + 1`
     - Append: `merged[count] = intervals[i]`
5. **Output Result:** Return the merged array containing `count + 1` intervals.

---

## Complexity Analysis

| Metric | Complexity | Notes |
| :--- | :--- | :--- |
| **Best-Case Time** | $O(n \log n)$ | Bounded by the initial sorting step |
| **Average-Case Time** | $O(n \log n)$ | Sorting dominates single linear pass |
| **Worst-Case Time** | $O(n \log n)$ | Guaranteed by Merge Sort / Heap Sort |
| **Auxiliary Space** | $O(n)$ | Required for storing the output merged list |

### Detailed Time Breakdown
* **Sorting Step:** Sorting $n$ intervals by start coordinate &rarr; $O(n \log n)$
* **Merging Scan:** Single linear traversal across $n - 1$ items with $O(1)$ comparisons and bounds updates &rarr; $O(n)$

$$\text{Total Time} = O(n \log n) + O(n) = \mathbf{O(n \log n)}$$

### Correctness
Sorting by start time guarantees that for any $j > i$, $\text{start}_j \ge \text{start}_i$. Therefore, an interval $j$ can only overlap with intervals before it if $\text{start}_j \le \max(\text{end}_k)$ for preceding overlapping intervals $k \le j$, which is continuously maintained by updating `merged[count].end`.
