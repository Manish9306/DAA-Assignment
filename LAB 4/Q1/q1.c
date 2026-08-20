/*1. Application of sorting-I: Assume that we are given n pairs of items as input, where the
first item is a number and the second item is one of three colours (red, blue, or yellow).
Further assume that the items are sorted by number. Give an O(n) algorithm to sort
the items by colour (all reds before all blues before all yellows) such that the numbers for
identical colours stay sorted. By choosing the proper input representation, write a program
in C to validate your algorithm.*/

/*======================================================================
STABLE COLOR SORT ALGORITHM
======================================================================

Input  : Array A of size n containing pairs of (number, color),
         pre-sorted in ascending order by number.
Output : Array A sorted such that all RED items come first, 
         followed by BLUE, then YELLOW, with the numerical order 
         preserved for matching colors.

----------------------------------------------------------------------
Intuitive 3-Step Idea:
----------------------------------------------------------------------
1. Count each color:
   - Count the total number of RED, BLUE, and YELLOW items.
   - Example: 3 Reds, 2 Blues, 2 Yellows.

2. Reserve slots in an output array:
   - RED section   : index 0 to 2
   - BLUE section  : index 3 to 4
   - YELLOW section: index 5 to 6

3. Place items from left to right:
   - Traverse the input list from start to finish.
   - Place each item into the next available spot in its section.
   - Copy the output array back to the original array.

----------------------------------------------------------------------
Formal Step-by-Step Algorithm:
----------------------------------------------------------------------
Step 1: Initialize counters:
        red_count = 0, blue_count = 0, yellow_count = 0

Step 2: Traverse array A from index 0 to n - 1:
        - If A[i].color == RED    -> red_count++
        - If A[i].color == BLUE   -> blue_count++
        - If A[i].color == YELLOW -> yellow_count++

Step 3: Calculate starting indices for the output array B:
        - red_index    = 0
        - blue_index   = red_count
        - yellow_index = red_count + blue_count

Step 4: Create a temporary array B of size n.

Step 5: Traverse array A from index 0 to n - 1 (left to right):
        - If A[i].color == RED:
            B[red_index] = A[i]
            red_index++
        - If A[i].color == BLUE:
            B[blue_index] = A[i]
            blue_index++
        - If A[i].color == YELLOW:
            B[yellow_index] = A[i]
            yellow_index++

Step 6: Copy all n elements from array B back to array A.

Step 7: Return sorted array A.
======================================================================*/

#include <stdio.h>

// Step 1: Define representation for Colors using simple numbers/enum
typedef enum {
    RED = 0,
    BLUE = 1,
    YELLOW = 2
} Color;

// Structure to represent each (number, color) pair
typedef struct {
    int number;
    Color color;
} Item;

// Helper function to print color names nicely
void printColor(Color c) {
    if (c == RED) printf("Red");
    else if (c == BLUE) printf("Blue");
    else if (c == YELLOW) printf("Yellow");
}

// Function to print the array of items
void displayArray(Item arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("(%d, ", arr[i].number);
        printColor(arr[i].color);
        printf(") ");
    }
    printf("\n");
}

// O(n) Stable Color Sort Function
void sortByColor(Item arr[], int n) {
    int red_count = 0, blue_count = 0, yellow_count = 0;

    // Pass 1: Count how many of each color we have
    for (int i = 0; i < n; i++) {
        if (arr[i].color == RED) {
            red_count++;
        } else if (arr[i].color == BLUE) {
            blue_count++;
        } else if (arr[i].color == YELLOW) {
            yellow_count++;
        }
    }

    // Determine the starting index for each color section
    int red_index = 0;
    int blue_index = red_count;
    int yellow_index = red_count + blue_count;

    // Temporary output array to place sorted items
    Item output[100]; // Fixed-size buffer suitable for 1st-year lab exercises

    // Pass 2: Traverse original array from left to right and place into buckets
    for (int i = 0; i < n; i++) {
        if (arr[i].color == RED) {
            output[red_index] = arr[i];
            red_index++;
        } else if (arr[i].color == BLUE) {
            output[blue_index] = arr[i];
            blue_index++;
        } else if (arr[i].color == YELLOW) {
            output[yellow_index] = arr[i];
            yellow_index++;
        }
    }

    // Copy sorted elements back to original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

int main() {
    // Input list (must be sorted by number initially)
    Item arr[] = {
        {1, BLUE},
        {2, RED},
        {3, YELLOW},
        {4, RED},
        {5, YELLOW},
        {6, BLUE},
        {7, RED}
    };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Input Array (Sorted by Number):\n");
    displayArray(arr, n);

    // Call the sorting function
    sortByColor(arr, n);

    printf("\nOutput Array (Sorted by Color, Numbers remain sorted):\n");
    displayArray(arr, n);

    return 0;
}

/*======================================================================
TIME COMPLEXITY ANALYSIS
======================================================================

Overall Time Complexity: O(n) [Linear Time]

----------------------------------------------------------------------
Step-by-Step Breakdown:
----------------------------------------------------------------------

1. Variable Initialization:
   - Initializing variables (red_count, blue_count, etc.) takes constant time:
     Time = O(1)

2. Pass 1 (Counting Frequencies):
   - A single for-loop runs n times (i = 0 to n-1).
   - Inside the loop, checking the color and incrementing counter takes O(1).
     Time = O(n)

3. Calculating Starting Positions:
   - Simple addition to find red_index, blue_index, yellow_index takes constant time:
     Time = O(1)

4. Pass 2 (Placing Elements into Output Array):
   - A single for-loop runs n times (i = 0 to n-1).
   - Placing the element at the calculated index and incrementing takes O(1).
     Time = O(n)

5. Pass 3 (Copying Output Array back to Original Array):
   - A single for-loop runs n times to copy elements back.
     Time = O(n)

----------------------------------------------------------------------
Total Time Complexity Calculation:
----------------------------------------------------------------------

Total Time = O(1) + O(n) + O(1) + O(n) + O(n)
           = O(3n + 2)
           = O(n)

----------------------------------------------------------------------
Final Verdict:
----------------------------------------------------------------------
- Worst-Case Time Complexity   : O(n)
- Best-Case Time Complexity    : O(n)
- Average-Case Time Complexity : O(n)

Reason: The algorithm makes 3 independent linear passes over the array of size n 
with no nested loops, ensuring strictly O(n) runtime.
======================================================================*/