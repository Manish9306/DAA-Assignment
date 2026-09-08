**Question 3: Reve's Puzzle (Frame-Stewart Algorithm)**

**Algorithm**:
* Choose an optimal partition integer 'k' between 1 and n-1[cite: 3].
* Recursively transfer the top (n - k) smallest disks from the source peg to an auxiliary peg using 4 pegs[cite: 3].
* Transfer the remaining 'k' largest disks from the source peg to the destination peg using 3 pegs[cite: 3].
* Recursively transfer the (n - k) smallest disks from the auxiliary peg to the destination peg using 4 pegs[cite: 3].

**Time Complexity**: 
* O(2^(sqrt(2*n))) moves[cite: 3].
