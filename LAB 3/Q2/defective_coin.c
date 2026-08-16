/*Q2.Search the Defective Coin: Imagine you are working as the quality-control engineer for a company that makes
coins. The company needs to certify that all the coins must have exactly identical weights. During your inspection,
you have observed that one of the workers is watching the mobile phone while giving final shape to a coin. 
When you confront the worker suddenly, in reflex, he dropped that one coin into a pile of other (n−1) perfectly
identical weighted coins. After your confrontation, the worker agreed that he was not attentive and had been
shaping the coin for more than the desired duration. However, he could not be sure whether the weight of the 
coin was less due to excessive shaping or remained perfect, but certain that the weight of the coin must not be 
more than the required weight. It is your job to find that one possible defective coin that is lighter than the 
others or possibly none, if, fortunately, the worker has made the perfect coin with exact required weight.

Being a Computer science graduate, your task is to determine which of the coins is lighter (defective) or 
report that none is lighter. In order to accomplish this task, you have been provided with a balance weighing 
scale . Using the balance weighing scale and necessary implementation, provide a divide and conquer algorithm to 
find the lighter (defective) coin, if present or not, in log2 n + c time, forsomepositive constant c.*/

#include <stdio.h>

int comparisons;

int findDefective(int coins[], int left, int right)
{
    if (left == right)
    {
        comparisons++;
        
        if (coins[left] < 10)
            return left;
        else
            return -1;
    }

    int mid = (left + right) / 2;

    int leftWeight = 0;
    int rightWeight = 0;

    for (int i = left; i <= mid; i++)
        leftWeight += coins[i];

    for (int i = mid + 1; i <= right; i++)
        rightWeight += coins[i];

    comparisons++;

    if (leftWeight < rightWeight)
        return findDefective(coins, left, mid);

    else if (rightWeight < leftWeight)
        return findDefective(coins, mid + 1, right);

    else
        return -1;
}

int main()
{
    int sizes[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    int numberOfSizes = 10;

    FILE *file = fopen("data.txt", "w");

    if (file == NULL)
    {
        printf("Error creating data.txt\n");
        return 1;
    }

    fprintf(file, "NumberOfCoins Comparisons\n");

    for (int s = 0; s < numberOfSizes; s++)
    {
        int n = sizes[s];

        int coins[n];

        for (int i = 0; i < n; i++)
            coins[i] = 10;

        coins[n - 1] = 9;

        comparisons = 0;

        findDefective(coins, 0, n - 1);

        fprintf(file, "%d %d\n", n, comparisons);
    }

    fclose(file);

    printf("Data generated successfully.\n");
    printf("Data saved in data.txt\n");

    return 0;
}