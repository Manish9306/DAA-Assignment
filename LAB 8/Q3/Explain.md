### 3. Longest Common Subsequence (LCS)

#### Problem Statement
Given two sequences X = <x1, x2, ..., xm> and Y = <y1, y2, ..., yn>, compute the length of their longest common subsequence and reconstruct the actual subsequence string.

#### Algorithm
LCS(X, Y, m, n):
1. Create 2D table dp[0..m][0..n]
2. Initialize dp[i][0] = 0 for all 0 <= i <= m
3. Initialize dp[0][j] = 0 for all 0 <= j <= n
4. For i = 1 to m:
     For j = 1 to n:
       If X[i - 1] == Y[j - 1]:
         dp[i][j] = dp[i - 1][j - 1] + 1
       Else:
         dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
5. Length = dp[m][n]

Reconstruct(dp, X, m, n):
1. Set i = m, j = n, k = dp[m][n] - 1
2. While i > 0 AND j > 0:
     If X[i - 1] == Y[j - 1]:
       result[k] = X[i - 1]
       k = k - 1
       i = i - 1
       j = j - 1
     Else if dp[i - 1][j] > dp[i][j - 1]:
       i = i - 1
     Else:
       j = j - 1
3. Return result

#### Complexity Analysis
- Time Complexity: O(m * n) to compute the DP table and O(m + n) for reconstruction.
- Space Complexity: O(m * n) to store the DP table.
