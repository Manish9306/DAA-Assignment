
### Question 10: Greedy Superstring Conjecture

**Algorithm:**
1. First eliminate any string that is already a substring of another string[cite: 10].
2. While more than one string remains in the collection:
   - For every pair of strings (i, j), calculate maximum suffix-prefix overlap[cite: 10].
   - Pick the pair (i, j) that gives the largest overlap[cite: 10].
   - Merge them by appending string j (excluding the overlapping prefix) to string i[cite: 10].
   - Delete string j from the collection[cite: 10].
3. The remaining string is our greedy superstring[cite: 10].

**Complexity:**
*   **Time Complexity:** O(n^3 * L) overall[cite: 10]. Pairwise overlap calculation takes O(n^2 * L) where L is max string length[cite: 10]. Merging over n-1 iterations takes O(n^3 * L)[cite: 10].
*   **Space Complexity:** O(n * L)[cite: 10].
