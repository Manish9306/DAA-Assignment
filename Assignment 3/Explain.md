# Algorithm

1. **Define Sorting Functions:** Create two sorting helper functions: `bubbleSortOptimized` (which uses a `swapped` flag to early-exit if no swaps occur in a pass) and `bubbleSortNormal` (standard Bubble Sort without early exit).
2. **Track Comparisons:** In both functions, maintain a `comparisons` counter that increments during every element comparison (`arr[j] > arr[j + 1]`) and returns the total count upon completion.
3. **Initialize Experiment:** In `main`, seed the pseudo-random number generator using `srand(time(NULL))` and define an array of dataset sizes (`sizes = {100, 200, 300, 400, 500}`).
4. **Generate Test Data:** Loop through each array size $N$, allocating two identical arrays (`arr1` and `arr2`) filled with the same pseudo-random values (`rand() % 1000`).
5. **Execute and Compare:** Run `bubbleSortOptimized` on `arr1` and `bubbleSortNormal` on `arr2` to record their respective comparison counts.
6. **Output Results:** Print a tab-separated comparison table displaying array sizes alongside the total comparisons performed by each algorithm variant.

---

# Complexity

* **Time Complexity: O(N²)** — In the worst and average cases, both algorithm variants perform nested iterations resulting in **O(N²)** operations. The optimized version achieves **O(N)** best-case time complexity when the input array is already sorted.
* **Space Complexity: O(N)** — Storage space for the fixed stack buffers allocated in `main` to hold array elements for sorting.
