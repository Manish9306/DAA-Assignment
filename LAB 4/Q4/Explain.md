# Maximum Simultaneous Guests (Sweep-Line / Event Sorting)

## Problem Description
Given entry times $a_i$ and exit times $b_i$ (where $b_i > a_i$) for $n$ persons attending an event, with all $2n$ timestamps being distinct, determine the time when the maximum number of people were simultaneously present in $O(n \log n)$ time.

---

## Algorithm

### Intuition
Each attendee's stay is represented by an interval $[a_i, b_i]$. We can decompose each interval into two independent timestamped events: an `ENTRY` event (which increases the active count by $+1$) and an `EXIT` event (which decreases the active count by $-1$). By sorting all $2n$ events chronologically and performing a linear sweep, we can track the exact running attendance and record the timestamp where the peak occurs.

### Step-by-Step Procedure
1. **Event Generation:** Construct an auxiliary array `events` of size $2n$. For each person $i$ from $0$ to $n - 1$:
   - Set `events[2 * i] = { time: a[i], type: ENTRY }`
   - Set `events[2 * i + 1] = { time: b[i], type: EXIT }`
2. **Sort Events:** Sort all $2n$ events in ascending order of `time` using Quick Sort or Merge Sort &rarr; $O(n \log n)$.
3. **Initialize Trackers:** Set `current_guests = 0`, `max_guests = 0`, and `peak_time = -1`.
4. **Chronological Sweep:** Iterate through the sorted `events` array from index $0$ to $2n - 1$:
   - If `events[i].type == ENTRY`:
     - Increment: `current_guests = current_guests + 1`
     - If `current_guests > max_guests`:
       - Update `max_guests = current_guests`
       - Update `peak_time = events[i].time`
   - If `events[i].type == EXIT`:
     - Decrement: `current_guests = current_guests - 1`
5. **Output Result:** Return `peak_time` and `max_guests`.

---

## Complexity Analysis

| Metric | Complexity | Notes |
| :--- | :--- | :--- |
| **Best-Case Time** | $O(n \log n)$ | Bounded by the event sorting step |
| **Average-Case Time** | $O(n \log n)$ | Sorting dominates linear sweep |
| **Worst-Case Time** | $O(n \log n)$ | Standard comparison-based sort of $2n$ elements |
| **Auxiliary Space** | $O(n)$ | Requires storage for $2n$ event structures |

### Detailed Time Breakdown
* **Event Creation:** Populating $2n$ events takes linear time &rarr; $O(n)$
* **Sorting Events:** Sorting $2n$ entries takes $O(2n \log(2n)) = O(2n (\log n + 1))$ &rarr; $O(n \log n)$
* **Sweep-Line Traversal:** Single pass through $2n$ elements with $O(1)$ updates per step &rarr; $O(n)$

$$\text{Total Time} = O(n) + O(n \log n) + O(n) = O(n \log n + 2n) = \mathbf{O(n \log n)}$$

### Correctness
Because all entry and exit times are distinct, each event uniquely increments or decrements the population at that instant. Processing events in strictly ascending chronological order guarantees that `current_guests` always reflects the exact number of people present in the room at that timestamp.
