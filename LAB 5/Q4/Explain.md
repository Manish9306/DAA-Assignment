# 4. Heap Sort on N Random Elements in a File

### Algorithm
1. **File IO:** Generate $N$ random integers, read into an array[cite: 1].
2. **Build Max-Heap:** Process non-leaf nodes bottom-up, calling Max-Heapify to establish heap property[cite: 1].
3. **Extract & Sort:** Swap the root (maximum) with the last element, reduce heap size, and Max-Heapify the root[cite: 1]. Repeat until sorted[cite: 1].

### Time Complexity
* **Overall Time Complexity:** Guaranteed $O(N \log N)$ in all cases (Best, Average, Worst) — Build-Heap takes $O(N)$, extraction takes $O(N \log N)$[cite: 1]
