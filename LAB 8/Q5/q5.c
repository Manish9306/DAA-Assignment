/*
5. [Maximum Sum Increasing Subsequence] Given an array of n positive integers A =
[a0, a1, ..., an-1], find the maximum possible sum of a strictly increasing subsequence.

ALGORITHM:
----------
MSIS(A[], n):
1. Create array dp[0..n-1], initialize dp[i] = A[i] for all i
2. For i = 1 to n-1:
     For j = 0 to i-1:
       If A[j] < A[i] AND dp[j] + A[i] > dp[i]:
         dp[i] = dp[j] + A[i]
3. Return max(dp[0..n-1])

TIME COMPLEXITY:  O(n^2)
SPACE COMPLEXITY: O(n)
*/

#include <stdio.h>

int msis(int A[], int n) {
    int dp[n];
    for (int i = 0; i < n; i++)
        dp[i] = A[i];

    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (A[j] < A[i] && dp[j] + A[i] > dp[i])
                dp[i] = dp[j] + A[i];

    int max = dp[0];
    for (int i = 1; i < n; i++)
        if (dp[i] > max)
            max = dp[i];

    return max;
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int A[n];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("Maximum Sum Increasing Subsequence: %d\n", msis(A, n));
    return 0;
}
