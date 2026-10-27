## Algorithm
1. **State Representation:** Since the effective cost depends on the parity (even/odd) of the number of weight-1 edges traversed, we split every vertex `v` into two states: `(v, 0)` for an even count, and `(v, 1)` for an odd count.
2. **0-1 BFS Initialization:** Use a double-ended queue (Deque) since edge weights are exclusively 0 or 1.
   - Initialize a distance array `dist[V][2]` with infinity.
   - Set the source distance `dist[S][0] = 0` and push `(S, 0)` to the front of the deque.
3. **State Exploration:** 
   - While the deque is not empty, pop the front element `(u, p)` where `p` is the current parity.
   - For every outgoing edge from `u` to `v` with weight `w`:
       - Calculate the new parity: `np = (p + w) % 2`.
       - Calculate the new cost: `new_cost = dist[u][p] + w`.
       - If `new_cost < dist[v][np]`:
           - Update `dist[v][np] = new_cost`.
           - If `w == 0`, push `(v, np)` to the **front** of the deque.
           - If `w == 1`, push `(v, np)` to the **back** of the deque.
4. **Final Computation:** For each vertex `v`, the minimum effective cost from `S` is the minimum of:
   - `dist[v][0]` (cost with an even number of 1-weight edges, no penalty)
   - `dist[v][1] + C` (cost with an odd number of 1-weight edges, plus penalty `C`)

## Complexity Analysis
- **Time Complexity:** `O(V + E)`. 
  Because there are only two states per vertex, the total number of states in our modified graph is `2V` and the number of edges is `2E`. 0-1 BFS processes each state and edge at most once in linear time.
- **Space Complexity:** `O(V)`.
  The distance array requires `2 * V` space, and the Deque holds at most `2V` elements at any time.
