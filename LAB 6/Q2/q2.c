/*
================================================================================
Design and Analysis of Algorithm (DAA), Lab-06
Question 2: 2D Square Matrix Operations and Complexity Analysis
================================================================================

QUESTION:
2. 2D square matrix operations and their complexities: Given square matrices with
n rows and n columns, what is the worst-case computational complexity of the following
matrix algorithms in terms of n:
(i) Matrix Addition.
(ii) Matrix Multiplication.
(iii) Finding if the given matrix is a zero matrix.
(iv) Finding if the given matrix is a symmetric matrix.
(v) Computing the determinant of the given matrix.
(vi) Transposing the matrix in situ (in place).
(vii) Finding the eigenvalue and eigenvector of the matrix.

By choosing the proper input representation, write a program in C to validate your procedures
and derive the corresponding complexity analysis.

--------------------------------------------------------------------------------
WORST-CASE COMPUTATIONAL COMPLEXITY SUMMARY:
--------------------------------------------------------------------------------
Operation                                 | Worst-Case Time | Aux. Space | Method / Algorithm
------------------------------------------+-----------------+------------+---------------------------------------
(i)   Matrix Addition                     | O(n^2)          | O(1) / O(n^2)| Element-wise C[i][j] = A[i][j] + B[i][j]
(ii)  Matrix Multiplication               | O(n^3)          | O(1) / O(n^2)| Standard triple-loop definition
                                          | (O(n^2.807) by Strassen's algorithm)
(iii) Zero Matrix Test                    | O(n^2)          | O(1)       | Check all n^2 elements (early exit if non-zero)
(iv)  Symmetric Matrix Test               | O(n^2)          | O(1)       | Compare A[i][j] == A[j][i] for i < j (n(n-1)/2 comp.)
(v)   Determinant Calculation             | O(n^3)          | O(n^2)     | Gaussian Elimination with partial pivoting
                                          | (Laplace expansion is O(n!), impractical for n > 10)
(vi)  In-place Transpose (in situ)        | O(n^2)          | O(1)       | Swap A[i][j] and A[j][i] for 0 <= i < j < n
(vii) Eigenvalue & Eigenvector            | O(k * n^2)      | O(n)       | Power Iteration Method (dominant eigenpair)
                                          | (QR Algorithm finds all eigenvalues in O(n^3) per iteration)
================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9
#define MAX_ITER 1000

// Utility to allocate a 2D square matrix dynamically
double **allocate_matrix(int n) {
    double **mat = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        mat[i] = (double *)malloc(n * sizeof(double));
    }
    return mat;
}

// Utility to free dynamic 2D matrix
void free_matrix(double **mat, int n) {
    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}

// Utility to copy matrix
double **copy_matrix(double **src, int n) {
    double **dest = allocate_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dest[i][j] = src[i][j];
        }
    }
    return dest;
}

// Utility to print a 2D matrix
void print_matrix(double **mat, int n, const char *name) {
    printf("%s (%dx%d):\n", name, n, n);
    for (int i = 0; i < n; i++) {
        printf("  [ ");
        for (int j = 0; j < n; j++) {
            printf("%8.3f ", mat[i][j]);
        }
        printf("]\n");
    }
    printf("\n");
}

/*
--------------------------------------------------------------------------------
(i) Matrix Addition
Algorithm:
  - For i = 0 to n-1 and j = 0 to n-1: C[i][j] = A[i][j] + B[i][j].
Worst-Case Time Complexity: O(n^2) -> Exactly n^2 additions.
Auxiliary Space Complexity: O(n^2) to store the result matrix C (or O(1) if adding into A).
--------------------------------------------------------------------------------
*/
double **matrix_addition(double **A, double **B, int n) {
    double **C = allocate_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

/*
--------------------------------------------------------------------------------
(ii) Matrix Multiplication
Algorithm:
  - Standard matrix multiplication: C[i][j] = sum_{k=0}^{n-1} (A[i][k] * B[k][j]).
Worst-Case Time Complexity: O(n^3) -> n^3 multiplications and n^2(n-1) additions.
  (Note: Strassen's algorithm achieves O(n^(log2 7)) = O(n^2.807)).
Auxiliary Space Complexity: O(n^2) to store the product matrix.
--------------------------------------------------------------------------------
*/
double **matrix_multiplication(double **A, double **B, int n) {
    double **C = allocate_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

/*
--------------------------------------------------------------------------------
(iii) Finding if the Matrix is a Zero Matrix
Algorithm:
  - Iterate through all n * n elements.
  - If any element |A[i][j]| > EPSILON, immediately return false.
Worst-Case Time Complexity: O(n^2) -> Occurs when matrix is zero or last element checked is non-zero.
Auxiliary Space Complexity: O(1).
--------------------------------------------------------------------------------
*/
int is_zero_matrix(double **A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fabs(A[i][j]) > EPSILON) {
                return 0; // Not a zero matrix
            }
        }
    }
    return 1; // Zero matrix
}

/*
--------------------------------------------------------------------------------
(iv) Finding if the Matrix is Symmetric
Algorithm:
  - A matrix is symmetric if A[i][j] == A[j][i] for all 0 <= i < j < n.
  - Iterate over the upper triangle and compare with transposed elements.
Worst-Case Time Complexity: O(n^2) -> Exactly n(n - 1)/2 comparisons.
Auxiliary Space Complexity: O(1).
--------------------------------------------------------------------------------
*/
int is_symmetric_matrix(double **A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (fabs(A[i][j] - A[j][i]) > EPSILON) {
                return 0; // Not symmetric
            }
        }
    }
    return 1; // Symmetric
}

/*
--------------------------------------------------------------------------------
(v) Computing the Determinant
Algorithm: Gaussian Elimination with Partial Pivoting
  - Convert matrix to Upper Triangular Matrix using row operations.
  - For each pivot column k:
      1. Find max element in column k (from row k to n-1) for numerical stability.
      2. Swap rows if needed (inverts determinant sign: det *= -1).
      3. If pivot is 0 (det == 0), return 0.
      4. Eliminate elements below pivot: Row[i] = Row[i] - factor * Row[k].
  - Determinant = product of diagonal elements * sign.
Worst-Case Time Complexity: O(n^3) -> n steps of elimination, each doing O(n^2) arithmetic.
  (In contrast, Laplace cofactor expansion is O(n!), which is computationally intractable).
Auxiliary Space Complexity: O(n^2) for the working copy of matrix (O(1) if mutated in-place).
--------------------------------------------------------------------------------
*/
double compute_determinant(double **mat, int n) {
    double **A = copy_matrix(mat, n);
    double det = 1.0;

    for (int i = 0; i < n; i++) {
        // Partial pivoting
        int pivot_row = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(A[k][i]) > fabs(A[pivot_row][i])) {
                pivot_row = k;
            }
        }

        if (fabs(A[pivot_row][i]) < EPSILON) {
            free_matrix(A, n);
            return 0.0; // Singular matrix
        }

        if (pivot_row != i) {
            // Swap row i and pivot_row
            double *temp = A[i];
            A[i] = A[pivot_row];
            A[pivot_row] = temp;
            det = -det; // Row swap flips sign
        }

        det *= A[i][i];

        // Eliminate column i below diagonal
        for (int j = i + 1; j < n; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i + 1; k < n; k++) {
                A[j][k] -= factor * A[i][k];
            }
        }
    }

    free_matrix(A, n);
    return det;
}

/*
--------------------------------------------------------------------------------
(vi) Transposing the Matrix in situ (in-place)
Algorithm:
  - Swap A[i][j] and A[j][i] for all 0 <= i < j < n.
Worst-Case Time Complexity: O(n^2) -> Exactly n(n - 1)/2 swaps.
Auxiliary Space Complexity: O(1) in-place auxiliary space.
--------------------------------------------------------------------------------
*/
void transpose_in_situ(double **A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

/*
--------------------------------------------------------------------------------
(vii) Finding Eigenvalue and Eigenvector (Power Iteration Method)
Algorithm:
  - Finds the dominant eigenvalue (largest in magnitude) and corresponding eigenvector.
  - Start with initial random/unit vector v_0.
  - Iteratively compute:
      1. w = A * v
      2. lambda = Rayleigh Quotient: (v^T * A * v) / (v^T * v)
      3. v = w / ||w||_2
      4. Repeat until |lambda_new - lambda_old| < EPSILON or max iterations reached.
Worst-Case Time Complexity: O(k * n^2), where k is number of iterations, each doing
  matrix-vector multiplication in O(n^2).
  (Note: Full spectrum algorithms like QR Algorithm take O(n^3) per iteration to find all eigenvalues).
Auxiliary Space Complexity: O(n) for vector storage.
--------------------------------------------------------------------------------
*/
double power_iteration_eigen(double **A, int n, double *eigenvector) {
    double *v = (double *)malloc(n * sizeof(double));
    double *w = (double *)malloc(n * sizeof(double));

    // Initialize unit vector
    for (int i = 0; i < n; i++) v[i] = 1.0 / sqrt(n);

    double lambda = 0.0;

    for (int iter = 0; iter < MAX_ITER; iter++) {
        // Compute w = A * v (O(n^2))
        for (int i = 0; i < n; i++) {
            w[i] = 0.0;
            for (int j = 0; j < n; j++) {
                w[i] += A[i][j] * v[j];
            }
        }

        // Rayleigh Quotient lambda = (v^T * w) / (v^T * v)
        double numerator = 0.0;
        double denominator = 0.0;
        for (int i = 0; i < n; i++) {
            numerator += v[i] * w[i];
            denominator += v[i] * v[i];
        }
        double new_lambda = numerator / denominator;

        // Compute norm of w
        double norm = 0.0;
        for (int i = 0; i < n; i++) norm += w[i] * w[i];
        norm = sqrt(norm);

        if (norm < EPSILON) break;

        // Update v = w / norm
        for (int i = 0; i < n; i++) v[i] = w[i] / norm;

        // Check convergence
        if (fabs(new_lambda - lambda) < EPSILON) {
            lambda = new_lambda;
            break;
        }
        lambda = new_lambda;
    }

    for (int i = 0; i < n; i++) {
        eigenvector[i] = v[i];
    }

    free(v);
    free(w);
    return lambda;
}

/*
--------------------------------------------------------------------------------
Main Driver Program
--------------------------------------------------------------------------------
*/
int main() {
    printf("==================================================================\n");
    printf("        DAA Lab 06 - Question 2: 2D Matrix Operations & Complexities\n");
    printf("==================================================================\n\n");

    int n = 3;

    // Allocate test matrices
    double **A = allocate_matrix(n);
    double **B = allocate_matrix(n);

    // Initialize Matrix A (Symmetric positive definite matrix)
    // [ 4, 1, 2 ]
    // [ 1, 5, 3 ]
    // [ 2, 3, 6 ]
    double valA[3][3] = {
        {4.0, 1.0, 2.0},
        {1.0, 5.0, 3.0},
        {2.0, 3.0, 6.0}
    };
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = valA[i][j];

    // Initialize Matrix B
    double valB[3][3] = {
        {1.0, 0.0, 2.0},
        {0.0, 3.0, 1.0},
        {4.0, 1.0, 2.0}
    };
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = valB[i][j];

    print_matrix(A, n, "Input Matrix A");
    print_matrix(B, n, "Input Matrix B");

    // (i) Matrix Addition
    double **C_add = matrix_addition(A, B, n);
    print_matrix(C_add, n, "(i) Matrix Addition (A + B) [Complexity: O(n^2) time]");
    free_matrix(C_add, n);

    // (ii) Matrix Multiplication
    double **C_mult = matrix_multiplication(A, B, n);
    print_matrix(C_mult, n, "(ii) Matrix Multiplication (A * B) [Complexity: O(n^3) time]");
    free_matrix(C_mult, n);

    // (iii) Zero Matrix Test
    double **Z = allocate_matrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Z[i][j] = 0.0;

    printf("(iii) Checking if Matrix A is Zero Matrix: %s\n", is_zero_matrix(A, n) ? "YES" : "NO");
    printf("      Checking if Matrix Z is Zero Matrix: %s\n", is_zero_matrix(Z, n) ? "YES" : "NO");
    printf("      [Complexity: O(n^2) time, O(1) space]\n\n");
    free_matrix(Z, n);

    // (iv) Symmetric Matrix Test
    printf("(iv)  Checking if Matrix A is Symmetric: %s\n", is_symmetric_matrix(A, n) ? "YES" : "NO");
    printf("      Checking if Matrix B is Symmetric: %s\n", is_symmetric_matrix(B, n) ? "YES" : "NO");
    printf("      [Complexity: O(n^2) time, O(1) space]\n\n");

    // (v) Determinant of Matrix A and Matrix B
    double detA = compute_determinant(A, n);
    double detB = compute_determinant(B, n);
    printf("(v)   Determinant of Matrix A: %.4f\n", detA);
    printf("      Determinant of Matrix B: %.4f\n", detB);
    printf("      [Complexity: O(n^3) time via Gaussian Elimination, O(1) aux space]\n\n");

    // (vi) Transposing Matrix B in situ (in-place)
    double **B_copy = copy_matrix(B, n);
    print_matrix(B_copy, n, "Original Matrix B before In-Situ Transpose");
    transpose_in_situ(B_copy, n);
    print_matrix(B_copy, n, "(vi) Matrix B after In-Situ Transpose [Complexity: O(n^2) time, O(1) space]");
    free_matrix(B_copy, n);

    // (vii) Dominant Eigenvalue and Eigenvector of Matrix A
    double *eigenvector = (double *)malloc(n * sizeof(double));
    double dominant_eigenval = power_iteration_eigen(A, n, eigenvector);
    printf("(vii) Dominant Eigenvalue of Matrix A: %.6f\n", dominant_eigenval);
    printf("      Corresponding Eigenvector: [ ");
    for (int i = 0; i < n; i++) printf("%.6f ", eigenvector[i]);
    printf("]\n");
    printf("      [Complexity: O(k * n^2) time via Power Iteration Method]\n\n");

    free(eigenvector);
    free_matrix(A, n);
    free_matrix(B, n);

    printf("==================================================================\n");
    printf("                     End of Validation\n");
    printf("==================================================================\n");
    return 0;
}
