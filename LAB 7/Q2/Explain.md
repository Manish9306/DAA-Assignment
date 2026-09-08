**Question 2: Super Egg Testing Experiment**

**Algorithm**:
* Use a Dynamic Programming formulation where DP[e][f] represents the minimum drops in the worst case for 'e' eggs and 'f' floors[cite: 2].
* Establish base cases: DP[e][0] = 0 and DP[e][1] = 1 for all e >= 1; DP[1][f] = f for all f >= 1[cite: 2].
* Apply the recurrence relation for e > 1 and f > 1: DP[e][f] = 1 + min_{1 <= k <= f} { max(DP[e - 1][k - 1], DP[e][f - k]) }[cite: 2].

**Time Complexity**: 
* O(E * F^2)[cite: 2].
