# Pair Sum Search Across Two Sets (Two-Pointer Technique)

## Problem Description
Given two sets/arrays $S_1$ and $S_2$ (each of size $n$) and a target number $x$, determine whether there exists a pair $(a, b)$ such that $a \in S_1$, $b \in S_2$, and $a + b = x$ in $O(n \log n)$ time.

---

## Algorithm

### Intuition
By sorting both arrays, we can exploit the monotonic property of ordered sequences. Placing a pointer at the minimum element of $S_1$ and another at the maximum element of $S_2$ allows us to adjust the sum deterministically in linear time: incrementing the left pointer increases the sum, while decrementing the right pointer decreases it.

### Step-by-Step Procedure
1. **Sort Array $S_1$:** Sort $S_1$ in ascending order using Merge Sort or Quick Sort &rarr; $O(n \log n)$.
2. **Sort Array $S_2$:** Sort $S_2$ in ascending order using Merge Sort or Quick Sort &rarr; $O(n \log n)$.
3. **Initialize Pointers:**
   - Set pointer $i = 0$ (points to the smallest element in $S_1$).
   - Set pointer $j = n - 1$ (points to the largest element in $S_2$).
4. **Two-Pointer Search:** While $i < n$ and $j \ge 0$:
   - Calculate `current_sum` $= S_1[i] + S_2[j]$.
   - If `current_sum == x`: **Return `TRUE`** with pair $(S_1[i], S_2[j])$.
   - If `current_sum < x`: Increment $i$ by $1$ to increase the sum.
   - If `current_sum > x`: Decrement $j$ by $1$ to decrease the sum.
5. **Termination:** If the loop terminates without finding a match, **Return `FALSE`**.

---

## Complexity Analysis

| Metric | Complexity | Notes |
| :--- | :--- | :--- |
| **Best-Case Time** | $O(n \log n)$ | Bounded by sorting step |
| **Average-Case Time** | $O(n \log n)$ | Sorting dominates two-pointer search |
| **Worst-Case Time** | $O(n \log n)$ | Strictly bounded by sorting algorithms |
| **Auxiliary Space** | $O(1)$ to $O(n)$ | $O(1)$ if in-place Heap/Quick Sort; $O(n)$ if Merge Sort |

### Detailed Time Breakdown
* **Sort $S_1$:** Standard comparison-based sort &rarr; $O(n \log n)$
* **Sort $S_2$:** Standard comparison-based sort &rarr; $O(n \log n)$
* **Two-Pointer Traversal:** Pointer $i$ increments at most $n$ times, pointer $j$ decrements at most $n$ times; each iteration does $O(1)$ comparisons &rarr; $O(n)$

$$\text{Total Time} = O(n \log n) + O(n \log n) + O(n) = O(2n \log n + n) = \mathbf{O(n \log n)}$$

### Correctness
Since $S_1$ and $S_2$ are sorted, if $S_1[i] + S_2[j] < x$, then $S_1[i]$ cannot pair with any element at an index $\le j$ in $S_2$ to reach $x$. Thus, incrementing $i$ safely eliminates $S_1[i]$ without skipping valid pairs. A symmetric argument holds for decrementing $j$ when the sum exceeds $x$.
