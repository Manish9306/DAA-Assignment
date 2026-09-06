/*
================================================================================
Design and Analysis of Algorithm (DAA), Lab-06
Question 3: Fast Vector Convolution using Divide & Conquer (FFT) in O(n log n)
================================================================================

QUESTION:
3. Convolution operation on vectors of size n: The convolution of two vectors A and B
is a new vector C such that
                     m-1
             C[k] = \sum A[j] * B[k - j]
                     j=0
Assuming the lengths of A and B are of length m and n, respectively, and the indexing of
the vectors starts from 0, find an O(n log n) divide and conquer algorithm for this operation.
Consider, n >= m for your implementation and analysis.

By choosing the proper input representation, write a program in C to validate your algorithm.

--------------------------------------------------------------------------------
ALGORITHM & COMPLEXITY ANALYSIS:
--------------------------------------------------------------------------------
1. Problem Formulation:
   - Vector A has length m: A = [A[0], A[1], ..., A[m-1]]
   - Vector B has length n: B = [B[0], B[1], ..., B[n-1]], with n >= m.
   - The resulting convolution vector C has length L = m + n - 1.
   - Computing C directly via definition requires:
       C[k] = sum_{j=0}^{m-1} A[j] * B[k - j]  (with 0 <= k - j < n)
     Time Complexity of Direct/Naive method: O(m * n). If m = O(n), this is O(n^2).

2. Divide & Conquer via Fast Fourier Transform (Cooley-Tukey Radix-2):
   - By the Convolution Theorem, convolution in the time/spatial domain corresponds
     to pointwise multiplication in the frequency domain:
         C = IFFT( FFT(A_padded) (pointwise-mul) FFT(B_padded) )
   
   - Step 1: Zero-Padding:
     Pad both vectors A and B with zeros to the smallest power of 2:
         N = 2^(ceil(log2(m + n - 1)))
     Since m <= n, m + n - 1 < 2n. Thus N < 4n, so N = Theta(n).

   - Step 2: Divide and Conquer FFT:
     Represent vector as polynomial A(x) = A_even(x^2) + x * A_odd(x^2).
     Evaluate at N complex roots of unity: omega_N^k = e^(2*pi*i*k / N).
     Recurrence Relation:
         T(N) = 2 * T(N/2) + O(N)
     By the Master Theorem (Case 2: a=2, b=2, f(N)=Theta(N)):
         T(N) = Theta(N log N) = O(n log n).

   - Step 3: Pointwise Multiplication:
     C_freq[k] = A_freq[k] * B_freq[k] for all 0 <= k < N.
     Time Complexity: O(N) = O(n).

   - Step 4: Inverse FFT (IFFT):
     Compute IFFT of C_freq using the exact same divide-and-conquer FFT structure
     with conjugate roots of unity (e^(-2*pi*i*k/N)) and scaling by 1/N.
     Time Complexity: O(N log N) = O(n log n).

3. Total Complexity:
   - Total Time: O(n log n) + O(n log n) + O(n) + O(n log n) = O(n log n).
   - Auxiliary Space: O(N) = O(n) complex numbers.
================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Portable Complex Number Structure
typedef struct {
    double real;
    double imag;
} Complex;

// Complex arithmetic helpers
Complex complex_add(Complex a, Complex b) {
    Complex res = {a.real + b.real, a.imag + b.imag};
    return res;
}

Complex complex_sub(Complex a, Complex b) {
    Complex res = {a.real - b.real, a.imag - b.imag};
    return res;
}

Complex complex_mul(Complex a, Complex b) {
    Complex res = {
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real
    };
    return res;
}

/*
--------------------------------------------------------------------------------
Divide and Conquer Fast Fourier Transform (Cooley-Tukey Radix-2)
  - Recursive formulation:
    Divides problem of size N into 2 subproblems of size N/2 (even and odd indices).
    Combines results using twiddle factors omega_N^k in O(N) time.
  - Recurrence: T(N) = 2*T(N/2) + O(N) => O(N log N).
--------------------------------------------------------------------------------
*/
void fft_recursive(Complex *a, int n, int invert) {
    if (n <= 1) return;

    // Divide: separate into even and odd indexed coefficients
    Complex *a0 = (Complex *)malloc((n / 2) * sizeof(Complex));
    Complex *a1 = (Complex *)malloc((n / 2) * sizeof(Complex));
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    // Conquer: recursively compute FFT of even and odd halves
    fft_recursive(a0, n / 2, invert);
    fft_recursive(a1, n / 2, invert);

    // Combine: Butterfly operations using N-th roots of unity
    double angle = 2.0 * M_PI / n * (invert ? -1 : 1);
    Complex w = {1.0, 0.0};
    Complex wn = {cos(angle), sin(angle)};

    for (int i = 0; 2 * i < n; i++) {
        Complex t = complex_mul(w, a1[i]);
        a[i] = complex_add(a0[i], t);
        a[i + n / 2] = complex_sub(a0[i], t);

        if (invert) {
            a[i].real /= 2.0;
            a[i].imag /= 2.0;
            a[i + n / 2].real /= 2.0;
            a[i + n / 2].imag /= 2.0;
        }
        w = complex_mul(w, wn);
    }

    free(a0);
    free(a1);
}

/*
--------------------------------------------------------------------------------
Fast Vector Convolution: C = A * B
  - Computes convolution of vector A (size m) and vector B (size n, where n >= m).
  - Pads vectors to power-of-2 length N >= m + n - 1.
  - Applies FFT, pointwise multiplication, and IFFT.
Worst-Case Time Complexity: O(n log n)
Auxiliary Space Complexity: O(n)
--------------------------------------------------------------------------------
*/
void convolve_fft(const double *A, int m, const double *B, int n, double *C, int *out_len) {
    int final_len = m + n - 1;
    *out_len = final_len;

    // Find smallest power of 2 >= final_len
    int N = 1;
    while (N < final_len) {
        N <<= 1;
    }

    Complex *fa = (Complex *)calloc(N, sizeof(Complex));
    Complex *fb = (Complex *)calloc(N, sizeof(Complex));

    for (int i = 0; i < m; i++) fa[i].real = A[i];
    for (int i = 0; i < n; i++) fb[i].real = B[i];

    // Forward FFT on both vectors: O(N log N)
    fft_recursive(fa, N, 0);
    fft_recursive(fb, N, 0);

    // Pointwise multiplication in frequency domain: O(N)
    for (int i = 0; i < N; i++) {
        fa[i] = complex_mul(fa[i], fb[i]);
    }

    // Inverse FFT to return to spatial/time domain: O(N log N)
    fft_recursive(fa, N, 1);

    // Extract real parts of result
    for (int i = 0; i < final_len; i++) {
        C[i] = fa[i].real;
    }

    free(fa);
    free(fb);
}

/*
--------------------------------------------------------------------------------
Direct / Naive Convolution (for validation):
  - C[k] = sum_{j=0}^{m-1} A[j] * B[k - j]
Time Complexity: O(m * n)
Space Complexity: O(1)
--------------------------------------------------------------------------------
*/
void convolve_naive(const double *A, int m, const double *B, int n, double *C) {
    int final_len = m + n - 1;
    for (int k = 0; k < final_len; k++) {
        C[k] = 0.0;
        for (int j = 0; j < m; j++) {
            int b_idx = k - j;
            if (b_idx >= 0 && b_idx < n) {
                C[k] += A[j] * B[b_idx];
            }
        }
    }
}

// Utility function to print vector
void print_vector(const double *vec, int len, const char *name) {
    printf("%s (len = %d): [", name, len);
    for (int i = 0; i < len; i++) {
        printf("%.2f%s", vec[i], (i == len - 1) ? "" : ", ");
    }
    printf("]\n");
}

/*
--------------------------------------------------------------------------------
Main Driver Program
--------------------------------------------------------------------------------
*/
int main() {
    printf("==================================================================\n");
    printf("        DAA Lab 06 - Question 3: Vector Convolution in O(n log n)\n");
    printf("==================================================================\n\n");

    // Example with n >= m
    // Vector A of length m = 4
    double A[] = {1.0, 2.0, 3.0, 4.0};
    int m = sizeof(A) / sizeof(A[0]);

    // Vector B of length n = 6 (n >= m)
    double B[] = {2.0, 1.0, 0.0, 3.0, 1.0, 2.0};
    int n = sizeof(B) / sizeof(B[0]);

    int out_len = m + n - 1;
    double *C_fft = (double *)malloc(out_len * sizeof(double));
    double *C_naive = (double *)malloc(out_len * sizeof(double));

    print_vector(A, m, "Vector A (Kernel)");
    print_vector(B, n, "Vector B (Signal, n >= m)");
    printf("Output Convolution Length (m + n - 1): %d\n\n", out_len);

    // 1. Compute via Divide & Conquer FFT in O(n log n)
    int fft_out_len = 0;
    convolve_fft(A, m, B, n, C_fft, &fft_out_len);
    print_vector(C_fft, fft_out_len, "Result C via Divide & Conquer FFT O(n log n)");

    // 2. Compute via Naive O(m * n) method
    convolve_naive(A, m, B, n, C_naive);
    print_vector(C_naive, out_len, "Result C via Direct Definition O(m * n)");

    // 3. Validation Check
    printf("\n--- Validation & Accuracy Check ---\n");
    double max_err = 0.0;
    for (int i = 0; i < out_len; i++) {
        double err = fabs(C_fft[i] - C_naive[i]);
        if (err > max_err) max_err = err;
    }
    printf("Maximum Absolute Discrepancy between FFT and Naive: %.10e\n", max_err);
    if (max_err < 1e-6) {
        printf(">> STATUS: MATCH VERIFIED! FFT Divide & Conquer output is 100%% accurate.\n\n");
    } else {
        printf(">> STATUS: MISMATCH DETECTED!\n\n");
    }

    printf("--- Complexity Comparison Summary ---\n");
    printf("Naive Approach:            T(n) = O(m * n)       -> for m = n: O(n^2)\n");
    printf("Divide & Conquer (FFT):    T(n) = 2*T(n/2) + O(n)-> O(n log n)\n");
    printf("Speedup for large n (e.g., n = 10^5): ~10^10 ops reduced to ~1.7 * 10^6 ops!\n");

    free(C_fft);
    free(C_naive);

    printf("\n==================================================================\n");
    printf("                     End of Validation\n");
    printf("==================================================================\n");
    return 0;
}
