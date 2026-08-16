# Finding Maximum and Minimum using Divide and Conquer

## 1. Algorithm Description

### `findMinMax(arr, low, high)`
A divide-and-conquer algorithm that finds both the maximum and minimum elements in an array by recursively splitting the array into halves, finding the extrema of both subproblems, and combining the results with 2 comparisons.

1. **Base Case 1 (Single Element):**
   - If `low == high`:
     - Set `result.min = arr[low]` and `result.max = arr[low]`.
     - Return `result` (0 element comparisons made).

2. **Base Case 2 (Two Elements):**
   - If `high == low + 1`:
     - **Comparison 1:** Compare `arr[low] < arr[high]`.
     - If true: `result.min = arr[low]`, `result.max = arr[high]`.
     - Else: `result.min = arr[high]`, `result.max = arr[low]`.
     - Return `result` (1 element comparison made).

3. **Divide Step:**
   - Compute midpoint: `mid = (low + high) / 2`.

4. **Conquer Step (Recursive Calls):**
   - `left = findMinMax(arr, low, mid)`
   - `right = findMinMax(arr, mid + 1, high)`

5. **Combine Step:**
   - **Comparison 1 (Max):** If `left.max > right.max`, set `result.max = left.max`; else `result.max = right.max`.
   - **Comparison 2 (Min):** If `left.min < right.min`, set `result.min = left.min`; else `result.min = right.min`.
   - Return `result` (2 element comparisons made to combine).

---

## 2. Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Best Case Time** | O(n) | Always splits the array completely down to base cases. |
| **Worst Case Time** | O(n) | Recurrence relation $T(n) = 2T(n/2) + 2$. |
| **Average Case Time** | O(n) | Number of steps is deterministic and depends solely on $n$. |
| **Space Complexity** | O(log₂ n) | Auxiliary recursion stack space for tree depth $\log_2 n$. |
| **Total Comparisons** | $\approx \frac{3n}{2} - 2$ | Exactly $\frac{3n}{2} - 2$ comparisons when $n$ is a power of 2. |

---

## 3. Comparison Count Recurrence Relation

### Mathematical Derivation (When $n$ is a power of 2):
- Base Case ($n = 1$): $T(1) = 0$
- Base Case ($n = 2$): $T(2) = 1$
- General Case:
  $$T(n) = 2T\left(\frac{n}{2}\right) + 2$$

Expanding the recurrence:
$$T(n) = 2\left[2T\left(\frac{n}{4}\right) + 2\right] + 2 = 4T\left(\frac{n}{4}\right) + 4 + 2$$
$$T(n) = 2^k T\left(\frac{n}{2^k}\right) + \sum_{i=1}^{k} 2^i$$

Let $\frac{n}{2^k} = 2 \implies 2^k = \frac{n}{2}$ (stopping at base case $n=2$ where $T(2) = 1$):
$$T(n) = \frac{n}{2} \cdot T(2) + (2 + 4 + \dots + n - 2)$$
$$T(n) = \frac{n}{2}(1) + 2(2^{\log_2(n/2)} - 1) = \frac{n}{2} + 2\left(\frac{n}{2} - 1\right)$$
$$T(n) = \frac{3n}{2} - 2$$

> **Key Takeaway:** A standard linear scan uses $2n - 2$ comparisons in the worst case (or $2n - 3$). The Divide and Conquer approach reduces total comparisons to $\approx \mathbf{1.5n - 2}$, achieving a $\approx 25\%$ reduction in element comparisons.
