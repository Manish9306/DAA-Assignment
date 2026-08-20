# Stable Color Sort (Counting Sort Adaptation)

## Problem Description
Given an array of `n` pairs `(number, color)` pre-sorted in ascending order by `number`, sort the elements by `color` (all **RED** &rarr; **BLUE** &rarr; **YELLOW**) such that the relative numerical order for identical colors is preserved (stable sort) in $O(n)$ time.

---

## Algorithm

### Intuition
This is an adaptation of **Counting Sort**. Because the key space is small and fixed (3 colors), we count occurrences to determine partition boundaries, then scan the input array from left to right to place each element into its respective bucket in order, ensuring stability.

### Step-by-Step Procedure
1. **Initialize Counters:** Set `red_count = 0`, `blue_count = 0`, and `yellow_count = 0`.
2. **Pass 1 (Frequency Count):** Traverse the input array `A` from index `0` to `n - 1`:
   - Increment the counter corresponding to `A[i].color`.
3. **Compute Boundary Offsets:**
   - `red_index = 0`
   - `blue_index = red_count`
   - `yellow_index = red_count + blue_count`
4. **Pass 2 (Stable Placement):** Traverse the original array `A` from index `0` to `n - 1` (left-to-right):
   - If `A[i].color == RED`: assign `B[red_index++] = A[i]`
   - If `A[i].color == BLUE`: assign `B[blue_index++] = A[i]`
   - If `A[i].color == YELLOW`: assign `B[yellow_index++] = A[i]`
5. **Pass 3 (Copy Back):** Copy all `n` elements from auxiliary array `B` back into original array `A`.

---

## Complexity Analysis

| Metric | Complexity | Notes |
| :--- | :--- | :--- |
| **Best-Case Time** | $O(n)$ | Independent of initial arrangement |
| **Average-Case Time** | $O(n)$ | Three non-nested linear passes |
| **Worst-Case Time** | $O(n)$ | Strictly bounded by $3n + c$ operations |
| **Auxiliary Space** | $O(n)$ | Requires output buffer of size $n$ |

### Detailed Time Breakdown
* **Pass 1 (Count):** Iterates $n$ times with $O(1)$ work per item &rarr; $O(n)$
* **Boundary Calculation:** Constant number of additions &rarr; $O(1)$
* **Pass 2 (Placement):** Iterates $n$ times with $O(1)$ work per item &rarr; $O(n)$
* **Pass 3 (Copy):** Copies $n$ items from buffer back to source &rarr; $O(n)$

$$\text{Total Time} = O(n) + O(1) + O(n) + O(n) = O(3n + 1) = \mathbf{O(n)}$$

### Stability
Because Pass 2 scans array `A` sequentially from left to right (where elements are already sorted by number), elements sharing the same color are inserted into buffer `B` in non-decreasing order of their numerical values, guaranteeing stability.
