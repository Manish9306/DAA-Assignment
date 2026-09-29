/*
7. [Rod Cutting with Reconstruction] Given a rod of length n inches and an array of
prices P = [p1, p2, ..., pn], where pi denotes the market price of a rod piece of length i
inches, determine:
(i)  The maximum revenue obtainable by cutting up the rod and selling the pieces.
(ii) The exact lengths of the pieces that constitute the optimal decomposition.

ALGORITHM:
----------
RodCut(P[], n):
1. Create arrays dp[0..n] and cut[0..n], dp[0] = 0
2. For i = 1 to n:
     dp[i] = -INF
     For j = 1 to i:
       If P[j-1] + dp[i-j] > dp[i]:
         dp[i] = P[j-1] + dp[i-j]
         cut[i] = j
3. Maximum revenue = dp[n]

Reconstruct: While n > 0: print cut[n], n = n - cut[n]

TIME COMPLEXITY:  O(n^2)
SPACE COMPLEXITY: O(n)
*/

#include <stdio.h>

void rodCut(int P[], int n) {
    int dp[n + 1], cut[n + 1];
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        dp[i] = -1;
        for (int j = 1; j <= i; j++) {
            if (P[j - 1] + dp[i - j] > dp[i]) {
                dp[i] = P[j - 1] + dp[i - j];
                cut[i] = j;
            }
        }
    }

    printf("Maximum Revenue: %d\n", dp[n]);

    // Reconstruct
    printf("Pieces: ");
    int rem = n;
    while (rem > 0) {
        printf("%d ", cut[rem]);
        rem -= cut[rem];
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter rod length: ");
    scanf("%d", &n);
    int P[n];
    printf("Enter prices for lengths 1 to %d: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &P[i]);

    rodCut(P, n);
    return 0;
}
