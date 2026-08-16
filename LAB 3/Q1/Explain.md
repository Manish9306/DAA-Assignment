# Binary Search vs. Ternary Search Analysis

## 1. Algorithm Descriptions

### A. Binary Search
1. **Initialize** `low = 0` and `high = n - 1`.
2. **Loop** while `low <= high`:
   - Calculate midpoint: `mid = low + (high - low) / 2`.
   - **Comparison 1:** If `arr[mid] == x`, return `mid`.
   - **Comparison 2:** If `x < arr[mid]`, set `high = mid - 1`.
   - Else, set `low = mid + 1`.
3. If not found, return `-1`.

### B. Ternary Search
1. **Initialize** `low = 0` and `high = n - 1`.
2. **Loop** while `low <= high`:
   - Calculate step: `third = (high - low) / 3`.
   - Set midpoints: `mid1 = low + third`, `mid2 = high - third`.
   - **Comparison 1:** If `arr[mid1] == x`, return `mid1`.
   - **Comparison 2:** If `arr[mid2] == x`, return `mid2`.
   - **Comparison 3:** If `x < arr[mid1]`, set `high = mid1 - 1`.
   - **Comparison 4:** Else if `x > arr[mid2]`, set `low = mid2 + 1`.
   - Else, set `low = mid1 + 1` and `high = mid2 - 1`.
3. If not found, return `-1`.

---

## 2. Complexity Analysis

| Algorithm | Best Case Time | Average Case Time | Worst Case Time | Space Complexity | Max Comparisons / Iteration |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Binary Search** | O(1) | O(log₂ n) | O(log₂ n) | O(1) | 2 |
| **Ternary Search** | O(1) | O(log₃ n) | O(log₃ n) | O(1) | 4 |

---

## 3. Comparison Count Comparison

- **Binary Search (Worst Case):**  
  `2 * log₂(n)` comparisons

- **Ternary Search (Worst Case):**  
  `4 * log₃(n) = 4 * (log₂(n) / log₂(3)) ≈ 2.52 * log₂(n)` comparisons

> **Conclusion:** While ternary search reduces the search space faster per iteration (by 1/3 instead of 1/2), it requires up to 4 comparisons per iteration compared to binary search's 2 comparisons. Thus, **binary search makes fewer total comparisons** in practice.
