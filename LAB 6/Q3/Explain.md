# Question 3: Convolution Operation on Vectors

**Assumption:** Vector sizes are $n$ and $m$, with $n \ge m$.

*   **Algorithm (Divide and Conquer via Fast Fourier Transform - FFT):**
    1.  Pad both vectors $A$ and $B$ with zeros so their lengths are a power of 2, specifically $L = 2^{\lceil \log_2(n+m-1) \rceil}$.
    2.  Compute the Discrete Fourier Transform (DFT) of both padded vectors using the $O(L \log L)$ Fast Fourier Transform (FFT) algorithm.
    3.  Perform element-wise multiplication of the transformed vectors in $O(L)$ time.
    4.  Compute the Inverse Fast Fourier Transform (IFFT) of the resulting vector to obtain the final convolution $C$.

*   **Time Complexity Analysis:** 
    Since the padded length $L$ is at most $2(n+m)$, and given $n \ge m$, $L$ is bound by $O(n)$. The FFT and IFFT steps dictate the time complexity.
    *   **Worst-case Complexity:** $O(n \log n)$
