# Question 2: 2D Square Matrix Operations and Complexities

**Assumption:** The matrix dimension is $n \times n$ (total $n^2$ elements).

*   **(i) Matrix Addition:**
    *   **Algorithm:** Iterate through each row $i$ and column $j$. Compute `C[i][j] = A[i][j] + B[i][j]`.
    *   **Worst-case Complexity:** $O(n^2)$

*   **(ii) Matrix Multiplication:**
    *   **Algorithm:** Standard multiplication uses three nested loops ($i, j, k$ from $0$ to $n-1$), computing the dot product of rows of A and columns of B. 
    *   **Worst-case Complexity:** $O(n^3)$ (Standard approach). *Note: Strassen's algorithm can achieve $O(n^{2.81})$*.

*   **(iii) Zero matrix check:**
    *   **Algorithm:** Iterate through rows and columns. Return `false` immediately if any `A[i][j] != 0`. If the loop finishes, return `true`.
    *   **Worst-case Complexity:** $O(n^2)$

*   **(iv) Symmetric matrix check:**
    *   **Algorithm:** Iterate through the upper triangle of the matrix ($i$ from $0$ to $n-1$, $j$ from $i+1$ to $n-1$). Return `false` immediately if `A[i][j] != A[j][i]`.
    *   **Worst-case Complexity:** $O(n^2)$

*   **(v) Determinant:**
    *   **Algorithm:** Use Gaussian elimination to reduce the matrix to an upper triangular form. The determinant is the product of the diagonal elements.
    *   **Worst-case Complexity:** $O(n^3)$

*   **(vi) Transpose in situ (in place):**
    *   **Algorithm:** Iterate through the upper triangle ($i < j$). Swap `A[i][j]` with `A[j][i]`.
    *   **Worst-case Complexity:** $O(n^2)$

*   **(vii) Eigenvalue and eigenvector:**
    *   **Algorithm:** The standard numerical approach for dense matrices is the QR algorithm, which involves reducing to Hessenberg form, followed by iterative QR factorizations.
    *   **Worst-case Complexity:** $O(n^3)$ per iteration (practically converges in $O(n^3)$ overall).
