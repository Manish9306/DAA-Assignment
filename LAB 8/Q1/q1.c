/*
1. [Minimum Coin Change] Given an integer array of coin denominations C = {c1, c2, ..., cn}
representing coins of different values, and an integer target amount V, find the minimum
number of coins needed to make up that amount. You may assume an infinite supply of
each coin denomination. If that amount of money cannot be made up by any combination
of the coins, return -1.

ALGORITHM:
----------
MinCoinChange(C[], n, V):
1. Create array dp[0..V], initialize dp[0] = 0, dp[1..V] = INF
2. For i = 1 to V:
     For j = 0 to n-1:
       If C[j] <= i AND dp[i - C[j]] + 1 < dp[i]:
         dp[i] = dp[i - C[j]] + 1
3. If dp[V] == INF, return -1
4. Else return dp[V]

TIME COMPLEXITY:  O(n * V)  where n = number of coins, V = target amount
SPACE COMPLEXITY: O(V)
*/

#include <stdio.h>
#include <limits.h>

int minCoins(int C[], int n, int V) {
    int dp[V + 1];
    dp[0] = 0;
    for (int i = 1; i <= V; i++)
        dp[i] = INT_MAX;

    for (int i = 1; i <= V; i++)
        for (int j = 0; j < n; j++)
            if (C[j] <= i && dp[i - C[j]] != INT_MAX && dp[i - C[j]] + 1 < dp[i])
                dp[i] = dp[i - C[j]] + 1;

    return dp[V] == INT_MAX ? -1 : dp[V];
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

    int result = minCoins(C, n, V);
    if (result == -1)
        printf("Not possible to make amount %d\n", V);
    else
        printf("Minimum coins needed: %d\n", result);

    return 0;
}
