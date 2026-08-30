# 3. QuickSort on N Random Elements in a File

### Algorithm
1. **File IO:** Generate $N$ random integers and write to input file[cite: 1]. Read elements from file into memory[cite: 1].
2. **QuickSort:** Partition the array around a random pivot[cite: 1]. Recursively sort the left and right sub-arrays[cite: 1].
3. **Output:** Write the fully sorted array into the destination output file[cite: 1].

### Time Complexity
* **Average Case:** $O(N \log N)$ (recursion depth is $\log N$, partitioning is $N$)[cite: 1]
* **Worst Case:** $O(N^2)$[cite: 1]
