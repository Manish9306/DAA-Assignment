## Algorithm
1. **Coordinate Flattening:**
   Map 2D coordinates (r, c) of the R x C grid to unique 1D integers:
     `index = r * C + c`  (where 0 <= r < R, 0 <= c < C).
2. **Data Structure:**
   - Maintain a 1D DSU with `parent[]` and `rankArr[]` for R * C elements.
   - Maintain a `grid[]` array where 0 = water and 1 = land.
   - Maintain a counter `islands` initialized to 0.
3. **Dynamic Land Addition:**
   When adding a land cell at (r, c):
   - Compute `id = r * C + c`.
   - If `grid[id]` is already 1, the count of islands is unchanged.
   - Otherwise:
       a. Mark `grid[id] = 1`, initialize `parent[id] = id`, and increment `islands++`.
       b. Check the 4 orthogonal neighbors: `(r-1, c)`, `(r+1, c)`, `(r, c-1)`, `(r, c+1)`.
       c. For each neighbor (nr, nc) within grid bounds where `grid[nid] == 1`:
          If `find(id) != find(nid)`, unite them and decrement `islands--`.
   - Output the updated island count after each step.

## Complexity Analysis
- **Time Complexity:**
  - Grid and DSU Initialization: `O(R * C)` to allocate and initialize arrays.
  - Per Land Addition: Inspects at most 4 neighbors. For each adjacent land cell, find and unite take amortized `O(α(R * C))` time using path compression and union by rank.
  - Total Time for K operations: `O(R * C + K * α(R * C))` ≈ **`O(R * C + K)`**.
- **Space Complexity:**
  - **`O(R * C)`** auxiliary space for DSU parent, rank, and grid state arrays.
