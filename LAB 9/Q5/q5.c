/*
Question 5: [Candy Distribution Problem (Bi-directional Slope Greedy)]
n children stand in a line, each assigned a rating. Each child must get at least
one candy. Children with a higher rating than their immediate neighbours must get
more candies than their neighbours. Find the minimum total number of candies needed.
By choosing the proper input representation, write a program in C to validate your
algorithm and derive the complexity analysis of your algorithm.

Algorithm:
1. Initialize a candies array where every child initially gets 1 candy.
2. Left-to-right pass:
   - For i from 1 to n - 1:
   - If rating[i] > rating[i - 1], then candies[i] = candies[i - 1] + 1.
3. Right-to-left pass:
   - For i from n - 2 down to 0:
   - If rating[i] > rating[i + 1] and candies[i] <= candies[i + 1],
     then candies[i] = candies[i + 1] + 1.
4. Add all values in the candies array to find the total minimum candies.

Time Complexity:
- Left pass: O(n)
- Right pass: O(n)
- Total sum: O(n)
Overall Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <stdio.h>

int main() {
    int n, i;
    int ratings[100];
    int candies[100];

    printf("Enter number of children: ");
    scanf("%d", &n);

    printf("Enter ratings for %d children: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &ratings[i]);
        candies[i] = 1; // base condition: everyone gets at least 1 candy
    }

    // left to right check
    for (i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    // right to left check
    for (i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            if (candies[i] <= candies[i + 1]) {
                candies[i] = candies[i + 1] + 1;
            }
        }
    }

    int total = 0;
    printf("\nFinal distribution:\n");
    for (i = 0; i < n; i++) {
        printf("Child %d (Rating %d): %d candies\n", i + 1, ratings[i], candies[i]);
        total += candies[i];
    }

    printf("\nTotal minimum candies needed: %d\n", total);

    return 0;
}
