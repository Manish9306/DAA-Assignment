
### 6. Edit Distance with Traceback Information

#### Problem Statement
Given two strings A of length m and B of length n, compute the minimum number of edit operations (insertions, deletions, substitutions) required to transform A into B, and print the traceback result.

#### Algorithm
EditDistance(A, B, m, n):
1. Create 2D table dp[0..m][0..n]
2. For i = 0 to m: dp[i][0] = i
3. For j = 0 to n: dp[0][j] = j
4. For i = 1 to m:
     For j = 1 to n:
       If A[i - 1] == B[j - 1]:
         dp[i][j] = dp[i - 1][j - 1]
       Else:
         dp[i][j] = 1 + min(dp[i - 1][j],       // Deletion
                            dp[i][j - 1],       // Insertion
                            dp[i - 1][j - 1])   // Substitution
5. Return dp[m][n]

Traceback(dp, A, B, m, n):
1. Set i = m, j = n
2. While i > 0 OR j > 0:
     If i > 0 AND j > 0 AND A[i - 1] == B[j - 1]:
       Print "Match", i = i - 1, j = j - 1
     Else if i > 0 AND j > 0 AND dp[i][j] == dp[i - 1][j - 1] + 1:
       Print "Substitute", i = i - 1, j = j - 1
     Else if j > 0 AND dp[i][j] == dp[i][j - 1] + 1:
       Print "Insert", j = j - 1
     Else:
       Print "Delete", i = i - 1

#### Complexity Analysis
- Time Complexity: O(m * n) to fill the DP table and O(m + n) for traceback.
- Space Complexity: O(m * n) for the 2D DP matrix.
