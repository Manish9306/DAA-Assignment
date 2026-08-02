# Algorithm

1. **Define Data Structure:** Create a `Function` structure that holds two variables: a string for the mathematical expression's name, and a `double` for its assigned numerical `growth_score`.
2. **Define Comparator:** Create a `compare` function that takes two `Function` elements. It extracts their `growth_score`s and returns `1` if the first is greater, `-1` if the first is smaller, and `0` if they are equal.
3. **Initialize Data:** In the `main` function, create an array of `Function` structs. Populate this array with the mathematical expressions and their corresponding pre-calculated growth scores (based on their Big-O asymptotic growth limits).
4. **Determine Size:** Calculate the number of elements in the array by dividing the total size of the array by the size of a single element (`sizeof(funcs) / sizeof(funcs[0])`).
5. **Sort:** Call C's built-in `qsort()` function, passing in the array, the number of elements, the size of one element, and the custom `compare` function.
6. **Output:** Iterate through the sorted array using a `for` loop and print the name of each function in its new, increasing order of growth.

---

# Complexity

* **Time Complexity:** **O(N log N)** — Dominated by the `qsort()` standard library function, where *N* is the number of functions in the array.
* **Space Complexity:** **O(N)** — Auxiliary space required for storing the array of `Function` structs in memory.
