/*
ALGORITHMIC ANALYSIS & COMPLEXITY FOR 2-WAY vs. 3-WAY MERGE SORT


1. STANDARD 2-WAY MERGE SORT
• Recurrence Relation:    T(n) = 2T(n/2) + Θ(n)
• Recursion Tree Height:  log_2(n) levels
• Divide Step:           O(1)   - Midpoint calculated in constant time [low + (high-low)/2].
• Conquer Step:          2T(n/2)- Two recursive calls on subarrays of size n/2.
• Combine (Merge Step):  O(n)   - At most (n - 1) comparisons to merge 2 sorted halves.
• Worst-Case Time:       O(n log_2 n) = O(n log n) - Derived via Master Theorem Case 2.
• Space Complexity:      O(n)   - Requires auxiliary array of size n for temporary merging.

2. MODIFIED 3-WAY MERGE SORT
• Recurrence Relation:    T(n) = 3T(n/3) + Θ(n)
• Recursion Tree Height:  log_3(n) levels
• Divide Step:           O(1)   - Two midpoints calculated in constant time [n/3 and 2n/3].
• Conquer Step:          3T(n/3)- Three recursive calls on subarrays of size n/3.
• Combine (Merge Step):  O(n)   - At most (2n - 2) comparisons to merge 3 sorted thirds.
• Worst-Case Time:       O(n log_3 n) = O(n log n) - Derived via Master Theorem Case 2.
• Space Complexity:      O(n)   - Requires auxiliary array of size n for temporary merging.

3. COMPARATIVE BREAKDOWN
• Asymptotic Complexity: Identical - Both belong to O(n log n).
• Recursion Depth:       3-Way tree is ~37% shallower than 2-Way [log_3(n) = log_2(n) / 1.585].
• Merge Overhead:        3-Way requires up to 2 comparisons per step to find min among 3 elements.
• Real-World Tradeoff:   3-Way reduces function call overhead, but increases comparison logic per merge pass.*/

/*

TIME COMPLEXITY BREAKDOWN (BEST, AVERAGE, WORST) FOR MERGE SORT VARIANTS


1. STANDARD 2-WAY MERGE SORT
• Best-Case Time:        O(n log n) - Occurs on any input; array is still split down to size 1.
• Average-Case Time:     O(n log n) - Expected performance across random permutations.
• Worst-Case Time:       O(n log n) - Unsorted/reverse array; maximum comparisons during merge.
• Number of Comparisons: Min ~ (n/2) log_2(n), Max ~ n log_2(n) - 1.
• Recurrence (Worst):    T(n) = 2T(n/2) + (n - 1) = O(n log_2 n).

2. MODIFIED 3-WAY MERGE SORT
• Best-Case Time:        O(n log n) - Recursive decomposition always builds log_3(n) deep tree.
• Average-Case Time:     O(n log n) - Expected performance across random permutations.
• Worst-Case Time:       O(n log n) - Maximum comparisons choosing min among 3 head pointers.
• Number of Comparisons: Min ~ (2n/3) log_3(n), Max ~ 2n log_3(n) - 2.
• Recurrence (Worst):    T(n) = 3T(n/3) + (2n - 2) = O(n log_3 n).

3. K-WAY MERGE SORT (GENERAL CASE)
• Best-Case Time:        O(n log n) - k-ary recursion tree of depth log_k(n).
• Average-Case Time:     O(n log n) - Balanced dividing across k partitions.
• Worst-Case Time:       O(n log n) - O(n log_k n * log_2 k) using a Min-Heap/Priority Queue.
• Comparison Factor:     Using Min-Heap to pick min among k elements takes O(log k) per move.
• Recurrence (Worst):    T(n) = kT(n/k) + O(n log k) = O(n log n).*/

GRAPH
<img width="1620" height="990" alt="17864227018605734709914096934259" src="https://github.com/user-attachments/assets/8e9aab2c-1718-4c8d-8a9f-965535944994" />
<img width="1620" height="990" alt="17864227352086953068719376141651" src="https://github.com/user-attachments/assets/621d984a-0637-4b1b-867f-51ad54ca1757" />
<img width="1620" height="990" alt="17864227576551485962566097851492" src="https://github.com/user-attachments/assets/d398ac3d-4bde-444b-a424-57c569a97917" />
<img width="1620" height="990" alt="17864227753597344982726832778032" src="https://github.com/user-attachments/assets/2f2fa2d3-0457-4ad2-ab93-73965eda4b2f" />

