/*
 * Lab 10 - Question 2: Dynamic Connected Components in a Grid (Number of Islands II)
 * 
 * Problem Statement:
 * Given an R x C grid initially completely filled with water, land cells are added
 * one by one at positions (r1, c1), (r2, c2), ..., (rk, ck). After each operation,
 * output the current number of 4-directionally connected land components (islands).
 * By choosing the proper input representation, write a program in C to validate your
 * algorithm and derive the complexity analysis of your algorithm.
 * 
 * [Hint: This is the Dynamic Connected Components in a Grid (commonly known as Number
 * of Islands II), which can be solved using a Disjoint Set Union (DSU / Union-Find)
 * data structure with coordinate flattening.]
 *
 * Algorithm:
 * 1. Coordinate Flattening:
 *    Map 2D coordinates (r, c) of the R x C grid to unique 1D integers:
 *      index = r * C + c  (where 0 <= r < R, 0 <= c < C).
 * 2. Data Structure:
 *    - Maintain a 1D DSU with parent[] and rankArr[] for R * C elements.
 *    - Maintain a grid[] array where 0 = water and 1 = land.
 *    - Maintain a counter `islands` initialized to 0.
 * 3. Dynamic Land Addition:
 *    When adding a land cell at (r, c):
 *    - Compute id = r * C + c.
 *    - If grid[id] is already 1, the count of islands is unchanged.
 *    - Otherwise:
 *        a. Mark grid[id] = 1, initialize parent[id] = id, and increment islands++.
 *        b. Check the 4 orthogonal neighbors: (r-1, c), (r+1, c), (r, c-1), (r, c+1).
 *        c. For each neighbor (nr, nc) within grid bounds where grid[nid] == 1:
 *           If find(id) != find(nid), unite them and decrement islands--.
 *    - Output the updated island count after each step.
 *
 * Complexity Analysis:
 * - Time Complexity:
 *   - Grid and DSU Initialization: O(R * C) to allocate and initialize arrays.
 *   - Per Land Addition: Inspects at most 4 neighbors. For each adjacent land cell,
 *     find and unite take amortized O(alpha(R * C)) time using path compression
 *     and union by rank.
 *   - Total Time for K operations: O(R * C + K * alpha(R * C)) ~ O(R * C + K).
 * - Space Complexity:
 *   - O(R * C) auxiliary space for DSU parent, rank, and grid state arrays.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int *parent;
int *rankArr;

int find(int i) {
    if (parent[i] != i) {
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

bool unite(int i, int j) {
    int rootI = find(i);
    int rootJ = find(j);
    if (rootI == rootJ) return false;

    if (rankArr[rootI] < rankArr[rootJ]) {
        parent[rootI] = rootJ;
    } else if (rankArr[rootI] > rankArr[rootJ]) {
        parent[rootJ] = rootI;
    } else {
        parent[rootJ] = rootI;
        rankArr[rootI]++;
    }
    return true;
}

int main(void) {
    int R, C, K;
    printf("Enter rows (R), columns (C) and operations (K): ");
    if (scanf("%d %d %d", &R, &C, &K) != 3 || R <= 0 || C <= 0) {
        return 1;
    }

    int totalCells = R * C;
    parent = (int*)malloc(totalCells * sizeof(int));
    rankArr = (int*)calloc(totalCells, sizeof(int));
    int *grid = (int*)calloc(totalCells, sizeof(int));

    for (int i = 0; i < totalCells; i++) {
        parent[i] = -1;
    }

    int islands = 0;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    printf("Enter %d operations (r c):\n", K);
    for (int step = 1; step <= K; step++) {
        int r, c;
        if (scanf("%d %d", &r, &c) != 2) break;

        if (r < 0 || r >= R || c < 0 || c >= C) {
            printf("Invalid cell (%d, %d)\n", r, c);
            continue;
        }

        int id = r * C + c;

        if (grid[id] == 1) {
            printf("Step %d: Added (%d, %d) -> Islands: %d\n", step, r, c, islands);
            continue;
        }

        grid[id] = 1;
        parent[id] = id;
        islands++;

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                int nid = nr * C + nc;
                if (grid[nid] == 1) {
                    if (unite(id, nid)) {
                        islands--;
                    }
                }
            }
        }

        printf("Step %d: Added (%d, %d) -> Islands: %d\n", step, r, c, islands);
    }

    free(parent);
    free(rankArr);
    free(grid);
    return 0;
}
