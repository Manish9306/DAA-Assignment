

### Question 2: Coin Change (Total Number of Ways)

```markdown
### 2. Coin Change: Total Number of Ways

#### Problem Statement
Given an array of distinct positive integers representing coin denominations $C = \{c_1, c_2, \dots, c_n\}$ and a target amount $V$, find the total number of distinct combinations of coins that sum up to $V$. Assume an infinite supply of each coin denomination. Order of coins does not matter.

#### Algorithm
```text
CoinChangeWays(C[], n, V):
1. Create array dp[0..V]
2. Initialize dp[0] = 1, dp[1..V] = 0
3. For i = 0 to n - 1:            // Iterate over coins
     For j = C[i] to V:           // Iterate over amounts
       dp[j] = dp[j] + dp[j - C[i]]
4. Return dp[V]
