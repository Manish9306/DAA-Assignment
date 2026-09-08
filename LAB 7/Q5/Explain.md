**Question 5: Hitting a Moving Target**

**Algorithm**:
* Utilize a Two-Phase Sweep Strategy for n >= 3[cite: 5].
* Execute Phase 1 (Forward Sweep) by shooting spots 2, 3, ..., n - 1 to catch the target if it started on an EVEN spot[cite: 5].
* Execute Phase 2 (Backward Sweep) by shooting spots n - 1, n - 2, ..., 2 to corner the target if it started on an ODD spot[cite: 5].
* Track the belief-state by maintaining an array of possible candidate spots and reducing it after each shot until empty[cite: 5].

**Time Complexity**: 
* O(n) shots; O(n^2) for the belief-state simulation[cite: 5].
