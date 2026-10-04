### 1. Minimum Coin Change

#### Problem Statement
Given an integer array of coin denominations $C = \{c_1, c_2, \dots, c_n\}$ representing coins of different values and an integer target amount $V$, find the minimum number of coins needed to make up that amount. Assume an infinite supply of each coin denomination. If the amount cannot be made up, return -1.

#### Algorithm
```text
MinCoinChange(C[], n, V):
1. Create array dp[0..V]
2. Initialize dp[0] = 0, dp[1..V] = INF
3. For i = 1 to V:
     For j = 0 to n - 1:
       If C[j] <= i AND dp[i - C[j]] != INF AND dp[i - C[j]] + 1 < dp[i]:
         dp[i] = dp[i - C[j]] + 1
4. If dp[V] == INF:
     Return -1
   Else:
     Return dp[V]
