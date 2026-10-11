/*
Question 6: [Reorganise String with K-Distance Apart]
Given a string S and an integer K, rearrange S such that the same characters are
at least distance K apart. If impossible, return an empty string. By choosing the
proper input representation, write a program in C to validate your algorithm and
derive the complexity analysis of your algorithm.

Algorithm:
1. Count the occurrences of each letter in the string.
2. We need to fill positions from index 0 to len - 1.
3. For each position, greedily pick the character with the maximum remaining
   frequency whose last used position was at least K indices ago.
4. If for any position no character is valid to place, it is impossible to rearrange.
5. Place the chosen character, decrease its count, update its last used index,
   and move to the next position.

Time Complexity:
- Counting frequencies: O(n)
- Greedy selection: n positions * alphabet size 26 = O(26 * n) = O(n)
Overall Time Complexity: O(n)
Space Complexity: O(1) extra space since alphabet size is 26
*/

#include <stdio.h>
#include <string.h>

int main() {
    char s[500];
    int k;

    printf("Enter string: ");
    scanf("%s", s);

    printf("Enter distance k: ");
    scanf("%d", &k);

    int n = strlen(s);
    int count[26] = {0};
    int lastPos[26];

    for (int i = 0; i < 26; i++) {
        lastPos[i] = -100000; // initialize to far away
    }

    for (int i = 0; i < n; i++) {
        count[s[i] - 'a']++;
    }

    char res[500];
    int possible = 1;

    for (int pos = 0; pos < n; pos++) {
        int bestChar = -1;
        int maxFreq = 0;

        // pick available character with highest remaining count
        for (int c = 0; c < 26; c++) {
            if (count[c] > 0 && (pos - lastPos[c]) >= k) {
                if (count[c] > maxFreq) {
                    maxFreq = count[c];
                    bestChar = c;
                }
            }
        }

        if (bestChar == -1) {
            possible = 0;
            break;
        }

        res[pos] = 'a' + bestChar;
        count[bestChar]--;
        lastPos[bestChar] = pos;
    }

    res[n] = '\0';

    if (possible) {
        printf("Rearranged string: %s\n", res);
    } else {
        printf("Not possible to rearrange with distance %d.\n", k);
    }

    return 0;
}
