## Algorithm
1. **Graph Input Representation:**
   - An Adjacency List is used to represent the graph in `O(V + E)` space, allowing iteration over incident edges of any vertex u in `O(deg(u))` time.
2. **Offline Reverse Time-Step Strategy:**
   - Deleting vertices splits components, which is expensive to maintain dynamically.
   - However, vertex deletions in forward order P = [p1, p2, ..., pV] can be modeled in reverse as sequential vertex additions from an initially empty graph.
   - After all V vertices are deleted, the graph is empty (max component sum = 0).
   - We iterate backwards from i = V - 1 down to 0:
       a. The answer after deleting vertices {p1, ..., pi} equals the current maximum component sum among already restored vertices {p_{i+1}, ..., pV}. Record `ans[i + 1] = curMax`.
       b. Activate vertex `u = p[i]`:
          Mark `active[u] = true`, set `compWeight[u] = weight[u]`, and update `curMax = max(curMax, compWeight[u])`.
       c. Traverse all neighbors v of u in the adjacency list.
          If `active[v]` is true and `find(u) != find(v)`:
            Unite the components of u and v using union by rank.
            Update the merged root's weight: `compWeight[newRoot] = compWeight[rootU] + compWeight[rootV]`.
            Update `curMax = max(curMax, compWeight[newRoot])`.
   - Print the recorded answers in forward order for each deletion step 1 to V.

## Complexity Analysis
- **Time Complexity:**
  - Adjacency List Construction: `O(V + E)` time.
  - Reverse DSU Processing: Each vertex is activated exactly once. Each edge (u, v) is checked at most twice (when each endpoint is activated). With path compression and union by rank, DSU find and union operations take amortized `O(α(V))` time.
  - Total Time Complexity: `O(V + E * α(V))` ≈ **`O(V + E)`**, which is nearly linear.
- **Space Complexity:**
  - Adjacency list: `O(V + E)` space.
  - DSU arrays (parent, rank, compWeight), active flags, and ans array: `O(V)` space.
  - Total Auxiliary Space: **`O(V + E)`**.
