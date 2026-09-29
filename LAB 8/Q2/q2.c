/*
2. [Coin Change: Total number of ways] Given an array of distinct positive integers rep-
resenting coin denominations C = {c1, c2, ..., cn} and a target amount V, find the total
number of distinct combinations of coins that sum up to V. You may assume an infinite
supply of each coin denomination. The order of coins does not matter (e.g., 1 + 2 and
2 + 1 are considered the same combination).

ALGORITHM:
----------
CoinChangeWays(C[], n, V):
1. Create array dp[0..V], initialize dp[0] = 1, dp[1..V] = 0
2. For i = 0 to n-1:            // iterate over each coin
     For j = C[i] to V:         // iterate over amounts
       dp[j] = dp[j] + dp[j - C[i]]
3. Return dp[V]

Note: Outer loop over coins ensures combinations (not permutations) are counted.

TIME COMPLEXITY:  O(n * V)  where n = number of coins, V = target amount
SPACE COMPLEXITY: O(V)
*/

#include <stdio.h>

int countWays(int C[], int n, int V) {
    int dp[V + 1];
    dp[0] = 1;
    for (int i = 1; i <= V; i++)
        dp[i] = 0;

    for (int i = 0; i < n; i++)
        for (int j = C[i]; j <= V; j++)
            dp[j] += dp[j - C[i]];

    return dp[V];
}

int main() {
    int n, V;
    printf("Enter number of coin denominations: ");
    scanf("%d", &n);
    int C[n];
    printf("Enter coin denominations: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &C[i]);
    printf("Enter target amount V: ");
    scanf("%d", &V);

    int result = countWays(C, n, V);
    printf("Total number of ways: %d\n", result);

    return 0;
}
