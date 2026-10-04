### 9. Collatz Conjecture Trajectory Analysis

#### Problem Statement
The Collatz Conjecture defines a recurrence relation for any strictly positive integer n:
   T(n) = n / 2      if n is even
          3n + 1     if n is odd
Analyse the trajectory of a user-provided starting value n >= 1 and across an interval [a, b].

#### Algorithm
CollatzTrajectory(n):
1. count = 0
2. While n != 1:
     Print n
     If n is even:
       n = n / 2
     Else:
       n = 3 * n + 1
     count = count + 1
3. Print 1
4. Return count

AnalyseInterval(a, b):
1. maxSteps = 0, maxN = a
2. For each i in [a, b]:
     steps = CollatzTrajectory(i)
     If steps > maxSteps:
       maxSteps = steps
       maxN = i
3. Return maxN, maxSteps

#### Complexity Analysis
- Time Complexity: Upper bound is not mathematically proven (open problem); empirically runs in O(log n) to O(n) steps per trajectory.
- Space Complexity: O(1) auxiliary space per trajectory.
