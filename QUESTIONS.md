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
