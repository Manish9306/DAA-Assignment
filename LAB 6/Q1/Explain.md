# Question 1: 1D Array Operations and Complexities

**Assumption:** The array has `n` unsorted integer elements.

*   **(i) Maximum element:** 
    *   **Algorithm:** Initialize `max = A[0]`. Iterate through the array from index 1 to $n-1$. If `A[i] > max`, update `max = A[i]`.
    *   **Worst-case Complexity:** $O(n)$

*   **(ii) First and second largest:**
    *   **Algorithm:** Initialize `max1` and `max2` to the minimum possible integer. Iterate through the array. If `A[i] > max1`, update `max2 = max1` and `max1 = A[i]`. Else if `A[i] > max2` and `A[i] != max1`, update `max2 = A[i]`.
    *   **Worst-case Complexity:** $O(n)$

*   **(iii) Mean:**
    *   **Algorithm:** Initialize `sum = 0`. Iterate through the array adding each element to `sum`. Return `sum / n`.
    *   **Worst-case Complexity:** $O(n)$

*   **(iv) Median:**
    *   **Algorithm:** Use the "Median of Medians" (Quickselect) algorithm to find the $n/2$-th smallest element without fully sorting the array.
    *   **Worst-case Complexity:** $O(n)$ 

*   **(v) Standard deviation:**
    *   **Algorithm:** Calculate the mean in one pass $O(n)$. In a second pass, sum the squared differences between each element and the mean. Divide by $n$ and take the square root. 
    *   **Worst-case Complexity:** $O(n)$

*   **(vi) Mode:**
    *   **Algorithm:** Use a Hash Map (or frequency array if range is known) to store frequencies of each element during a single pass, keeping track of the element with the maximum frequency.
    *   **Worst-case Complexity:** $O(n)$ 

*   **(vii) Removing duplicates:**
    *   **Algorithm:** Use a Hash Set to track seen elements. Iterate through the array; if an element is not in the set, add it and append it to a new logical array index. 
    *   **Worst-case Complexity:** $O(n)$ (amortized via Hash Set).

*   **(viii) Reversing elements:**
    *   **Algorithm:** Use two pointers, `left = 0` and `right = n-1`. Swap `A[left]` and `A[right]`, then increment `left` and decrement `right` until `left >= right`.
    *   **Worst-case Complexity:** $O(n)$

*   **(ix) Partitioning around a pivot:**
    *   **Algorithm:** Standard two-pointer partitioning (e.g., Lomuto's or Hoare's). Iterate through the array and swap elements such that elements $\ge$ pivot are placed at the end, and elements $<$ pivot are placed at the beginning.
    *   **Worst-case Complexity:** $O(n)$
