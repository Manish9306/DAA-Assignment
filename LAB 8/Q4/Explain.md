
### 4. Longest Increasing Subsequence (LIS)

#### Problem Statement
Given an integer array A = [a0, a1, ..., an-1], find the length of the longest subsequence such that all elements of the subsequence are strictly increasing.

#### Algorithm
LIS(A[], n):
1. Create array dp[0..n-1]
2. Initialize dp[i] = 1 for all 0 <= i < n
3. For i = 1 to n - 1:
     For j = 0 to i - 1:
       If A[j] < A[i] AND dp[j] + 1 > dp[i]:
         dp[i] = dp[j] + 1
4. Return max(dp[0..n-1])

#### Complexity Analysis
- Time Complexity: O(n^2) due to nested loops comparing pairs of elements.
- Space Complexity: O(n) for the 1D DP array.
