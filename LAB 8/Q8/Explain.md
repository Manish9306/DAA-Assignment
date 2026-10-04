/*ALGORITHM:
----------
OptimalBST(p[], q[], n):
1. Create tables e[1..n+1][0..n], w[1..n+1][0..n], root[1..n][1..n]
2. For i = 1 to n+1: e[i][i-1] = q[i-1], w[i][i-1] = q[i-1]
3. For l = 1 to n:              // chain length
     For i = 1 to n-l+1:
       j = i + l - 1
       e[i][j] = INF
       w[i][j] = w[i][j-1] + p[j] + q[j]
       For r = i to j:          // try each root
         cost = e[i][r-1] + e[r+1][j] + w[i][j]
         If cost < e[i][j]:
           e[i][j] = cost
           root[i][j] = r
4. Return e[1][n]

TIME COMPLEXITY:  O(n^3)
SPACE COMPLEXITY: O(n^2)
*/

