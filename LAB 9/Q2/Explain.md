
### Question 2: Huffman Coding

**Algorithm:**
1. Count or take input of frequencies for each symbol[cite: 2].
2. Build a Huffman tree using two minimum nodes at each step until 1 tree remains[cite: 2].
3. Compute code lengths for each leaf node by finding the tree depth[cite: 2].
4. Sort symbols first by code length, and for ties, alphabetically (canonical rule)[cite: 2].
5. Generate canonical binary codes using the prefix shift rule:
   - First code is 0 with its bit length[cite: 2].
   - Next code = (previous code + 1) shifted left by (len_diff)[cite: 2].
6. Print the codebook table and calculate the average length[cite: 2].

**Complexity:**
*   **Time Complexity:** O(n log n) overall[cite: 2]. Finding min nodes repeatedly takes O(n^2) or O(n log n) with a heap[cite: 2]. Sorting code lengths takes O(n log n)[cite: 2]. Code generation takes O(n)[cite: 2].
*   **Space Complexity:** O(n)[cite: 2].
