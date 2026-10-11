
### Question 6: Reorganise String with K-Distance Apart

**Algorithm:**
1. Count the occurrences of each letter in the string[cite: 6].
2. We need to fill positions from index 0 to len - 1[cite: 6].
3. For each position, greedily pick the character with the maximum remaining frequency whose last used position was at least K indices ago[cite: 6].
4. If for any position no character is valid to place, it is impossible to rearrange[cite: 6].
5. Place the chosen character, decrease its count, update its last used index, and move to the next position[cite: 6].

**Complexity:**
*   **Time Complexity:** O(n) overall[cite: 6]. Counting frequencies takes O(n)[cite: 6]. Greedy selection for n positions * alphabet size 26 is O(26 * n) = O(n)[cite: 6].
*   **Space Complexity:** O(1) extra space since the alphabet size is 26[cite: 6].
