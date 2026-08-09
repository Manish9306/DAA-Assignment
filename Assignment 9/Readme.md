/*
ALGORITHMS FOR MERGING k SORTED ARRAYS (EACH OF SIZE n)


1. METHOD 1: SEQUENTIAL / ITERATIVE MERGING

• Input:  An array of k sorted arrays `Arrays[0...k-1]`, each containing n elements.
• Output: A single sorted array `Result` of size (k * n).

• Algorithm Steps:
  1. Initialize `Result` as a copy of `Arrays[0]`.
  2. Set `current_size = n`.
  3. Loop `i` from 1 to `k - 1`:
     a. Allocate a temporary array `Temp` of size `(current_size + n)`.
     b. Merge sorted arrays `Result` (size `current_size`) and `Arrays[i]` (size `n`) into `Temp`.
     c. Update `Result = Temp`.
     d. Update `current_size = current_size + n`.
  4. Return `Result`.


2. METHOD 2: DIVIDE AND CONQUER / PAIRWISE MERGING

• Input:  An array of k sorted arrays `Arrays[0...k-1]`, each containing n elements.
• Output: A single sorted array `Result` of size (k * n).

• Algorithm Steps:
  1. Place all k arrays into a working list of arrays `CurrentList`.
  2. While size of `CurrentList` > 1:
     a. Create an empty list of arrays `NextList`.
     b. Loop `i` from 0 to `length(CurrentList) - 1` with step size 2:
        - If `(i + 1) < length(CurrentList)`:
            Merge `CurrentList[i]` and `CurrentList[i+1]` using standard 2-way merge.
            Append the merged result to `NextList`.
        - Else (odd array left out):
            Append `CurrentList[i]` directly to `NextList`.
     c. Set `CurrentList = NextList`.
  3. Return the single remaining array in `CurrentList`.*/
