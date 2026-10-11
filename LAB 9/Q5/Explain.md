### Question 5: Candy Distribution Problem (Bi-directional Slope Greedy)

**Algorithm:**
1. Initialize a candies array where every child initially gets 1 candy[cite: 5].
2. Left-to-right pass:
   - For i from 1 to n - 1[cite: 5]:
   - If rating[i] > rating[i - 1], then candies[i] = candies[i - 1] + 1[cite: 5].
3. Right-to-left pass:
   - For i from n - 2 down to 0[cite: 5]:
   - If rating[i] > rating[i + 1] and candies[i] <= candies[i + 1], then candies[i] = candies[i + 1] + 1[cite: 5].
4. Add all values in the candies array to find the total minimum candies[cite: 5].

**Complexity:**
*   **Time Complexity:** O(n) overall[cite: 5]. The left pass takes O(n)[cite: 5]. The right pass takes O(n)[cite: 5]. The total sum takes O(n)[cite: 5].
*   **Space Complexity:** O(n)[cite: 5].
