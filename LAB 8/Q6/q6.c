/*
6. [Edit Distance with Traceback Information] Given two strings A of length m and B
of length n, compute the minimum number of operations (insertions, deletions, or substi-
tutions) required to transform A into B, and print the traceback result.

ALGORITHM:
----------
EditDistance(A, B, m, n):
1. Create table dp[0..m][0..n]
2. dp[i][0] = i for all i, dp[0][j] = j for all j
3. For i = 1 to m:
     For j = 1 to n:
       If A[i-1] == B[j-1]:
         dp[i][j] = dp[i-1][j-1]
       Else:
         dp[i][j] = 1 + min(dp[i-1][j],      // delete
                            dp[i][j-1],        // insert
                            dp[i-1][j-1])      // substitute
4. Return dp[m][n]

Traceback: From dp[m][n], backtrack to dp[0][0] printing each operation.

TIME COMPLEXITY:  O(m * n)
SPACE COMPLEXITY: O(m * n)
*/

#include <stdio.h>
#include <string.h>

int min3(int a, int b, int c) {
    if (a <= b && a <= c) return a;
    if (b <= c) return b;
    return c;
}

void editDistance(char A[], char B[]) {
    int m = strlen(A), n = strlen(B);
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (A[i - 1] == B[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min3(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);

    printf("Edit Distance: %d\n", dp[m][n]);

    // Traceback
    printf("\nTraceback:\n");
    int i = m, j = n;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1]) {
            printf("  Match '%c'\n", A[i - 1]);
            i--; j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            printf("  Substitute '%c' -> '%c'\n", A[i - 1], B[j - 1]);
            i--; j--;
        } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            printf("  Insert '%c'\n", B[j - 1]);
            j--;
        } else {
            printf("  Delete '%c'\n", A[i - 1]);
            i--;
        }
    }
}

int main() {
    char A[100], B[100];
    printf("Enter first string: ");
    scanf("%s", A);
    printf("Enter second string: ");
    scanf("%s", B);

    editDistance(A, B);
    return 0;
}
