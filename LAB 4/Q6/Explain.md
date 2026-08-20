# Point of Maximum Overlapping Intervals (Sweep-Line Approach)

## Problem Description
Given a set $S$ of $n$ closed intervals on a 1D line, where each interval $i$ is defined by its endpoints $[l_i, r_i]$ (inclusive), find a point $p$ on the line that is contained in the maximum number of intervals in $O(n \log n)$ time.

---

## Algorithm

### Intuition
Every closed interval $[l_i, r_i]$ contributes $+1$ to the overlap count starting at $l_i$ and $-1$ immediately after $r_i$. By decomposing intervals into $2n$ discrete coordinate events (`START` and `END`), sorting them along the real number line, and scanning left-to-right, we can track the active overlap count at each transition. Because endpoints are inclusive, a `START` event takes precedence over an `END` event at identical coordinates.

### Step-by-Step Procedure
1. **Event Decomposition:** Create an array `events` of size $2n$. For each interval $i$ from $0$ to $n - 1$:
   - `events[2 * i] = { coordinate: l_i, type: START }`
   - `events[2 * i + 1] = { coordinate: r_i, type: END }`
2. **Sort Events:** Sort the $2n$ events using Quick Sort or Merge Sort:
   - Primary key: Ascending order of `coordinate`.
   - Secondary key (tie-breaker): `START` before `END` if coordinates are equal.
3. **Initialize Trackers:** Set `current_overlap = 0`, `max_overlap = 0`, and `best_point = events[0].coordinate`.
4. **Sweep-Line Traversal:** Iterate through `events` from index $0$ to $2n - 1$:
   - If `events[i].type == START`:
     - Increment: `current_overlap = current_overlap + 1`
     - If `current_overlap > max_overlap`:
       - Update `max_overlap = current_overlap`
       - Update `best_point = events[i].coordinate`
   - If `events[i].type == END`:
     - Decrement: `current_overlap = current_overlap - 1`
5. **Output Result:** Return `best_point` and `max_overlap`.

---

## Complexity Analysis

| Metric | Complexity | Notes |
| :--- | :--- | :--- |
| **Best-Case Time** | $O(n \log n)$ | Bounded by sorting the event points |
| **Average-Case Time** | $O(n \log n)$ | Sorting dominates linear traversal |
| **Worst-Case Time** | $O(n \log n)$ | Standard comparison-based sort of $2n$ points |
| **Auxiliary Space** | $O(n)$ | Required for storing $2n$ event records |

### Detailed Time Breakdown
* **Event Array Initialization:** Extracting $2n$ endpoints from $n$ intervals &rarr; $O(n)$
* **Sorting Step:** Sorting $2n$ event structures &rarr; $O(2n \log(2n)) = O(n \log n)$
* **Linear Sweep:** Iterating through $2n$ events with $O(1)$ comparisons and updates &rarr; $O(n)$

$$\text{Total Time} = O(n) + O(n \log n) + O(n) = \mathbf{O(n \log n)}$$

### Correctness
The tie-breaking rule (`START` before `END`) guarantees that when multiple intervals start and end at the exact same point $x$, all incoming intervals are counted before any outgoing intervals are subtracted, correctly evaluating closed intervals where boundary points are shared.
