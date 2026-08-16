# Special-Pattern Matrix Multiplication using Divide and Conquer ($O(n^2)$)

## 1. Problem Overview

Given two $n \times n$ matrices $A$ and $B$ where $n = 2^k$. Both matrices follow a recursive 2-block circulant/symmetric structure:

$$A = \begin{pmatrix} A_1 & A_2 \\ A_2 & A_1 \end{pmatrix}, \quad B = \begin{pmatrix} B_1 & B_2 \\ B_2 & B_1 \end{pmatrix}$$

Each sub-block $A_1, A_2, B_1, B_2$ recursively exhibits the same pattern down to scalar integers ($1 \times 1$).

---

## 2. Algorithm Description

### `specialMultiply(A, B, C, n)`

1. **Base Case ($n = 1$):**
   - Directly multiply the scalars: $C[0][0] = A[0][0] \times B[0][0]$.
   - Return $C$.

2. **Divide Step:**
   - Divide $A$ into sub-blocks $A_1, A_2$ and $B$ into $B_1, B_2$ of size $\frac{n}{2} \times \frac{n}{2}$.
   - Compute auxiliary matrices using matrix addition and subtraction:
     - $A_{\text{plus}} = A_1 + A_2$
     - $A_{\text{minus}} = A_1 - A_2$
     - $B_{\text{plus}} = B_1 + B_2$
     - $B_{\text{minus}} = B_1 - B_2$

3. **Conquer Step (Only 2 Recursive Multiplications):**
   - $P = \text{specialMultiply}(A_{\text{plus}}, B_{\text{plus}}, \frac{n}{2})$
   - $Q = \text{specialMultiply}(A_{\text{minus}}, B_{\text{minus}}, \frac{n}{2})$

4. **Combine Step:**
   - Calculate output quadrants:
     - $C_1 = \frac{P + Q}{2}$
     - $C_2 = \frac{P - Q}{2}$
   - Construct matrix $C$:
     $$C = \begin{pmatrix} C_1 & C_2 \\ C_2 & C_1 \end{pmatrix}$$

---

## 3. Mathematical Correctness Proof

### Standard Block Multiplication:
$$C = AB = \begin{pmatrix} A_1 & A_2 \\ A_2 & A_1 \end{pmatrix} \begin{pmatrix} B_1 & B_2 \\ B_2 & B_1 \end{pmatrix} = \begin{pmatrix} A_1 B_1 + A_2 B_2 & A_1 B_2 + A_2 B_1 \\ A_2 B_1 + A_1 B_2 & A_2 B_2 + A_1 B_1 \end{pmatrix}$$

Let:
- $C_1 = A_1 B_1 + A_2 B_2$
- $C_2 = A_1 B_2 + A_2 B_1$

### Expanding Algorithm Terms:
- $P = (A_1 + A_2)(B_1 + B_2) = A_1 B_1 + A_1 B_2 + A_2 B_1 + A_2 B_2$
- $Q = (A_1 - A_2)(B_1 - B_2) = A_1 B_1 - A_1 B_2 - A_2 B_1 + A_2 B_2$

### Reconstructing $C_1$ and $C_2$:
$$\frac{P + Q}{2} = \frac{2(A_1 B_1 + A_2 B_2)}{2} = A_1 B_1 + A_2 B_2 = C_1$$
$$\frac{P - Q}{2} = \frac{2(A_1 B_2 + A_2 B_1)}{2} = A_1 B_2 + A_2 B_1 = C_2$$

Because sums and differences of matrices with this special structure also preserve the special structure, the subproblems $P$ and $Q$ can be solved recursively down to $n = 1$.

---

## 4. Complexity Analysis

| Metric | Special D&C Algorithm | Standard Multiplication | Strassen's Algorithm |
| :--- | :--- | :--- | :--- |
| **Time Complexity** | **$\mathcal{O}(n^2)$** | $\mathcal{O}(n^3)$ | $\mathcal{O}(n^{2.807})$ |
| **Scalar Multiplications** | **$n$** | $n^3$ | $n^{2.807}$ |
| **Space Complexity** | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ | $\mathcal{O}(n^2)$ |

---

## 5. Recurrence Derivation

### A. Number of Scalar Multiplications $M(n)$
$$M(n) = 2 M\left(\frac{n}{2}\right), \quad M(1) = 1$$
$$M(n) = 2^{\log_2 n} = n$$

### B. Total Time Complexity $T(n)$
The algorithm makes 2 recursive calls of size $n/2$ and performs $O(n^2)$ matrix additions/subtractions:

$$T(n) = 2 T\left(\frac{n}{2}\right) + \Theta(n^2)$$

Applying the **Master Theorem**:
- $a = 2, \, b = 2, \, f(n) = \Theta(n^2)$
- $\log_b a = \log_2 2 = 1$
- Since $f(n) = \Omega(n^c)$ where $c = 2 > \log_2 2$ (**Case 3**), and the regularity condition $2 f(n/2) \le k f(n)$ holds:

$$T(n) = \Theta(n^2)$$

> **Conclusion:** By leveraging block symmetries to eliminate 6 out of 8 recursive multiplications, the time complexity drops strictly to quadratic $\mathcal{O}(n^2)$.
