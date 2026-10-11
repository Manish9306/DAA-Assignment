### Question 9: Hu-Tucker Greedy Simulation

**Algorithm:**
1. Combination phase:
   - Keep weights in a list preserving sequence[cite: 9].
   - Two nodes (i, j) with i < j are compatible if every element between them is already an internal merged node[cite: 9].
   - Repeatedly find the compatible pair with minimum sum (w[i] + w[j]), merge them, replace the left node with the sum, and remove the right node[cite: 9].
   - Continue until only 1 node remains[cite: 9].
2. Level Assignment phase:
   - Calculate the depth of each original weight from the tree[cite: 9].
3. Reconstruction phase:
   - Build an alphabetic binary tree with the computed leaf depths[cite: 9].

**Complexity:**
*   **Time Complexity:** O(n^2) overall[cite: 9]. The pair searching simulation takes O(n^2)[cite: 9]. Depth assignment takes O(n)[cite: 9].
*   **Space Complexity:** O(n)[cite: 9].
