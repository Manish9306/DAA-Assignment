
# Question 4: Sorting via Reversal Procedure

### Part 1: Mathematical Proof for $O(n)$ Reversals
*   **Proof Approach (Pancake Sorting logic):** 
    We can sort the array using a variant of selection sort. To place the largest element at its correct position at the end of the unsorted portion:
    1. Find the maximum element in the current unsorted prefix. Let it be at index $k$.
    2. Apply `reverse(p, 0, k)` to bring this maximum element to the front (index 0).
    3. Apply `reverse(p, 0, unsorted_length - 1)` to move this maximum element to its correct final position at the end of the unsorted segment.
*   **Conclusion:** This requires at most 2 reversals per element. For $n$ elements, it takes at most $2n$ reversals, which is strictly $O(n)$ reversals.

### Part 2: $O(n \log^2 n)$ Cost Algorithm
*   **Algorithm (In-Place Merge Sort using Rotations):**
    1.  Divide the array into two halves recursively until reaching base cases of size 1.
    2.  Merge the two sorted halves. To merge two adjacent sorted blocks $A$ and $B$ (representing left and right halves) in-place without extra memory, use a block rotation technique via reversals.
    3.  A block swap/rotation of $AB \to BA$ can be done with exactly 3 reversals: $Reverse(A)$, $Reverse(B)$, and $Reverse(Total)$.
    4.  By using binary search to find the correct split points and applying rotations, two sorted arrays of combined size $N$ can be merged with a reversal cost of $O(N \log N)$.
    
*   **Cost Analysis:** 
    The recurrence relation for the overall cost is $T(n) = 2T(n/2) + O(n \log n)$. Solving this recurrence using the Master Theorem yields an overall sorting cost (where cost = number of elements reversed) of **$O(n \log^2 n)$**.
