/*
Question 10: [Greedy Superstring Conjecture] (Open Unsolved Problem)
Given a set of n strings S = {s1, s2, ..., sn}, find the shortest single string
that contains every si as a substring. You are advised to explore more on this
problem to develop an insight.

Background and current status of the conjecture:
The conjecture formulated nearly four decades ago hypothesised that the classic
greedy algorithm (repeatedly merging the pair with the maximum overlap) always
yields a superstring no more than twice the length of the optimal solution
(2-approximation).
A September 2026 paper titled "Disproving the Greedy Superstring Conjecture"
published on ArXiV demonstrated that the approximation ratio for instances where
input strings have an even length k >= 10 is at least (9k + 2) / (4k + 4),
establishing a limit of 9/4 (2.25) as k -> infinity. This conclusively disproves
the long-standing 2-approximation claim.

Algorithm:
1. First eliminate any string that is already a substring of another string.
2. While more than one string remains in the collection:
   - For every pair of strings (i, j), calculate maximum suffix-prefix overlap.
   - Pick the pair (i, j) that gives the largest overlap.
   - Merge them by appending string j (excluding the overlapping prefix) to string i.
   - Delete string j from the collection.
3. The remaining string is our greedy superstring.

Time Complexity:
- Pairwise overlap calculation: O(n^2 * L) where L is max string length
- Merging over n-1 iterations: O(n^3 * L)
Overall Time Complexity: O(n^3 * L)
Space Complexity: O(n * L)
*/

#include <stdio.h>
#include <string.h>

// calculates maximum overlap where suffix of a matches prefix of b
int getOverlap(char a[], char b[]) {
    int lenA = strlen(a);
    int lenB = strlen(b);
    int maxOv = lenA < lenB ? lenA : lenB;

    for (int ov = maxOv; ov >= 1; ov--) {
        if (strncmp(a + lenA - ov, b, ov) == 0) {
            return ov;
        }
    }
    return 0;
}

int main() {
    int n, i, j;
    char str[20][300];
    int active[20];

    printf("Enter number of strings: ");
    scanf("%d", &n);

    printf("Enter %d strings:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%s", str[i]);
        active[i] = 1;
    }

    // eliminate duplicate/contained strings
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j && active[i] && active[j]) {
                if (strstr(str[j], str[i]) != NULL && strlen(str[i]) <= strlen(str[j])) {
                    active[i] = 0;
                    break;
                }
            }
        }
    }

    int remaining = 0;
    for (i = 0; i < n; i++) {
        if (active[i]) remaining++;
    }

    while (remaining > 1) {
        int bestI = -1, bestJ = -1;
        int maxOverlap = -1;

        for (i = 0; i < n; i++) {
            if (!active[i]) continue;
            for (j = 0; j < n; j++) {
                if (i != j && active[j]) {
                    int ov = getOverlap(str[i], str[j]);
                    if (ov > maxOverlap) {
                        maxOverlap = ov;
                        bestI = i;
                        bestJ = j;
                    }
                }
            }
        }

        // merge bestJ onto end of bestI
        strcat(str[bestI], str[bestJ] + maxOverlap);
        active[bestJ] = 0;
        remaining--;
    }

    int ansIdx = 0;
    for (i = 0; i < n; i++) {
        if (active[i]) {
            ansIdx = i;
            break;
        }
    }

    printf("\nGreedy shortest superstring: %s\n", str[ansIdx]);
    printf("Length of superstring: %d\n", (int)strlen(str[ansIdx]));

    return 0;
}
