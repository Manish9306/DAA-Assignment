## Algorithm
1. We maintain a Disjoint Set Union (DSU) data structure augmented with distance parity (parity-tracking / 2-coloring DSU).
2. For each vertex x:
     - `parent[x]`: parent in the DSU forest.
     - `parity[x]`: color difference (0 or 1) between vertex x and `parent[x]` (0: same color, 1: opposite color).
     - `rank[x]`: tree height upper bound for union by rank.
3. During `find(x)`, path compression is applied, recursively updating parity:
     `parity[x] = parity[x] ^ parity[old_parent]`.
4. When an online edge (u, v) arrives:
   - Find roots: `rootU = find(u)`, `rootV = find(v)`.
   - If `rootU == rootV`:
       - If `parity[u] == parity[v]`, u and v have the same partition color. Connecting them introduces an odd-length cycle, violating bipartiteness. The edge is rejected.
       - If `parity[u] != parity[v]`, u and v have opposite colors. Adding the edge forms an even-length cycle, so bipartiteness is maintained.
   - If `rootU != rootV`:
       - Connect the two trees via union by rank.
       - Assign relative parity to link the roots: `parity[rootU] = parity[u] ^ parity[v] ^ 1`.

## Complexity Analysis
- **Time Complexity:**
  - Initialization: `O(V)` to initialize parent, parity, and rank arrays.
  - Edge Processing: Each edge performs 2 find operations and at most 1 union operation. With path compression and union by rank, each operation takes `O(α(V))` amortized time, where `α` is the Inverse Ackermann function.
  - Total Time for E online edges: `O(V + E * α(V))` ≈ **`O(V + E)`**.
- **Space Complexity:**
  - **`O(V)`** auxiliary space for parent, parity, and rank arrays.
