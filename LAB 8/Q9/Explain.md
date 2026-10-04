ALGORITHM:
----------
CollatzTrajectory(n):
1. count = 0
2. While n != 1:
     Print n
     If n is even: n = n / 2
     Else: n = 3*n + 1
     count++
3. Print 1, return count

AnalyseInterval(a, b):
1. For each n in [a, b]:
     Compute CollatzTrajectory length (stopping time)
2. Track and print the number with the longest trajectory

TIME COMPLEXITY:  Not proven bounded (conjecture is open!)
                  Empirically each trajectory takes O(log n) to O(n) steps.
SPACE COMPLEXITY: O(1) per trajectory
*/
