# $k$-Sum Target Search (Sorting + Binary Search)

## Problem Description
Given a set $S$ of $n$ integers, a target sum $T$, and an integer $k \ge 1$, determine whether there exist $k$ distinct elements in $S$ that sum to $T$ in $O(n^{k-1} \log n)$ time.

---

## Algorithm

### Intuition
Sorting the array initially in $O(n \log n)$ time enables $O(\log n)$ random-access lookups via **Binary Search**. To find a $k$-subset that sums to $T$, we iterate through all possible combinations of the first $(k - 1)$ elements. For each combination, the required $k$-th element value is fixed as `needed` = $T - \sum \text{chosen}$, which can be looked up in the remaining sorted subarray using binary search.

### Step-by-Step Procedure
1. **Sort Array $S$:** Sort $S$ in ascending order using Quick Sort or Merge Sort &rarr; $O(n \log n)$.
2. **Select $(k - 1)$ Elements:** Use recursion or $(k - 1)$ nested loops to iterate over strictly increasing index combinations ($i_1 < i_2 < \dots < i_{k-1}$):
   - Calculate the partial sum: `current_sum` = $S[i_1] + S[i_2] + \dots + S[i_{k-1}]$
   - Compute the complement needed: `needed` = $T - \text{current\_sum}$
3. **Binary Search for Complement:**
   - Execute binary search for `needed` in the right subarray $S[i_{k-1} + 1 \dots n - 1]$.
   - If found: **Return `TRUE`** (and the $k$ indices).
4. **Termination:** If all combinations are exhausted without a match, **Return `FALSE`**.

---

## Complexity Analysis

| Metric | Complexity | Notes |
| :--- | :--- | :--- |
| **Best-Case Time** | $O(n \log n)$ | When target combination is found on early iterations |
| **Average-Case Time** | $O(n^{k-1} \log n)$ | Exhausts a fraction of combinations |
| **Worst-Case Time** | $O(n^{k-1} \log n)$ | Checks all possible $(k-1)$ combinations |
| **Auxiliary Space** | $O(k)$ to $O(n)$ | $O(k)$ recursion depth / index storage; $O(1)$ extra space if iterative |

### Detailed Time Breakdown
* **Initial Sort:** $O(n \log n)$
* **Outer Combinations:** Selecting $(k - 1)$ items from $n$ produces $\approx O(n^{k-1})$ total tuples.
* **Innermost Binary Search:** Searching the remaining suffix of length $\le n$ takes $O(\log n)$ per candidate tuple.

$$\text{Total Time} = O(n \log n) + O(n^{k-1}) \times O(\log n) = \mathbf{O(n^{k-1} \log n)}$$

### Correctness
Restricting the binary search strictly to indices greater than $i_{k-1}$ guarantees that all $k$ chosen indices are distinct ($i_1 < i_2 < \dots < i_k$), preventing duplicate usage of the same array element.
