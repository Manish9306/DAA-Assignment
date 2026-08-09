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
