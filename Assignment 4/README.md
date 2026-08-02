# Algorithm

1. **Define Recursive Tower of Hanoi Function:** Create a recursive function `TOH` that accepts the number of disks `n` along with three peg identifiers: `source`, `auxiliary`, and `destination`.
2. **Base Case:** If `n == 1`, directly print the instruction to move disk 1 from the `source` peg to the `destination` peg, increment the global `moves` counter, and return.
3. **First Recursive Step:** Recursively call `TOH(n - 1, source, destination, auxiliary)` to move the top $n - 1$ disks from `source` to `auxiliary` using `destination` as a temporary peg.
4. **Move Largest Disk:** Print the instruction to move disk `n` directly from `source` to `destination` and increment the `moves` counter.
5. **Second Recursive Step:** Recursively call `TOH(n - 1, auxiliary, source, destination)` to move the $n - 1$ disks from `auxiliary` to `destination` using `source` as a temporary peg.
6. **Execute and Output Total:** In `main`, prompt the user to input $n$, invoke `TOH(n, 'A', 'B', 'C')`, and print the grand total of moves stored in the global variable.

---

# Complexity

* **Time Complexity: O(2ⁿ)** — The total number of recursive calls made doubles with each additional disk, following the recurrence relation $T(n) = 2T(n - 1) + 1$, which solves to $2^n - 1$ total move operations.
* **Space Complexity: O(n)** — Determined by the maximum depth of the call stack required for recursive execution, which grows linearly with $n$.
