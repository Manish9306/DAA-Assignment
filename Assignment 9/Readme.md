/*
ALGORITHMS FOR MERGING k SORTED ARRAYS (EACH OF SIZE n)


1. METHOD 1: SEQUENTIAL / ITERATIVE MERGING

• Input:  An array of k sorted arrays `Arrays[0...k-1]`, each containing n elements.
• Output: A single sorted array `Result` of size (k * n).

• Algorithm Steps:
  1. Initialize `Result` as a copy of `Arrays[0]`.
  2. Set `current_size = n`.
  3. Loop `i` from 1 to `k - 1`:
     a. Allocate a temporary array `Temp` of size `(current_size + n)`.
     b. Merge sorted arrays `Result` (size `current_size`) and `Arrays[i]` (size `n`) into `Temp`.
     c. Update `Result = Temp`.
     d. Update `current_size = current_size + n`.
  4. Return `Result`.


2. METHOD 2: DIVIDE AND CONQUER / PAIRWISE MERGING

• Input:  An array of k sorted arrays `Arrays[0...k-1]`, each containing n elements.
• Output: A single sorted array `Result` of size (k * n).

• Algorithm Steps:
  1. Place all k arrays into a working list of arrays `CurrentList`.
  2. While size of `CurrentList` > 1:
     a. Create an empty list of arrays `NextList`.
     b. Loop `i` from 0 to `length(CurrentList) - 1` with step size 2:
        - If `(i + 1) < length(CurrentList)`:
            Merge `CurrentList[i]` and `CurrentList[i+1]` using standard 2-way merge.
            Append the merged result to `NextList`.
        - Else (odd array left out):
            Append `CurrentList[i]` directly to `NextList`.
     c. Set `CurrentList = NextList`.
  3. Return the single remaining array in `CurrentList`.*/

TIME COMPLEXITY ANALYSIS FOR MERGING k SORTED ARRAYS (k ARRAYS, EACH OF SIZE n)


1. METHOD 1: SEQUENTIAL / ITERATIVE MERGING

• Analysis:
  - Step 1: Merge Array 1 (size n) and Array 2 (size n)      -> at most 2n comparisons.
  - Step 2: Merge Result (size 2n) and Array 3 (size n)     -> at most 3n comparisons.
  - Step 3: Merge Result (size 3n) and Array 4 (size n)     -> at most 4n comparisons.
  - ...
  - Step i: Merge Result (size i*n) and Array i+1 (size n)  -> at most (i + 1)n comparisons.
  - Step k-1: Merge Result (size (k-1)n) and Array k (n)    -> at most kn comparisons.

• Total Comparisons Formula:
  Sum_{i=2}^{k} (i * n) = n * [ (k * (k + 1) / 2) - 1 ]

• Worst-Case Time Complexity:
  O(n * k^2)   - Quadratic with respect to k.

• Best-Case Time Complexity:
  O(n * k^2)   - Even if elements are ordered ideally, intermediate arrays must still be fully copied.


2. METHOD 2: DIVIDE AND CONQUER / PAIRWISE MERGING

• Analysis:
  - Level 1: Merge k/2 pairs of arrays of size n            -> (k/2) * (2n) = k * n total operations.
  - Level 2: Merge k/4 pairs of arrays of size 2n           -> (k/4) * (4n) = k * n total operations.
  - Level 3: Merge k/8 pairs of arrays of size 4n           -> (k/8) * (8n) = k * n total operations.
  - ...
  - Tree Height: Total recursion/iteration depth is log_2(k) levels.

• Total Comparisons Formula:
  (Work per level) * (Tree Height) = (k * n) * ceil(log_2 k)

• Worst-Case Time Complexity:
  O(n * k * log k)   - Logarithmic with respect to k.

• Best-Case Time Complexity:
  O(n * k * log k)   - Structural height of the reduction tree remains log_2(k) for any array content.


3. SUMMARY COMPARISON
• Method 1 Running Time: O(n * k^2)       - Inefficient for large k due to re-scanning growing arrays.
• Method 2 Running Time: O(n * k log k)   - Optimal time complexity using balanced pairwise merges
