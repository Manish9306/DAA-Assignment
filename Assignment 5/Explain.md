# Algorithm

1. **Define Binary Search Function:** Create a `findTransition` function that accepts a sorted binary array `A` (consisting of 0s followed by 1s) and its size `n`.
2. **Initialize Pointers:** Set search boundary pointers `low = 0` and `high = n - 1`.
3. **Execute Binary Search:** Loop while `low <= high`, calculating the midpoint index `mid = (low + high) / 2`.
4. **Evaluate Midpoint Value:** 
   * If `A[mid] == 0`, check if `mid` is the last index or if `A[mid + 1] == 1`. If so, return `mid + 1` as the index of the first `1`. Otherwise, narrow the search to the right half by setting `low = mid + 1`.
   * If `A[mid] == 1`, narrow the search to the left half by setting `high = mid - 1`.
5. **Handle No Transition Case:** Return `-1` if the loop ends without finding a transition (e.g., if the array contains no `1`s).
6. **Input and Execute:** In `main`, prompt the user to input array size `n` and its elements, call `findTransition(A, n)`, and print the index where the transition occurs or state if no transition was found.

---

# Complexity

* **Time Complexity: O(log N)** — Utilizes binary search to halve the search space during each iteration, where *N* is the number of elements in the array.
* **Space Complexity: O(N)** — Auxiliary stack space required to allocate memory for storing the input array elements in `main`.
