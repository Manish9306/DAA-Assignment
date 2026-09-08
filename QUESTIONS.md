Questions
# Question 1: Function Growth Rate Order

Using implementation in C, place the given functions in a list by increasing order of growth for sufficiently large values of $n$:

$n \log_2 n$, $12\sqrt{n}$, $n^{\log_2 n}$, $100n^2 + 6n$, $n^{0.51}$, $n^2 - 324$, $50n^{0.5}$, $2n^3$, $3^n$, $2^{32}n$, $\log_2 n$

---

# Question 2: Fair vs. Biased Coin Simulation

Using simulation in C, show that the probability of getting a HEAD by tossing a fair coin is about 0.5. Extend your simulation to compare fair vs. biased coin-tossing experiments.

---

# Question 3: Performance Analysis of Bubble Sort

Using C, implement two different versions of bubble sort simulation for randomised data sequences as follows:

1. **Optimized Bubble Sort:** Terminates if the array is sorted before the $(n-1)^{\text{th}}$ pass.
2. **Standard Bubble Sort:** Always completes the $(n-1)^{\text{th}}$ pass.

Plot the number of comparisons in both cases to analyse their efficiency.

---

# Question 4: Towers of Hanoi (ToH)

Simulate the solution to the ToH problem using C. Plot the total number of moves required for solving the problem of $n$-discs. What can you conclude about your algorithm from the plot obtained?

---

# Question 5: Find the Partition Point

Consider an array $A$ with $n$ elements containing a run of 0's followed by a run of 1's. Implement a method to find out the exact point of transition between them.

---

# Question 6: Element Uniqueness

For given $n$ random numbers, implement a method in C to check if there are any duplicates. What can you conclude about your method for a sufficiently large value of $n$?

---

---

## Question 7: Dictionary Operations

Consider a dictionary ($D$) abstract data type that permits access to data items by content (key)[cite: 1]. The following are the primary operations that the dictionary supports[cite: 1]:

* **Search($D, k$)**: Given a search key $k$, return a pointer to the elements in the dictionary $D$ whose key value is $k$, if one exists[cite: 1].
* **Insert($D, x$)**: Given a data item $x$, add it to the Dictionary $D$[cite: 1].
* **Delete($D, x$)**: Given a pointer to a data item $x$ in the dictionary $D$, remove it from $D$[cite: 1].
* **Max($D$)** or **Min($D$)**: Retrieve the item with the largest (or smallest) key from $D$[cite: 1]. These two operations help the dictionary to serve as a priority queue[cite: 1].
* **Predecessor($D, x$)** or **Successor($D, x$)**: Retrieve the item from $D$ whose key is immediately before (or after) the item $x$ in sorted order[cite: 1].

What are the asymptotic worst-case running times for all the seven primary operations when the said data structure is implemented using[cite: 1]:
* An unsorted array[cite: 1].
* A sorted array[cite: 1].
* A singly linked unsorted list[cite: 1].
* A singly linked sorted list[cite: 1].
* A doubly linked unsorted list[cite: 1].
* A doubly linked sorted list[cite: 1].

> **Task:** Write a C program to validate your claim by plotting the order of growth of these functions[cite: 1].

---

## Question 8: Merge Sort vs. Modified Merge Sort

Consider the following modification to merge sort: divide the input array into thirds (rather than halves), recursively sort each third, and finally combine the results using a three-way merge subroutine[cite: 1]. What is the worst-case running time of this modified merge sort?[cite: 1]

> **Task:** Write a C program to validate your claim by plotting the order of growth for both the merge sort (discussed in class) and the modified merge sort described above[cite: 1].

---

## Question 9: Merging $k$ Sorted Arrays

Suppose you are given $k$ sorted arrays, each with $n$ elements, and you want to combine them into a single sorted array of $kn$ elements[cite: 1].

### (a) Method 1
One approach is to use the merge subroutine repeatedly, merging the first two arrays, then merging the result with the third array, then with the fourth array, and so on until you merge in the $k^{\text{th}}$ and final input array[cite: 1]. 

* Write a program to validate this idea[cite: 1].
* Find the worst-case running time of this method[cite: 1].

### (b) Method 2
Consider the algorithm that first divides the $k$ arrays into $\frac{k}{2}$ pairs of arrays and uses the merge subroutine to combine each pair, resulting in $\frac{k}{2}$ sorted arrays of length $2n$[cite: 1]. The algorithm repeats this step until there is only one sorted array of length $kn$[cite: 1].

* Write a program to validate this idea[cite: 1].
* What is the running time of this method as a function of $n$ and $k$?[cite: 1]

---s
# Lab 3: Divide and Conquer & Analysis of Algorithms

---

## Question 1: Binary vs. Ternary Search

In binary search, an $n$-element list is divided into nearly two equal halves, while in ternary search, it is divided into nearly three equal intervals. Then the search proceeds in one of the intervals.

> **Task:** Design and implement a C program to search for an element $x$ in a sorted list of size $n$ using binary and ternary search. Justify and validate that binary search is better than ternary search via your implementation.

---

## Question 2: Search the Defective Coin

Imagine you are working as the quality-control engineer for a company that makes coins. The company needs to certify that all coins have identical weights. During inspection, you observe that a worker shaping a coin was distracted and dropped that coin into a pile of $(n - 1)$ perfectly identical coins. 

The worker was shaping the coin for longer than required; thus, the coin is either lighter than normal or perfectly weighted, but certainly not heavier. Your task is to determine which coin is lighter (defective) or report that none is lighter using a balance weighing scale.

> **Task:** Provide a divide-and-conquer algorithm and implement it to find the lighter (defective) coin, if present or not, in $\mathcal{O}(\log_2 n + c)$ time for some positive constant $c$.

---

## Question 3: Max and Min using D&C Approach

Using the divide-and-conquer approach, develop an algorithm to find both the maximum and minimum elements in an array of size $n$ such that the number of element comparisons is bounded by $\lceil 3n/2 \rceil - 2$.

> **Task:** Implement your algorithm in C to validate the theoretical bound on the number of comparisons.

---

## Question 4: Matrix Multiplication using Strassen's Method

Standard matrix multiplication requires $\mathcal{O}(n^3)$ operations. Strassen’s divide-and-conquer method reduces the subproblems from 8 to 7 recursive multiplications.

> **Task:** Write a C program to multiply two square matrices of size $n \times n$ using Strassen’s algorithm.

---

## Question 5: Multiply Special-Pattern Square Matrices

Two $n \times n$ matrices are provided where $n = 2^k$ for some natural number $k$. Each matrix has a recursive structure such that when partitioned into four equal-sized blocks, the two diagonal blocks are identical, and the two off-diagonal blocks are identical:

$$M = \begin{bmatrix} M_1 & M_2 \\ M_2 & M_1 \end{bmatrix}$$

Each sub-block maintains this recursive structure down to single integer elements.

> **Task:** Design a divide-and-conquer $\mathcal{O}(n^2)$ algorithm to multiply two such structured matrices, implement it in C, and validate its time complexity.

---

## Question 6: Use of Loop Invariants in Sorting

Consider sorting $n$ numbers stored in an array $A[1 \dots n]$ (Selection Sort):
* Find the smallest element of $A[1 \dots n]$ and exchange it with $A[1]$.
* Find the smallest element of $A[2 \dots n]$ and exchange it with $A[2]$.
* Continue in this manner for the first $(n - 1)$ elements of $A$.

Address the following theoretical points:
* Write the pseudocode for this algorithm.
* State the loop invariant maintained by this algorithm and prove its correctness (Initialization, Maintenance, Termination).
* Explain why the outer loop only needs to run for $(n - 1)$ elements rather than all $n$ elements.
* Give the worst-case and best-case running times in $\Theta$-notation.

> **Task:** Implement the algorithm in C to validate your theoretical claims.

# Lab 4

### Question 1: Application of Sorting-I (Stable Color Sort)
Assume that we are given $n$ pairs of items as input, where the first item is a number and the second item is one of three colours (red, blue, or yellow)[cite: 1]. Further assume that the items are sorted by number[cite: 1]. Give an $O(n)$ algorithm to sort the items by colour (all reds before all blues before all yellows) such that the numbers for identical colours stay sorted[cite: 1]. By choosing the proper input representation, write a program in C to validate your algorithm[cite: 1].

---

### Question 2: Application of Sorting-II (Pair Sum Across Two Sets)
Given two sets $S_1$ and $S_2$ (each of size $n$), and a number $x$, describe an $O(n \log n)$ algorithm for finding whether there exists a pair of elements, one from $S_1$ and one from $S_2$, that add up to $x$[cite: 1]. By choosing the proper input representation, write a program in C to validate your algorithm[cite: 1].

---

### Question 3: Application of Sorting-III ($k$-Sum Search)
Given a set $S$ of $n$ integers and an integer $T$, give an $O(n^{k-1} \log n)$ algorithm to test whether $k$ of the integers in $S$ add up to $T$[cite: 1]. By choosing the proper input representation, write a program in C to validate your algorithm[cite: 1].

---

### Question 4: Application of Sorting-IV (Maximum Simultaneous Guests)
A camera at the door tracks the entry time $a_i$ and exit time $b_i$ (assume $b_i > a_i$) for each of the $n$ persons $p_i$ attending a party[cite: 1]. Give an $O(n \log n)$ algorithm that analyses this data to determine the time when the most people were simultaneously present at the party[cite: 1]. Assume that all entry and exit times are distinct (no ties)[cite: 1]. By choosing the proper input representation, write a program in C to validate your algorithm[cite: 1].

---

### Question 5: Application of Sorting-V (Merge Overlapping Intervals)
Given a list $I$ of $n$ intervals, specified as $(x_i, y_i)$ pairs, return a list where the overlapping intervals are merged[cite: 1]. For $I = \{(1, 3), (2, 6), (8, 10), (7, 18)\}$ the output should be $\{(1, 6), (7, 18)\}$[cite: 1]. Your algorithm should run in worst-case $O(n \log n)$ time complexity[cite: 1]. By choosing a suitable input and output representation, write a program in C to validate your algorithm[cite: 1].

---

### Question 6: Application of Sorting-VI (Point of Maximum Interval Overlap)
You are given a set $S$ of $n$ intervals on a line, with the $i^{\text{th}}$ interval described by its left and right endpoints $(l_i, r_i)$[cite: 1]. Give an $O(n \log n)$ algorithm to identify a point $p$ on the line that is in the largest number of intervals[cite: 1]. As an example, for $S = \{(10, 40), (20, 60), (50, 90), (15, 70)\}$ no point exists in all four intervals, but $p = 50$ is an example of a point in three intervals[cite: 1]. You can assume an endpoint counts as being in its interval[cite: 1]. By choosing a suitable input and output representation, write a program in C to validate your algorithm[cite: 1].

# LAB 5: Sorting & Selection Algorithms

Implementation of selection and sorting algorithms in C, including file I/O operations.

## Contents
1. **`q1_median_quickselect.c`**: Find Median Without Sorting using QuickSelect.
2. **`q2_kth_smallest.c`**: Find K-th Smallest Element using QuickSelect.
3. **`q3_quicksort_file.c`**: QuickSort on $N$ Random Elements with File I/O.
4. **`q4_heapsort_file.c`**: Heap Sort on $N$ Random Elements with File I/O.

---

## 1. Find Median Without Sorting (QuickSelect)
- **Time Complexity:** Average $O(N)$, Worst $O(N^2)$
- **Space Complexity:** $O(1)$ auxiliary

## 2. Find K-th Smallest Element (QuickSelect)
- **Time Complexity:** Average $O(N)$, Worst $O(N^2)$
- **Space Complexity:** $O(1)$ iterative in-place

## 3. QuickSort on N Random Elements in a File
- **Time Complexity:** Average $O(N \log N)$, Worst $O(N^2)$
- **Space Complexity:** $O(\log N)$ stack space

## 4. Heap Sort on N Random Elements in a File
- **Time Complexity:** Guaranteed $O(N \log N)$ (Best, Average, Worst)
- **Space Complexity:** $O(1)$ auxiliary

 # Lab 6: Algorithmic Complexity and Advanced Operations

This repository contains the problem statements and C implementations for Lab 6. The focus is on analyzing the worst-case computational complexity for various 1D array, 2D matrix, convolution, and sorting operations.

---

## Question 1: 1D Array Operations and Complexities

Given an array with $n$ unsorted integer elements, determine the worst-case complexity of the following problems in terms of $n$:

*   **(i)** Finding the maximum element.
*   **(ii)** Finding the first and second largest elements.
*   **(iii)** Finding the mean.
*   **(iv)** Finding the median.
*   **(v)** Finding the standard deviation.
*   **(vi)** Finding the mode.
*   **(vii)** Removing all duplicates.
*   **(viii)** Reversing the elements of the array.
*   **(ix)** Partitioning the array with respect to a given random pivot element so that all elements less than the pivot appear after all the elements greater than or equal to the pivot.

**Task:** By choosing the proper input representation, write a program in C to validate your procedures and derive the corresponding complexity analysis.

---

## Question 2: 2D Square Matrix Operations and Complexities

Given square matrices with $n$ rows and $n$ columns, determine the worst-case computational complexity of the following matrix algorithms in terms of $n$:

*   **(i)** Matrix Addition.
*   **(ii)** Matrix Multiplication.
*   **(iii)** Finding if the given matrix is a zero matrix.
*   **(iv)** Finding if the given matrix is a symmetric matrix.
*   **(v)** Computing the determinant of the given matrix.
*   **(vi)** Transposing the matrix in situ (in place).
*   **(vii)** Finding the eigenvalue and eigenvector of the matrix.

**Task:** By choosing the proper input representation, write a program in C to validate your procedures and derive the corresponding complexity analysis.

---

## Question 3: Convolution Operation on Vectors

The convolution of two vectors $A$ and $B$ is a new vector $C$ such that:

$$ C[k] = \sum_{j=0}^{m-1} A[j] * B[k - j] $$

Assuming the lengths of $A$ and $B$ are $m$ and $n$, respectively, and the indexing of the vectors starts from 0, find an $O(n \log n)$ divide and conquer algorithm for this operation. Consider $n \geq m$ for your implementation and analysis.

**Task:** By choosing the proper input representation, write a program in C to validate your algorithm.

---

## Question 4: Sorting via Reversal Procedure

Suppose you are given a permutation $p$ of the integers $1$ to $n$, and seek to sort them to be in increasing order $[1, ..., n]$. The only operation at your disposal is `reverse(p, i, j)`, which reverses the elements of a subsequence $p_i, ..., p_j$ in the permutation. For example, for the permutation $[1, 4, 3, 2, 5]$, one reversal (of the second through fourth elements) suffices to sort it.

1.  **Mathematical Proof:** Show mathematically that it is possible to sort any permutation using $O(n)$ reversals.
2.  **Algorithm Design:** Now suppose that the cost of `reverse(p, i, j)` is equal to its length (the number of elements in the range, $|j - i| + 1$). Design an algorithm that sorts $p$ in $O(n \log^2 n)$ cost. 
3.  **Analysis:** Analyze the running time and cost of your algorithm and prove its correctness.

**Task:** Write a program in C to validate your algorithm supporting your analysis.

# Design and Analysis of Algorithm (DAA) - Lab 07

## 1. Invert the coin-triangle
Consider an equilateral triangle formed by closely packed pennies or other identical coins. (The centers of the coins are assumed to be at the points of the equilateral triangular lattice.) Design an algorithm to flip the triangle upside down in the minimum number of moves if on each move you can slide one coin at a time to its new position. Give a compact formula for the number of minimum moves.

**Task:** By choosing the proper input representation, write a program in C to validate your procedures and derive the complexity analysis of your algorithm.

---

## 2. Super egg testing experiment
A firm has invented a super-strong egg. For publicity purposes, it wants to determine the highest floor in a 100-storey building from which such an egg can fall without breaking. The firm has given a tester two identical eggs to experiment with. Of course, the same egg can be dropped multiple times unless it breaks. What is the minimum number of droppings that is guaranteed to determine the highest safe floor in all cases? Design a dynamic programming generalized solution for `E` eggs and `F` floors.

**Task:** By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## 3. Reve's puzzle
There are eight disks of different sizes and four pegs. Initially, all the disks are on the first peg in order of size, the largest on the bottom and the smallest on the top. The objective is to transfer all the disks to another peg by a sequence of moves. Only one disk can be moved at a time, and it is forbidden to place a larger disk on top of a smaller one. Devise an algorithm that solves the puzzle in 33 moves. Generalize your algorithm for an `n`-disk problem.

**Task:** By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## 4. Security switches
There is a row of `n` security switches protecting a military installation entrance. The switches can be manipulated as follows:
1. The rightmost switch may be turned on or off at will.
2. Any other switch may be turned on or off only if the switch to its immediate right is on and all the other switches to its right, if any, are off.
3. Only one switch may be toggled at a time.

**Task:** Devise an algorithm to turn off all the switches, which are initially all on, in the minimum number of moves. (Toggling one switch is considered one move.) By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## 5. Hitting a moving target
A computer game has a shooter and a moving target. The shooter can hit any of `n > 1` hiding spots located along a straight line in which the target can hide. The shooter can never see the target; all he knows is that the target moves to an adjacent hiding spot between every two consecutive shots. Design an algorithm that guarantees hitting the target or prove that no such algorithm exists.

**Task:** If any such algorithm exists, by choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## 6. The best time to be alive
An editor of *The History of the World Science* wants to find out the time when the largest number of prominent scientists were alive. The prominent scientists are, by definition, the people mentioned in the book with the dates of their birth and death. (No living scientists are included in the book.) Devise an algorithm for this task if it has the book's index as its input. The entries in the index are sorted alphabetically and give the persons' birth and death years. If a person A died the same year person B was born, assume that the former event happened before the latter one.

**Task:** By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## 7. Matrix Chain Multiplication (MCM) problem
Consider the matrix chain multiplication problem. 

**Task:** Write a program in C to implement the dynamic programming solution of the MCM problem in order to find the minimum number of scalar multiplications involved and the corresponding ordering to obtain the final result.
