# Strassen's Matrix Multiplication (Divide and Conquer)

## 1. Algorithm Description

### `strassen(A, B, C, n)`
A divide-and-conquer algorithm for multiplying two $n \times n$ matrices that reduces the number of recursive block multiplications from 8 (standard divide-and-conquer) to 7 by utilizing matrix additions and subtractions.

1. **Base Case:**
   - If $n = 1$:
     - $C[0][0] = A[0][0] \times B[0][0]$
     - Increment multiplication count and return.

2. **Divide Step:**
   - Partition matrices $A$ and $B$ of size $n \times n$ into four submatrices of size $\frac{n}{2} \times \frac{n}{2}$:
     $$A = \begin{pmatrix} A_{11} & A_{12} \\ A_{21} & A_{22} \end{pmatrix}, \quad B = \begin{pmatrix} B_{11} & B_{12} \\ B_{21} & B_{22} \end{pmatrix}$$

3. **Compute 7 Strassen Products (Conquer Step):**
   - $M_1 = (A_{11} + A_{22})(B_{11} + B_{22})$
   - $M_2 = (A_{21} + A_{22}) B_{11}$
   - $M_3 = A_{11} (B_{12} - B_{22})$
   - $M_4 = A_{22} (B_{21} - B_{11})$
   - $M_5 = (A_{11} + A_{12}) B_{22}$
   - $M_6 = (A_{21} - A_{11})(B_{11} + B_{12})$
   - $M_7 = (A_{12} - A_{22})(B_{21} + B_{22})$

   *(Requires 10 block additions/subtractions to prepare inputs for recursive calls).*

4. **Combine Step (Calculate Quadrants of Matrix $C$):**
   - $C_{11} = M_1 + M_4 - M_5 + M_7$
   - $C_{12} = M_3 + M_5$
   - $C_{21} = M_2 + M_4$
   - $C_{22} = M_1 - M_2 + M_3 + M_6$

   *(Requires 8 block additions/subtractions to combine products into output quadrants).*

---

## 2. Complexity Analysis

| Metric | Strassen's Algorithm | Standard Matrix Multiplication |
| :--- | :--- | :--- |
| **Time Complexity (All Cases)** | $\mathcal{O}(n^{\log_2 7}) \approx \mathcal{O}(n^{2.807})$ | $\mathcal{O}(n^3)$ |
| **Space Complexity** | $\mathcal{O}(n^2)$ (dynamic memory) / $\mathcal{O}(\log n)$ stack | $\mathcal{O}(1)$ auxiliary (in-place) |
| **Scalar Multiplications** | $n^{\log_2 7} \approx n^{2.807}$ | $n^3$ |
| **Scalar Additions / Subtractions** | $\approx 6 \cdot n^{\log_2 7} - 6 \cdot n^2$ | $n^3 - n^2$ |

---

## 3. Mathematical Recurrence Relation

### A. Scalar Multiplications Count
$$M(n) = 7 M\left(\frac{n}{2}\right), \quad M(1) = 1$$
$$M(n) = 7^{\log_2 n} = n^{\log_2 7} \approx n^{2.8074}$$

### B. Total Time Complexity (Operations Count)
The algorithm performs 7 recursive multiplications of size $n/2$ and 18 matrix additions/subtractions of size $n/2 \times n/2$ (each costing $\Theta(n^2)$ time):

$$T(n) = 7 T\left(\frac{n}{2}\right) + \Theta(n^2)$$

Applying the **Master Theorem**:
- $a = 7, \, b = 2, \, f(n) = \Theta(n^2)$
- Critical exponent: $\log_b a = \log_2 7 \approx 2.807$
- Since $f(n) = \mathcal{O}(n^c)$ where $c = 2 < \log_2 7$ (**Case 1**):

$$T(n) = \Theta\left(n^{\log_2 7}\right) \approx \Theta\left(n^{2.807}\right)$$

> **Takeaway:** By replacing 1 matrix multiplication with 10 extra additions at each level, Strassen's algorithm reduces the asymptotic growth rate below the cubic $\mathcal{O}(n^3)$ barrier of traditional matrix multiplication.
