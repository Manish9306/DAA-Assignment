## Algorithm
1. **Data Structure Representation:**
   - DSU arrays:
       `parent[v]`     : parent pointer in DSU forest.
       `sz[root]`      : number of vertices in connected component.
       `compWeight[r]` : sum of vertex weights in connected component.
       `version[r]`    : monotonic version counter used to invalidate outdated heap entries.
   - Binary Max-Heap:
       Stores tuples `(weight, root, version)` for active components whose size <= K.
2. **Dynamic Component Merging & Maintenance:**
   - Initially, every single vertex forms a component of size 1 with weight w_v. If 1 <= K, each initial component is pushed to the Max-Heap with version 1.
   - When an edge (u, v) arrives:
       a. Find component roots `rootU = find(u)`, `rootV = find(v)`.
       b. If `rootU != rootV`, merge smaller component into larger (union by size).
       c. Let `rootU` be the merged root:
            `sz[rootU] += sz[rootV]`
            `compWeight[rootU] += compWeight[rootV]`
            `version[rootU]++`, `version[rootV]++`
       d. If `sz[rootU] <= K`, push the newly formed component `(compWeight[rootU], rootU, version[rootU])` into the Max-Heap.
3. **Querying the Maximum Valid Weight:**
   - Inspect the top of the Max-Heap using Lazy Deletion:
     Pop elements where `parent[root] != root` (no longer a root), `version[root] != top.version` (stale component data), or `sz[root] > K` (exceeded threshold).
   - The first valid element at the top gives the maximum component weight.

## Complexity Analysis
- **Time Complexity:**
  - Initialization: `O(V)` to initialize arrays and push V elements into heap.
  - DSU Operations: Path compression and union by size take `O(α(V))` per edge.
  - Max-Heap Operations: Each edge causes at most 1 push into the heap. Across all operations, at most (V + E) items are inserted and popped from the heap. Each heap push/pop takes `O(log(V + E))`.
  - Total Time Complexity: `O(V + E * log(V + E))` ≈ **`O((V + E) log V)`**.
- **Space Complexity:**
  - DSU arrays: `O(V)` space.
  - Max-Heap storage: `O(V + E)` space.
  - Total Auxiliary Space: **`O(V + E)`**.
