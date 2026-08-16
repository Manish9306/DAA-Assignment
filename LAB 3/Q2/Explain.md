# Defective Coin Identification (Divide and Conquer)

## 1. Algorithm Description

### `findDefective(coins, left, right)`
A divide-and-conquer algorithm designed to locate a single lighter (defective) coin among genuine coins by comparing the total weight of two halves.

1. **Base Case:**
   - If `left == right`:
     - Compare `coins[left] < 10`.
     - If true, return index `left` (defective coin located).
     - Else, return `-1` (no defective coin found).

2. **Divide Step:**
   - Calculate midpoint: `mid = (left + right) / 2`.
   - Calculate total weight of left segment: `leftWeight = sum(coins[left...mid])`.
   - Calculate total weight of right segment: `rightWeight = sum(coins[mid+1...right])`.

3. **Conquer / Weigh Step:**
   - **Comparison:** Compare `leftWeight` with `rightWeight`.
   - If `leftWeight < rightWeight`: The lighter coin is in the left half $\rightarrow$ recursively call `findDefective(coins, left, mid)`.
   - Else if `rightWeight < leftWeight`: The lighter coin is in the right half $\rightarrow$ recursively call `findDefective(coins, mid + 1, right)`.
   - Else (`leftWeight == rightWeight`): Both sides weigh the same $\rightarrow$ return `-1` (no defective coin exists).

---

## 2. Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Best Case Time** | O(1) | When $N = 1$ (immediate base case). |
| **Worst Case Time** | O(n) | Recurrence relation is $T(n) = T(n/2) + O(n)$ due to linear summing at each level. |
| **Average Case Time**| O(n) | Follows the same recursion path down to the single element. |
| **Space Complexity** | O(log₂ n) | Auxiliary recursion stack space corresponding to tree depth $\log_2 n$. |
| **Weighing Comparisons**| log₂(n) + 1 | Exactly one scale comparison per recursive level, plus one check at the base case. |

---

## 3. Mathematical Recurrence Relation

### A. Time Complexity (Execution Time)
At each recursive step of size $k$, the algorithm computes the sum of elements using loops, requiring $O(k)$ operations:

$$T(n) = T\left(\frac{n}{2}\right) + O(n)$$

By **Master Theorem** (Case 3 where $a = 1, b = 2, f(n) = O(n)$):
$$T(n) = O(n)$$

*(Note: While the search tree has depth $O(\log n)$, the summation loops at each recursive level result in $n + \frac{n}{2} + \frac{n}{4} + \dots = O(n)$ total work).*

### B. Number of Scale Weighings (Comparison Metric)
Counting only the `comparisons` tracked in the code:

$$C(n) = C\left(\frac{n}{2}\right) + 1, \quad C(1) = 1$$
$$C(n) = \log_2(n) + 1$$
