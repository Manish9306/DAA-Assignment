/*Q1.Binary vs Ternary Search: In binary search, an n element list is divided into nearly two equal halves, 
while in ternary search, it is divided into nearly three equal intervals. Then the search will be in one of the
intervals. Design and implement a C program to search for an element x in a sorted list of size n using binary 
and ternary search. Justify and validate that binary search is better than ternary search via your implementation.*/

#include <stdio.h>

int binaryComparisons;
int ternaryComparisons;

int binarySearch(int arr[], int n, int x)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        binaryComparisons++;

        if (arr[mid] == x)
            return mid;

        binaryComparisons++;

        if (x < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    return -1;
}

int ternarySearch(int arr[], int n, int x)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int third = (high - low) / 3;

        int mid1 = low + third;
        int mid2 = high - third;

        ternaryComparisons++;

        if (arr[mid1] == x)
            return mid1;

        ternaryComparisons++;

        if (arr[mid2] == x)
            return mid2;

        ternaryComparisons++;

        if (x < arr[mid1])
        {
            high = mid1 - 1;
        }
        else if (x > arr[mid2])
        {
            low = mid2 + 1;
        }
        else
        {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }

    return -1;
}

int main()
{
    int sizes[] = {
        16, 32, 64, 128, 256,
        512, 1024, 2048, 4096, 8192
    };

    int numberOfSizes = 10;

    FILE *file = fopen("data.txt", "w");

    if (file == NULL)
    {
        printf("Error creating data.txt\n");
        return 1;
    }

    fprintf(file, "NumberOfElements BinaryComparisons TernaryComparisons\n");

    for (int s = 0; s < numberOfSizes; s++)
    {
        int n = sizes[s];

        int arr[n];

        for (int i = 0; i < n; i++)
            arr[i] = i + 1;

        /*
           Search for the last element.
           This gives both algorithms a substantial search.
        */
        int x = n;

        binaryComparisons = 0;
        ternaryComparisons = 0;

        int binaryResult = binarySearch(arr, n, x);
        int ternaryResult = ternarySearch(arr, n, x);

        fprintf(file, "%d %d %d\n",
                n,
                binaryComparisons,
                ternaryComparisons);

        printf("n = %d, Binary = %d, Ternary = %d\n",
               n,
               binaryComparisons,
               ternaryComparisons);

        if (binaryResult == -1 || ternaryResult == -1)
            printf("Search error.\n");
    }

    fclose(file);

    printf("\nData generated successfully.\n");
    printf("Data saved in data.txt\n");

    return 0;
}