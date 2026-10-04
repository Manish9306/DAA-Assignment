### 5. Maximum Sum Increasing Subsequence (MSIS)

#### Problem Statement
Given an array of n positive integers A = [a0, a1, ..., an-1], find the maximum possible sum of a strictly increasing subsequence.

#### Algorithm
MSIS(A[], n):
1. Create array dp[0..n-1]
2. Initialize dp[i] = A[i] for all 0 <= i < n
3. For i = 1 to n - 1:
     For j = 0 to i - 1:
       If A[j] < A[i] AND dp[j] + A[i] > dp[i]:
         dp[i] = dp[j] + A[i]
4. Return max(dp[0..n-1])

#### Complexity Analysis
- Time Complexity: O(n^2) due to the nested loop scanning prior elements.
- Space Complexity: O(n) for the DP array.
