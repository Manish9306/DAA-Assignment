/*
3. [Longest Common Subsequence (LCS)] Given two sequences X = <x1, x2, ..., xm>
and Y = <y1, y2, ..., yn>, compute the length of their longest common subsequence and
reconstruct the actual subsequence string. By choosing the proper input representation,
write a program in C to validate your algorithm and derive the complexity analysis of your
algorithm.
*/
/*ALGORITHM:
----------
LCS(X, Y, m, n):
1. Create table dp[0..m][0..n], initialize dp[i][0] = 0, dp[0][j] = 0
2. For i = 1 to m:
     For j = 1 to n:
       If X[i-1] == Y[j-1]:
         dp[i][j] = dp[i-1][j-1] + 1
       Else:
         dp[i][j] = max(dp[i-1][j], dp[i][j-1])
3. Length = dp[m][n]

Reconstruct(dp, X, m, n):
1. Start at i = m, j = n, k = dp[m][n] - 1
2. While i > 0 AND j > 0:
     If X[i-1] == Y[j-1]: result[k--] = X[i-1], i--, j--
     Else if dp[i-1][j] > dp[i][j-1]: i--
     Else: j--

TIME COMPLEXITY:  O(m * n)
SPACE COMPLEXITY: O(m * n)
*/

#include <stdio.h>
#include <string.h>

void lcs(char X[], char Y[]) {
    int m = strlen(X), n = strlen(Y);
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) dp[i][0] = 0;
    for (int j = 0; j <= n; j++) dp[0][j] = 0;

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];

    printf("Length of LCS: %d\n", dp[m][n]);

    // Reconstruct
    int len = dp[m][n];
    char result[len + 1];
    result[len] = '\0';
    int i = m, j = n, k = len - 1;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            result[k--] = X[i - 1];
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }
    printf("LCS: %s\n", result);
}

int main() {
    char X[100], Y[100];
    printf("Enter first string: ");
    scanf("%s", X);
    printf("Enter second string: ");
    scanf("%s", Y);

    lcs(X, Y);
    return 0;
}

