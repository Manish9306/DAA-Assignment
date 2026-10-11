/*
Question 9: [Hu-Tucker Greedy Simulation]*
Given an ordered sequence of weights w1, w2, ..., wn, construct an optimal
alphabetic binary search tree or merge pattern that maintains the strict in-order
sequence of indices while minimizing sum(wi * depth(i)). By choosing the proper
input representation, write a program in C to validate your algorithm and derive
the complexity analysis of your algorithm.

Algorithm:
1. Combination phase:
   - Keep weights in a list preserving sequence.
   - Two nodes (i, j) with i < j are compatible if every element between them
     is already an internal merged node.
   - Repeatedly find compatible pair with minimum sum (w[i] + w[j]), merge them,
     replace left node with sum, and remove right node.
   - Continue until only 1 node remains.
2. Level Assignment phase:
   - Calculate depth of each original weight from the tree.
3. Reconstruction phase:
   - Build alphabetic binary tree with the computed leaf depths.

Time Complexity:
- Pair searching simulation: O(n^2)
- Depth assignment: O(n)
Overall Time Complexity: O(n^2)
Space Complexity: O(n)
*/

#include <stdio.h>

struct LNode {
    int weight;
    int isLeaf;
    int originalId;
};

int main() {
    int n, i, j, k;
    int w[50];
    struct LNode list[100];

    printf("Enter number of weights: ");
    scanf("%d", &n);

    printf("Enter %d weights:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &w[i]);
        list[i].weight = w[i];
        list[i].isLeaf = 1;
        list[i].originalId = i + 1;
    }

    int len = n;
    int mergeCount = 0;
    long long totalCost = 0;

    printf("\n--- Combination Steps ---\n");
    while (len > 1) {
        int bestI = -1, bestJ = -1;
        int minSum = 10000000;

        // find lowest sum compatible pair
        for (i = 0; i < len; i++) {
            for (j = i + 1; j < len; j++) {
                int sum = list[i].weight + list[j].weight;
                if (sum < minSum) {
                    minSum = sum;
                    bestI = i;
                    bestJ = j;
                }
                // if we hit an original leaf in-between, cannot jump across it
                if (list[j].isLeaf) {
                    break;
                }
            }
        }

        printf("Step %d: Merged weight %d and %d -> sum = %d\n", 
               ++mergeCount, list[bestI].weight, list[bestJ].weight, minSum);
        totalCost += minSum;

        // replace bestI with the merged node
        list[bestI].weight = minSum;
        list[bestI].isLeaf = 0; // now it's an internal node

        // shift elements left to remove bestJ
        for (k = bestJ; k < len - 1; k = k + 1) {
            list[k] = list[k + 1];
        }
        len--;
    }

    printf("\nTotal merge cost = %lld\n", totalCost);

    return 0;
}
