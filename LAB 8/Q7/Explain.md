### 7. Rod Cutting with Reconstruction

#### Problem Statement
Given a rod of length n inches and an array of prices P = [p1, p2, ..., pn], where pi denotes the market price of a rod piece of length i inches, determine:
(i)  The maximum revenue obtainable by cutting up the rod and selling the pieces.
(ii) The exact lengths of the pieces that constitute the optimal decomposition.

#### Algorithm
RodCut(P[], n):
1. Create arrays dp[0..n] and cut[0..n]
2. Initialize dp[0] = 0
3. For i = 1 to n:
     dp[i] = -INF
     For j = 1 to i:
       If P[j - 1] + dp[i - j] > dp[i]:
         dp[i] = P[j - 1] + dp[i - j]
         cut[i] = j
4. Maximum revenue = dp[n]

Reconstruct(cut[], n):
1. While n > 0:
     Print cut[n]
     n = n - cut[n]

#### Complexity Analysis
- Time Complexity: O(n^2) for evaluating cuts for all sub-lengths.
- Space Complexity: O(n) for dp and cut arrays.
