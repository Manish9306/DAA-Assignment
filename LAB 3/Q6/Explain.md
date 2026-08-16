# Selection Sort: Algorithm & Complexity Analysis

## 1. Algorithm Description

### `selectionSort(arr, n)`
An in-place comparison-based sorting algorithm that divides the input array into two parts: a sorted subarray on the left and an unsorted subarray on the right. In each iteration, it finds the smallest element in the unsorted subarray and swaps it with the first unsorted element.

1. **Outer Loop:**
   - Iterate index `i` from `0` to `n - 2` (first `n - 1` elements).
   - Set `minIndex = i` (assume current element is the minimum).

2. **Inner Loop (Search Minimum):**
   - Iterate index `j` from `i + 1` to `n - 1`.
   - **Comparison:** Compare `arr[j] < arr[minIndex]`.
   - If true, update `minIndex = j`.

3. **Swap / Exchange:**
   - If `minIndex != i`:
     - Swap `arr[i]` and `arr[minIndex]`.
   - Subarray `arr[0...i]` is now sorted.

4. **Termination:**
   - After `n - 1` passes, the remaining single element at `arr[n - 1]` is automatically the largest element in its correct position.

---

## 2. Complexity Analysis

| Metric | Best Case | Average Case | Worst Case | Space Complexity |
| :--- | :--- | :--- | :--- | :--- |
| **Time Complexity** | $\mathbf{\Theta(n^2)}$ | $\mathbf{\Theta(n^2)}$ | $\mathbf{\Theta(n^2)}$ | $\mathbf{\Theta(1)}$ (In-place) |
| **Comparisons** | $\frac{n(n - 1)}{2}$ | $\frac{n(n - 1)}{2}$ | $\frac{n(n - 1)}{2}$ | — |
| **Swaps** | $0$ | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | — |

---

## 3. Mathematical Derivation of Comparisons

The inner loop performs $(n - 1 - i)$ comparisons for each outer loop iteration $i \in [0, n - 2]$:

$$C(n) = \sum_{i=0}^{n-2} (n - 1 - i) = (n - 1) + (n - 2) + \dots + 2 + 1 = \frac{n(n - 1)}{2} = \frac{n^2 - n}{2}$$

- **Worst-Case Time:** $\Theta(n^2)$
- **Best-Case Time:** $\Theta(n^2)$ — **Not any better**, because the algorithm must scan all remaining unsorted elements to confirm the minimum even if the array is already sorted.
- **Auxiliary Space:** $\Theta(1)$ — Only a few primitive variables (`i`, `j`, `minIndex`, `temp`) are used.
