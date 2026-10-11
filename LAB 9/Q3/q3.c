/*
Question 3: [Minimum Initial Fuel (Reverse Greedy)]
A vehicle needs to reach the target D starting with fuel F. Along the way are
stations (di, fi) (distance from origin and refuel amount). What is the minimum
number of refuelling stops required to reach the target? By choosing the proper
input representation, write a program in C to validate your algorithm and derive
the complexity analysis of your algorithm.

Algorithm:
1. Sort fuel stations in ascending order of their distances from origin.
2. Maintain available fuel and keep moving forward from the current position.
3. Keep track of all gas stations that we have already crossed but haven't used yet.
4. If fuel is not enough to reach the next station (or target D), greedily pick the
   station with maximum fuel from our passed-by pool.
5. If pool is empty and we still cannot reach the next mark, it is impossible.
6. Count how many times we had to take fuel.

Time Complexity:
- Sorting stations: O(n log n)
- Greedy selection: O(n log n) with priority queue or O(n^2) with array pool
Overall Time Complexity: O(n^2) or O(n log n)
Space Complexity: O(n)
*/

#include <stdio.h>

struct Station {
    int dist;
    int fuel;
};

void sortStations(struct Station s[], int n) {
    int i, j;
    struct Station temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (s[j].dist > s[j + 1].dist) {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, D, F;
    struct Station st[100];
    int passedFuel[100];
    int poolSize = 0;

    printf("Enter target distance: ");
    scanf("%d", &D);

    printf("Enter start fuel: ");
    scanf("%d", &F);

    printf("Enter number of fuel stations: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Station %d (distance fuel): ", i + 1);
        scanf("%d %d", &st[i].dist, &st[i].fuel);
    }

    // append destination as a dummy station with 0 fuel
    st[n].dist = D;
    st[n].fuel = 0;

    sortStations(st, n); // sort real stations

    int stops = 0;
    int curFuel = F;
    int prevPos = 0;
    int possible = 1;

    for (int i = 0; i <= n; i++) {
        int distNeed = st[i].dist - prevPos;

        // if fuel is low, pick highest fuel from previously passed stations
        while (curFuel < distNeed) {
            if (poolSize == 0) {
                possible = 0;
                break;
            }

            // find max in passedFuel array
            int maxIdx = 0;
            for (int k = 1; k < poolSize; k++) {
                if (passedFuel[k] > passedFuel[maxIdx]) {
                    maxIdx = k;
                }
            }

            curFuel += passedFuel[maxIdx];
            stops++;

            // remove chosen station from pool
            passedFuel[maxIdx] = passedFuel[poolSize - 1];
            poolSize--;
        }

        if (!possible) {
            break;
        }

        curFuel -= distNeed;
        prevPos = st[i].dist;

        if (i < n) {
            passedFuel[poolSize++] = st[i].fuel;
        }
    }

    if (possible) {
        printf("Minimum refuelling stops required: %d\n", stops);
    } else {
        printf("Cannot reach the target distance.\n");
    }

    return 0;
}
