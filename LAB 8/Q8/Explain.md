### 8. Optimal Binary Search Trees (OBST)

#### Problem Statement
Given a set of n distinct sorted keys K = <k1, k2, ..., kn> with search probabilities p1, p2, ..., pn, and n + 1 dummy keys d0, d1, ..., dn representing searches not in K with probabilities q0, q1, ..., qn, find the minimum expected search cost of a binary search tree and construct the tree structure.

#### Algorithm
OptimalBST(p[], q[], n):
1. Create tables e[1..n+1][0..n], w[1..n+1][0..n], and root[1..n][1..n]
2. For i = 1 to n + 1:
     e[i][i - 1] = q[i - 1]
     w[i][i - 1] = q[i - 1]
3. For l = 1 to n:                         // Chain length
     For i = 1 to n - l + 1:
       j = i + l - 1
       e[i][j] = INF
       w[i][j] = w[i][j - 1] + p[j] + q[j]
       For r = i to j:                     // Try each root candidate
         cost = e[i][r - 1] + e[r + 1][j] + w[i][j]
         If cost < e[i][j]:
           e[i][j] = cost
           root[i][j] = r
4. Return e[1][n]

#### Complexity Analysis
- Time Complexity: O(n^3) due to three nested loops (length, starting key, root candidate).
- Space Complexity: O(n^2) for the dynamic programming matrices.

