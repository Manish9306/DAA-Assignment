/*
Question 2: [Huffman Coding]
Given symbol frequencies, construct a prefix-free binary code of minimum expected
length, and output the canonical Huffman codebook (where codes are ordered
lexicographically by length). By choosing the proper input representation, write
a program in C to validate your algorithm and derive the complexity analysis of
your algorithm.

Algorithm:
1. Count or take input of frequencies for each symbol.
2. Build Huffman tree using two minimum nodes at each step until 1 tree remains.
3. Compute code lengths for each leaf node by finding tree depth.
4. Sort symbols first by code length, and for ties, alphabetically (canonical rule).
5. Generate canonical binary codes using the prefix shift rule:
   - First code is 0 with its bit length.
   - Next code = (previous code + 1) shifted left by (len_diff).
6. Print codebook table and calculate average length.

Time Complexity:
- Finding min nodes repeatedly: O(n^2) or O(n log n) with heap
- Sorting code lengths: O(n log n)
- Code generation: O(n)
Overall Time Complexity: O(n log n)
Space Complexity: O(n)
*/

#include <stdio.h>
#include <string.h>

struct Node {
    char ch;
    int freq;
    int left;
    int right;
};

struct CodeEntry {
    char ch;
    int len;
    int code;
};

struct Node tree[200];
int treeSize = 0;
int isUsed[200];

int getMinNode(int total) {
    int minIdx = -1;
    int minVal = 9999999;
    for (int i = 0; i < total; i++) {
        if (!isUsed[i] && tree[i].freq < minVal) {
            minVal = tree[i].freq;
            minIdx = i;
        }
    }
    if (minIdx != -1) {
        isUsed[minIdx] = 1;
    }
    return minIdx;
}

void getCodeLengths(int root, int depth, int lengths[]) {
    if (root == -1) return;
    if (tree[root].left == -1 && tree[root].right == -1) {
        lengths[root] = (depth == 0) ? 1 : depth;
        return;
    }
    getCodeLengths(tree[root].left, depth + 1, lengths);
    getCodeLengths(tree[root].right, depth + 1, lengths);
}

void printBinary(int num, int len) {
    for (int i = len - 1; i >= 0; i--) {
        if ((num >> i) & 1)
            printf("1");
        else
            printf("0");
    }
}

int main() {
    int n, i, j;
    char chars[50];
    int freqs[50];

    printf("Enter number of distinct characters: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter char and frequency (%d): ", i + 1);
        scanf(" %c %d", &chars[i], &freqs[i]);
        tree[i].ch = chars[i];
        tree[i].freq = freqs[i];
        tree[i].left = -1;
        tree[i].right = -1;
        isUsed[i] = 0;
    }
    treeSize = n;

    // merge two lowest frequency nodes
    for (i = 0; i < n - 1; i++) {
        int left = getMinNode(treeSize);
        int right = getMinNode(treeSize);

        tree[treeSize].ch = '$';
        tree[treeSize].freq = tree[left].freq + tree[right].freq;
        tree[treeSize].left = left;
        tree[treeSize].right = right;
        isUsed[treeSize] = 0;
        treeSize++;
    }

    int root = treeSize - 1;
    int lengths[100] = {0};
    getCodeLengths(root, 0, lengths);

    struct CodeEntry list[50];
    for (i = 0; i < n; i++) {
        list[i].ch = chars[i];
        list[i].len = lengths[i];
        list[i].code = 0;
    }

    // sort canonically: first by length asc, then by char asc
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            int swapNeeded = 0;
            if (list[j].len > list[j + 1].len) {
                swapNeeded = 1;
            } else if (list[j].len == list[j + 1].len && list[j].ch > list[j + 1].ch) {
                swapNeeded = 1;
            }
            if (swapNeeded) {
                struct CodeEntry tmp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = tmp;
            }
        }
    }

    // canonical code assignment
    list[0].code = 0;
    for (i = 1; i < n; i++) {
        list[i].code = (list[i - 1].code + 1) << (list[i].len - list[i - 1].len);
    }

    printf("\n--- Canonical Huffman Codes ---\n");
    printf("Char\tLength\tCode\n");
    for (i = 0; i < n; i++) {
        printf("%c\t%d\t", list[i].ch, list[i].len);
        printBinary(list[i].code, list[i].len);
        printf("\n");
    }

    return 0;
}
