/*Q4.Matrix Multiplication using D&C Approach: Write a C program to multiply two square matrices of size n × n using 
Strassen’s method.*/

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
    for (int i = 0; i < n; i++)
        free(matrix[i]);

    free(matrix);
}

/* Generate random matrix */
void generateMatrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
}

/* Add two matrices */
void addMatrix(
    int **A,
    int **B,
    int **C,
    int n)
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

/* Subtract two matrices */
void subtractMatrix(
    int **A,
    int **B,
    int **C,
    int n)
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

/* Strassen Matrix Multiplication */
void strassen(
    int **A,
    int **B,
    int **C,
    int n)
{
    /* Base case */
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        multiplication_count++;
        return;
    }

    int newSize = n / 2;

    /* Allocate submatrices */
    int **A11 = allocateMatrix(newSize);
    int **A12 = allocateMatrix(newSize);
    int **A21 = allocateMatrix(newSize);
    int **A22 = allocateMatrix(newSize);

    int **B11 = allocateMatrix(newSize);
    int **B12 = allocateMatrix(newSize);
    int **B21 = allocateMatrix(newSize);
    int **B22 = allocateMatrix(newSize);

    int **M1 = allocateMatrix(newSize);
    int **M2 = allocateMatrix(newSize);
    int **M3 = allocateMatrix(newSize);
    int **M4 = allocateMatrix(newSize);
    int **M5 = allocateMatrix(newSize);
    int **M6 = allocateMatrix(newSize);
    int **M7 = allocateMatrix(newSize);

    int **T1 = allocateMatrix(newSize);
    int **T2 = allocateMatrix(newSize);

    /* Divide A and B into four submatrices */

    for (int i = 0; i < newSize; i++)
    {
        for (int j = 0; j < newSize; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    /*
        Strassen's seven products

        M1 = (A11 + A22)(B11 + B22)
        M2 = (A21 + A22)B11
        M3 = A11(B12 - B22)
        M4 = A22(B21 - B11)
        M5 = (A11 + A12)B22
        M6 = (A21 - A11)(B11 + B12)
        M7 = (A12 - A22)(B21 + B22)
    */

    addMatrix(A11, A22, T1, newSize);
    addMatrix(B11, B22, T2, newSize);
    strassen(T1, T2, M1, newSize);

    addMatrix(A21, A22, T1, newSize);
    strassen(T1, B11, M2, newSize);

    subtractMatrix(B12, B22, T2, newSize);
    strassen(A11, T2, M3, newSize);

    subtractMatrix(B21, B11, T2, newSize);
    strassen(A22, T2, M4, newSize);

    addMatrix(A11, A12, T1, newSize);
    strassen(T1, B22, M5, newSize);

    subtractMatrix(A21, A11, T1, newSize);
    addMatrix(B11, B12, T2, newSize);
    strassen(T1, T2, M6, newSize);

    subtractMatrix(A12, A22, T1, newSize);
    addMatrix(B21, B22, T2, newSize);
    strassen(T1, T2, M7, newSize);

    /*
        C11 = M1 + M4 - M5 + M7
        C12 = M3 + M5
        C21 = M2 + M4
        C22 = M1 - M2 + M3 + M6
    */

    for (int i = 0; i < newSize; i++)
    {
        for (int j = 0; j < newSize; j++)
        {
            C[i][j] =
                M1[i][j] + M4[i][j]
                - M5[i][j] + M7[i][j];

            addition_count += 3;

            C[i][j + newSize] =
                M3[i][j] + M5[i][j];

            addition_count++;

            C[i + newSize][j] =
                M2[i][j] + M4[i][j];

            addition_count++;

            C[i + newSize][j + newSize] =
                M1[i][j] - M2[i][j]
                + M3[i][j] + M6[i][j];

            addition_count += 3;
        }
    }

    /* Free memory */

    freeMatrix(A11, newSize);
    freeMatrix(A12, newSize);
    freeMatrix(A21, newSize);
    freeMatrix(A22, newSize);

    freeMatrix(B11, newSize);
    freeMatrix(B12, newSize);
    freeMatrix(B21, newSize);
    freeMatrix(B22, newSize);

    freeMatrix(M1, newSize);
    freeMatrix(M2, newSize);
    freeMatrix(M3, newSize);
    freeMatrix(M4, newSize);
    freeMatrix(M5, newSize);
    freeMatrix(M6, newSize);
    freeMatrix(M7, newSize);

    freeMatrix(T1, newSize);
    freeMatrix(T2, newSize);
}

int main()
{
    FILE *fp;

    /*
        Matrix sizes must be powers of 2
        for straightforward Strassen recursion.
    */
    int sizes[] = {
        2, 4, 8, 16, 32, 64, 128
    };

    int numberOfSizes =
        sizeof(sizes) / sizeof(sizes[0]);

    fp = fopen("strassen_data.csv", "w");

    if (fp == NULL)
    {
        printf("Error opening CSV file.\n");
        return 1;
    }

    fprintf(
        fp,
        "n,strassen_multiplications,strassen_additions,"
        "total_operations,theoretical_multiplications\n"
    );

    srand((unsigned int)time(NULL));

    printf("\n");
    printf("Strassen Matrix Multiplication\n");
    printf("==============================\n");

    printf(
        "%8s %20s %18s %18s\n",
        "n",
        "Multiplications",
        "Additions",
        "Total Operations"
    );

    for (int s = 0; s < numberOfSizes; s++)
    {
        int n = sizes[s];

        int **A = allocateMatrix(n);
        int **B = allocateMatrix(n);
        int **C = allocateMatrix(n);

        if (A == NULL || B == NULL || C == NULL)
        {
            printf("Memory allocation failed for n = %d\n", n);
            fclose(fp);
            return 1;
        }

        generateMatrix(A, n);
        generateMatrix(B, n);

        multiplication_count = 0;
        addition_count = 0;

        /* Execute Strassen */
        strassen(A, B, C, n);

        long long total_operations =
            multiplication_count + addition_count;

        /*
            Strassen multiplication recurrence:
            M(n) = 7M(n/2)

            Therefore:
            M(n) = n^(log2(7))
        */
        double theoretical_multiplications =
            pow((double)n, log2(7.0));

        printf(
            "%8d %20lld %18lld %18lld\n",
            n,
            multiplication_count,
            addition_count,
            total_operations
        );

        fprintf(
            fp,
            "%d,%lld,%lld,%lld,%.2f\n",
            n,
            multiplication_count,
            addition_count,
            total_operations,
            theoretical_multiplications
        );

        freeMatrix(A, n);
        freeMatrix(B, n);
        freeMatrix(C, n);
    }

    fclose(fp);

    printf("\nData successfully saved to strassen_data.csv\n");

    return 0;
}