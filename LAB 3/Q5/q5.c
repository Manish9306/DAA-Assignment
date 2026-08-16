/*Q5.Multiply special-pattern square matrices using D&C approach: Two n×nmatrices are provided to you, where n = 2k for
some natural number k. Each matrix has the recursive structure described as: when divided into four equal-sized 
blocks, two diagonal blocks areidentical, and two off-diagonal blocks are identical, i.e. the structure of the 
matrices would be: M= M1 M2 M2 M1 . Each block has a recursive structure that goes down to single integer elements. 
Give a divide-and-conquer approach-based O(n2) algorithm for multiplying two such matrices and validate the 
complexity of your algorithm.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

long long multiplication_count = 0;
long long addition_count = 0;

/* Allocate an n x n matrix */
int **allocateMatrix(int n)
{
    int **matrix = (int **)malloc(n * sizeof(int *));
    if (matrix == NULL)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        matrix[i] = (int *)malloc(n * sizeof(int));
        if (matrix[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(matrix[j]);
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

/* Free an n x n matrix */
void freeMatrix(int **matrix, int n)
{
    if (matrix == NULL) return;
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

/* 
   Recursively generate matrices satisfying the special pattern:
   M = [ M1  M2 ]
       [ M2  M1 ]
   down to 1x1 base scalars.
*/
void generateSpecialMatrix(int **M, int n)
{
    if (n == 1)
    {
        M[0][0] = (rand() % 9) + 1; // values 1-9 to avoid overflow and 0s
        return;
    }

    int m = n / 2;
    int **M1 = allocateMatrix(m);
    int **M2 = allocateMatrix(m);

    generateSpecialMatrix(M1, m);
    generateSpecialMatrix(M2, m);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            M[i][j]         = M1[i][j];     // Top-Left
            M[i][j + m]     = M2[i][j];     // Top-Right
            M[i + m][j]     = M2[i][j];     // Bottom-Left
            M[i + m][j + m] = M1[i][j];     // Bottom-Right
        }
    }

    freeMatrix(M1, m);
    freeMatrix(M2, m);
}

/* Matrix addition */
void addMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
            addition_count++;
        }
    }
}

/* Matrix subtraction */
void subtractMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
            addition_count++;
        }
    }
}

/* 
   Special-pattern matrix multiplication:
   Given:
   A = [ A1  A2 ],  B = [ B1  B2 ]
       [ A2  A1 ]       [ B2  B1 ]
   
   P = (A1 + A2)(B1 + B2)
   Q = (A1 - A2)(B1 - B2)

   C1 = (P + Q) / 2
   C2 = (P - Q) / 2

   C = [ C1  C2 ]
       [ C2  C1 ]
*/
void specialMultiply(int **A, int **B, int **C, int n)
{
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        multiplication_count++;
        return;
    }

    int m = n / 2;

    int **A1 = allocateMatrix(m);
    int **A2 = allocateMatrix(m);
    int **B1 = allocateMatrix(m);
    int **B2 = allocateMatrix(m);

    int **Aplus  = allocateMatrix(m);
    int **Aminus = allocateMatrix(m);
    int **Bplus  = allocateMatrix(m);
    int **Bminus = allocateMatrix(m);

    int **P = allocateMatrix(m);
    int **Q = allocateMatrix(m);

    /* Extract top-left and top-right blocks */
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + m];

            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + m];
        }
    }

    /* Compute additions and subtractions */
    addMatrix(A1, A2, Aplus, m);
    subtractMatrix(A1, A2, Aminus, m);
    addMatrix(B1, B2, Bplus, m);
    subtractMatrix(B1, B2, Bminus, m);

    /* Only 2 recursive multiplications instead of 8 */
    specialMultiply(Aplus, Bplus, P, m);
    specialMultiply(Aminus, Bminus, Q, m);

    /* Reconstruct result matrix C */
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int c1 = (P[i][j] + Q[i][j]) / 2;
            int c2 = (P[i][j] - Q[i][j]) / 2;

            addition_count += 2;

            C[i][j]         = c1;
            C[i][j + m]     = c2;
            C[i + m][j]     = c2;
            C[i + m][j + m] = c1;
        }
    }

    /* Free intermediate memory */
    freeMatrix(A1, m);
    freeMatrix(A2, m);
    freeMatrix(B1, m);
    freeMatrix(B2, m);
    freeMatrix(Aplus, m);
    freeMatrix(Aminus, m);
    freeMatrix(Bplus, m);
    freeMatrix(Bminus, m);
    freeMatrix(P, m);
    freeMatrix(Q, m);
}

/* Standard O(n^3) matrix multiplication for verification */
void standardMultiply(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/* Compare two matrices for exact match */
int verifyMatch(int **C_special, int **C_std, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (C_special[i][j] != C_std[i][j])
                return 0; // Mismatch
        }
    }
    return 1; // Match
}

int main()
{
    FILE *fp;
    int sizes[] = {2, 4, 8, 16, 32, 64, 128};
    int numberOfSizes = sizeof(sizes) / sizeof(sizes[0]);

    fp = fopen("special_matrix_data.csv", "w");
    if (fp == NULL)
    {
        printf("Error opening CSV file.\n");
        return 1;
    }

    fprintf(fp, "n,multiplications,additions,total_operations,n_squared\n");
    srand((unsigned int)time(NULL));

    printf("\nSpecial-Pattern Matrix Multiplication: D&C O(n^2)\n");
    printf("%6s %15s %15s %18s %12s\n",
           "n", "Multiplications", "Additions", "Total Ops", "Verified?");

    for (int s = 0; s < numberOfSizes; s++)
    {
        int n = sizes[s];

        int **A = allocateMatrix(n);
        int **B = allocateMatrix(n);
        int **C_special = allocateMatrix(n);
        int **C_std = allocateMatrix(n);

        /* Generate recursively structured matrices */
        generateSpecialMatrix(A, n);
        generateSpecialMatrix(B, n);

        multiplication_count = 0;
        addition_count = 0;

        /* Execute D&C O(n^2) Algorithm */
        specialMultiply(A, B, C_special, n);

        long long total_operations = multiplication_count + addition_count;
        long long n_squared = (long long)n * n;

        /* Verification against Standard Multiplication */
        standardMultiply(A, B, C_std, n);
        int is_correct = verifyMatch(C_special, C_std, n);

        printf("%6d %15lld %15lld %18lld %12s\n",
               n,
               multiplication_count,
               addition_count,
               total_operations,
               is_correct ? "PASSED" : "FAILED");

        fprintf(fp, "%d,%lld,%lld,%lld,%lld\n",
                n,
                multiplication_count,
                addition_count,
                total_operations,
                n_squared);

        freeMatrix(A, n);
        freeMatrix(B, n);
        freeMatrix(C_special, n);
        freeMatrix(C_std, n);
    }

    fclose(fp);
    printf("\nData successfully saved to special_matrix_data.csv\n");

    return 0;
}