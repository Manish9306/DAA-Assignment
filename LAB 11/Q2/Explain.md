## Algorithm
1. **Multi-Source Initialization:**
   - Initialize a `queue` for BFS.
   - Initialize two arrays: `owner[V]` set to `-1` (unassigned) and `dist[V]` set to `infinity`.
   - For every hub `h_i` (from `1` to `K`):
       - Set `owner[h_i] = i` and `dist[h_i] = 0`.
       - Push `h_i` into the queue.
2. **Simultaneous Expansion:**
   - While the queue is not empty, pop the current vertex `u`.
   - If `dist[u] == R`, do not expand to its neighbors (enforcing the radius threshold `R`).
   - For every adjacent vertex `v` of `u`:
       - **Unvisited Node:** If `dist[v] == infinity`:
           - Set `dist[v] = dist[u] + 1` and `owner[v] = owner[u]`.
           - Push `v` into the queue.
       - **Tie-Breaking:** If `dist[v] == dist[u] + 1`:
           - This means `v` is reached by multiple hubs at the exact same minimum distance.
           - Apply deterministic tie-breaking: `owner[v] = min(owner[v], owner[u])`.
3. **Result:** The `owner` array now correctly holds the closest hub index (with tie-breaking) for all reachable vertices within radius `R`, and `-1` for those outside the coverage area.

## Complexity Analysis
- **Time Complexity:** `O(V + E)`. 
  This is a standard Breadth-First Search where multiple sources are enqueued at level 0. Each vertex and edge in the graph is visited and processed a constant number of times.
- **Space Complexity:** `O(V)`.
  The queue can hold at most `V` vertices, and the `owner` and `dist` arrays both require `O(V)` space.
