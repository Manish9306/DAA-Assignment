/*
4. [Longest Increasing Subsequence] Given an integer array A = [a0, a1, ..., an-1], find
the length of the longest subsequence such that all elements of the subsequence are strictly
increasing.

ALGORITHM:
----------
LIS(A[], n):
1. Create array dp[0..n-1], initialize dp[i] = 1 for all i
2. For i = 1 to n-1:
     For j = 0 to i-1:
       If A[j] < A[i] AND dp[j] + 1 > dp[i]:
         dp[i] = dp[j] + 1
3. Return max(dp[0..n-1])

TIME COMPLEXITY:  O(n^2)
SPACE COMPLEXITY: O(n)
*/

#include <stdio.h>

int lis(int A[], int n) {
    int dp[n];
    for (int i = 0; i < n; i++)
        dp[i] = 1;

    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (A[j] < A[i] && dp[j] + 1 > dp[i])
                dp[i] = dp[j] + 1;

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

    printf("Length of LIS: %d\n", lis(A, n));
    return 0;
}
