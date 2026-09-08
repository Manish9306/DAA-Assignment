**Question 7: Matrix Chain Multiplication (MCM)**

**Algorithm**:
* Define subproblems where m[i][j] is the minimum scalar multiplications needed for matrices A_i to A_j[cite: 7].
* Set the base case m[i][i] = 0 for all matrices[cite: 7].
* Use the recurrence step for chain lengths L = 2 to n: m[i][j] = min_{i <= k < j} { m[i][k] + m[k+1][j] + p_{i-1} * p_k * p_j }[cite: 7].
* Store the optimal split index 'k' in a table s[i][j] and use it to recursively reconstruct the optimal parenthesization[cite: 7].

**Time Complexity**: 
* O(n^3)[cite: 7].
