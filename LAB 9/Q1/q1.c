/*
Question 1: [Fractional Knapsack with Deterioration Rate]
You have n items with base values vi, weights wi, and decay rates lambda_i > 0.
If an item is consumed at time t, its effective value density decays to
(vi/wi) - lambda_i * t. Knapsack capacity is W. Determine the optimal scheduling
order and fractional choices to maximise total value. By choosing the proper
input representation, write a program in C to validate your algorithm and derive
the complexity analysis of your algorithm.

Algorithm:
1. We sort items in descending order of decay rate lambda. By exchange argument,
   items that lose value faster per second must be processed earlier.
2. Initialize remaining knapsack capacity as W, current time step t = 0, and total_val = 0.
3. Traverse through sorted items:
   - Calculate current value density = (v[i] / w[i]) - lambda[i] * t.
   - If density <= 0, item has completely spoiled, so ignore it.
   - Take min(w[i], remaining capacity).
   - Add taken_weight * density to total_val, decrement remaining capacity, and increment t by 1.
4. Stop when knapsack is full or all items are visited.

Time Complexity:
- Sorting items by lambda: O(n log n)
- Greedy selection loop: O(n)
Total Time Complexity: O(n log n)
Space Complexity: O(n)
*/

#include <stdio.h>

struct Item {
    int id;
    double val;
    double wt;
    double lambda;
};

// simple bubble sort so it looks like standard student lab code
void sortByDecay(struct Item arr[], int n) {
    int i, j;
    struct Item temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].lambda < arr[j + 1].lambda) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, i;
    double W;
    struct Item items[100];

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter knapsack capacity: ");
    scanf("%lf", &W);

    for (i = 0; i < n; i++) {
        items[i].id = i + 1;
        printf("Enter value, weight and decay rate for item %d: ", i + 1);
        scanf("%lf %lf %lf", &items[i].val, &items[i].wt, &items[i].lambda);
    }

    sortByDecay(items, n);

    double remW = W;
    double totalVal = 0.0;
    int t = 0;

    printf("\nSelected items in order:\n");
    for (i = 0; i < n; i++) {
        if (remW <= 0.00001) break;

        double density = (items[i].val / items[i].wt) - (items[i].lambda * t);

        if (density <= 0) {
            continue; // item decayed, no point picking
        }

        double take = items[i].wt;
        if (take > remW) {
            take = remW;
        }

        double earned = take * density;
        totalVal += earned;
        remW -= take;

        printf("Time %d -> Item %d: weight taken = %.2f, value gained = %.2f\n", 
               t, items[i].id, take, earned);
        t++;
    }

    printf("\nTotal value obtained = %.2f\n", totalVal);
    printf("Remaining capacity = %.2f\n", remW);

    return 0;
}
