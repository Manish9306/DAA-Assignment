## Algorithm
1. **Graph Abstraction:** We treat each word as a vertex. An edge exists between two words if their Hamming distance is exactly 1 (they differ by exactly one character).
2. **Bidirectional BFS Setup:**
   - Instead of a standard BFS which expands outward from `A` creating a massive search tree, we run two simultaneous BFS expansions: one forward from `A` and one backward from `B`.
   - Maintain two queues (`qA`, `qB`) and two Hash Maps/Sets to track visited words and their distances from the respective sources (`distA`, `distB`).
3. **Alternating Expansion:**
   - At each step, choose the smaller queue to expand. This strictly keeps the branching factor balanced and significantly reduces the search space.
   - Pop a word `u` from the chosen queue.
   - Generate all valid neighbors by systematically changing each character of `u` from 'a' to 'z' (i.e., `25 * L` possible mutations).
   - If a mutated word `v` exists in the dictionary `D`:
       - If `v` is unvisited in the current direction, add it to the current queue and record its distance.
       - **Intersection Check:** If `v` has *already been visited* by the opposite BFS search (e.g., it exists in the other Hash Map), an optimal path has been found. The shortest transformation sequence length is `distA[u] + distB[v] + 1`.
4. **Termination:** If the queues empty out without intersecting, return `-1` (no valid transformation sequence exists).

## Complexity Analysis
- **Time Complexity:** `O(B^(d/2) * L)` where `B` is the branching factor (max `25 * L`) and `d` is the shortest path length.
  Standard BFS takes `O(B^d)`. Bidirectional BFS cuts the depth in half, reducing the time to `O(B^(d/2))`. In the worst-case, it explores at most `N` words, taking bounded time `O(N * L)`.
- **Space Complexity:** `O(N * L)`.
  Storing the dictionary in a Hash Set, maintaining the bidirectional visited maps, and the queues require space proportional to the number of words `N` and their length `L`.
