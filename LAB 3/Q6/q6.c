/*q6.Use of loop invariants in sorting: Generally, loop invariants are used to prove an algorithm’s correctness. 
To validate the proof, one must show three things about a loop invariant: initialisation, maintenance, and 
termination. Consider sorting on n numbers stored in an array A[1···n] by first finding the smallest element of 
A[1···n] and exchanging it with the element in A[1]. Then, find the smallest element of A[2···n], and exchange it 
with A[2]. Then, find the smallest element of A[3···n], and exchange it with A[3]. Continue in this manner for the 
first (n − 1) elements of A. Write a pseudocode for this algorithm. What loop invariant does this algorithm maintain?
Why does it need to run for only the first (n −1) elements, rather than for all n elements? Give the worst-case 
running time of the above sorting algorithm in Θ-notation. Is the best-case running time any better? Finally, 
implement your algorithm in C to validate your claim.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparisons = 0;
long long swaps = 0;


/*
    Selection Sort
*/
void selectionSort(int arr[], int n)
{
    int i, j, minIndex, temp;

    for (i = 0; i < n - 1; i++)
    {
        minIndex = i;

        /*
            Find the smallest element
            in the unsorted portion.
        */
        for (j = i + 1; j < n; j++)
        {
            comparisons++;

            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        /*
            Exchange A[i] with A[minIndex]
        */
        if (minIndex != i)
        {
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;

            swaps++;
        }
    }
}


/*
    Generate random array
*/
void generateRandomArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100000;
    }
}


/*
    Generate sorted array
*/
void generateSortedArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }
}


/*
    Generate reverse sorted array
*/
void generateReverseArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = n - i;
    }
}


int main()
{
    FILE *fp;

    /*
        Different input sizes
    */
    int sizes[] = {
        10,
        20,
        50,
        100,
        200,
        500,
        1000,
        2000,
        5000,
        10000
    };

    int numberOfSizes =
        sizeof(sizes) / sizeof(sizes[0]);


    /*
        Open CSV file
    */
    fp = fopen("selection_sort_data.csv", "w");

    if (fp == NULL)
    {
        printf("Error opening CSV file.\n");
        return 1;
    }


    /*
        CSV header
    */
    fprintf(
        fp,
        "n,best_case,worst_case,average_case,theoretical\n"
    );


    srand((unsigned int)time(NULL));


    printf("\n");
    printf("Selection Sort - Loop Invariant Validation\n");
    printf("===========================================\n\n");

    printf(
        "%8s %15s %15s %15s %15s\n",
        "n",
        "Best Case",
        "Worst Case",
        "Average",
        "Theoretical"
    );


    for (int s = 0; s < numberOfSizes; s++)
    {
        int n = sizes[s];


        /*
            Allocate three arrays
        */
        int *bestArray =
            (int *)malloc(n * sizeof(int));

        int *worstArray =
            (int *)malloc(n * sizeof(int));

        int *averageArray =
            (int *)malloc(n * sizeof(int));


        if (bestArray == NULL ||
            worstArray == NULL ||
            averageArray == NULL)
        {
            printf(
                "Memory allocation failed for n = %d\n",
                n
            );

            fclose(fp);

            return 1;
        }


        /*
            Best case:
            Already sorted array
        */
        generateSortedArray(bestArray, n);


        /*
            Worst case:
            Reverse sorted array
        */
        generateReverseArray(worstArray, n);


        /*
            Average case:
            Random array
        */
        generateRandomArray(averageArray, n);


        /*
            -------------------------
            BEST CASE
            -------------------------
        */
        comparisons = 0;
        swaps = 0;

        selectionSort(bestArray, n);

        long long bestComparisons =
            comparisons;


        /*
            -------------------------
            WORST CASE
            -------------------------
        */
        comparisons = 0;
        swaps = 0;

        selectionSort(worstArray, n);

        long long worstComparisons =
            comparisons;


        /*
            -------------------------
            AVERAGE CASE
            -------------------------
        */
        comparisons = 0;
        swaps = 0;

        selectionSort(averageArray, n);

        long long averageComparisons =
            comparisons;


        /*
            Theoretical number of comparisons:

                n(n-1)/2
        */
        long long theoretical =
            ((long long)n * (n - 1)) / 2;


        /*
            Display results
        */
        printf(
            "%8d %15lld %15lld %15lld %15lld\n",
            n,
            bestComparisons,
            worstComparisons,
            averageComparisons,
            theoretical
        );


        /*
            Save results to CSV
        */
        fprintf(
            fp,
            "%d,%lld,%lld,%lld,%lld\n",
            n,
            bestComparisons,
            worstComparisons,
            averageComparisons,
            theoretical
        );


        free(bestArray);
        free(worstArray);
        free(averageArray);
    }


    fclose(fp);


    printf(
        "\nData successfully saved to "
        "selection_sort_data.csv\n"
    );

    return 0;
}