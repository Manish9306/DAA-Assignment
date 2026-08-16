/*Q3.Max and Min using D&C Approach: Using the divide and conquer approach, 
develop an algorithm to find the maximum and minimum elements in an array of size n so that the 
number of comparisonswill be bounded by 3n 2 . Implement your algorithm in C to validate the result.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int min;
    int max;
} MinMax;

long long comparisons;

/* Divide and Conquer function */
MinMax findMinMax(int arr[], int low, int high)
{
    MinMax result, left, right;
    int mid;

    /* Only one element */
    if (low == high)
    {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }

    /* Two elements */
    if (high == low + 1)
    {
        comparisons++;

        if (arr[low] < arr[high])
        {
            result.min = arr[low];
            result.max = arr[high];
        }
        else
        {
            result.min = arr[high];
            result.max = arr[low];
        }

        return result;
    }

    /* Divide */
    mid = (low + high) / 2;

    /* Conquer */
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);

    /* Combine - compare maximums */
    comparisons++;

    if (left.max > right.max)
        result.max = left.max;
    else
        result.max = right.max;

    /* Combine - compare minimums */
    comparisons++;

    if (left.min < right.min)
        result.min = left.min;
    else
        result.min = right.min;

    return result;
}

int main()
{
    FILE *fp;
    int sizes[] = {
        10, 20, 50, 100, 200,
        500, 1000, 2000, 5000,
        10000, 20000
    };

    int numberOfSizes = sizeof(sizes) / sizeof(sizes[0]);

    fp = fopen("max_min_data.csv", "w");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    /* CSV header */
    fprintf(fp, "n,comparisons,theoretical_bound\n");

    srand((unsigned int)time(NULL));

    printf("Max-Min using Divide and Conquer\n");
    printf("----------------------------------\n");
    printf("%10s %15s %20s\n",
           "n", "Comparisons", "3n/2 Bound");

    for (int s = 0; s < numberOfSizes; s++)
    {
        int n = sizes[s];

        int *arr = (int *)malloc(n * sizeof(int));

        if (arr == NULL)
        {
            printf("Memory allocation failed for n = %d\n", n);
            fclose(fp);
            return 1;
        }

        /* Generate random data */
        for (int i = 0; i < n; i++)
        {
            arr[i] = rand() % 100000;
        }

        comparisons = 0;

        /* Execute Divide and Conquer algorithm */
        MinMax result = findMinMax(arr, 0, n - 1);

        double theoreticalBound = 1.5 * n;

        printf("%10d %15lld %20.2f\n",
               n, comparisons, theoreticalBound);

        /* Save data to CSV */
        fprintf(fp, "%d,%lld,%.2f\n",
                n, comparisons, theoreticalBound);

        free(arr);
    }

    fclose(fp);

    printf("\nData successfully saved to max_min_data.csv\n");

    return 0;
}