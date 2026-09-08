/*
 * DAA Lab - 07 | Problem 6
 *
 * QUESTION:
 * 6. [The best time to be alive]
 *    An editor of The History of the World Science wants to find out the time when the
 *    largest number of prominent scientists were alive. The prominent scientists are,
 *    by definition, the people mentioned in the book with the dates of their birth and
 *    death. (No living scientists are included in the book.) Devise an algorithm for
 *    this task if it has the book’s index as its input. The entries in the index are
 *    sorted alphabetically and give the persons’ birth and death years. If a person A
 *    died the same year person B was born, assume that the former event happened before
 *    the latter one.
 *
 *    By choosing the proper input representation, write a program in C to validate your
 *    algorithm and derive the complexity analysis of your algorithm.
 *
 * ALGORITHM & TIE-BREAKING MODEL:
 * 1. Convert each scientist record [birthYear, deathYear] into two discrete events:
 *    - BIRTH event at birthYear (+1)
 *    - DEATH event at deathYear (-1)
 *
 * 2. Tie-breaking rule:
 *    "If person A died the same year person B was born, assume the former event happened
 *    before the latter one."
 *    Therefore, on equal years:
 *        DEATH (-1) MUST PRECEDE BIRTH (+1).
 *
 * 3. Sweep-line:
 *    Sort the 2N events by year ascending, then DEATH before BIRTH.
 *    Traverse events tracking current concurrent count and record the peak count and year.
 *
 * COMPLEXITY ANALYSIS:
 * - Time Complexity:  O(N log N) dominated by sorting 2N events
 * - Space Complexity: O(N) to store events array
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 64
#define EVENT_DEATH 0
#define EVENT_BIRTH 1

typedef struct {
    char name[MAX_NAME_LEN];
    int birthYear;
    int deathYear;
} Scientist;

typedef struct {
    int year;
    int type; // EVENT_DEATH (0) before EVENT_BIRTH (1)
    char name[MAX_NAME_LEN];
} TimelineEvent;

int compareEvents(const void *a, const void *b) {
    const TimelineEvent *e1 = (const TimelineEvent *)a;
    const TimelineEvent *e2 = (const TimelineEvent *)b;

    if (e1->year != e2->year) {
        return e1->year - e2->year;
    }
    return e1->type - e2->type;
}

void findBestTimeToBeAlive(Scientist scientists[], int n) {
    printf("Scientist Index (%d records, alphabetically sorted):\n", n);
    for (int i = 0; i < n; i++) {
        printf("  %-28s : %4d - %4d\n",
               scientists[i].name, scientists[i].birthYear, scientists[i].deathYear);
    }
    printf("\n");

    int totalEvents = 2 * n;
    TimelineEvent *events = (TimelineEvent *)malloc(totalEvents * sizeof(TimelineEvent));

    int idx = 0;
    for (int i = 0; i < n; i++) {
        events[idx].year = scientists[i].birthYear;
        events[idx].type = EVENT_BIRTH;
        strncpy(events[idx].name, scientists[i].name, MAX_NAME_LEN);
        idx++;

        events[idx].year = scientists[i].deathYear;
        events[idx].type = EVENT_DEATH;
        strncpy(events[idx].name, scientists[i].name, MAX_NAME_LEN);
        idx++;
    }

    qsort(events, totalEvents, sizeof(TimelineEvent), compareEvents);

    int currentAlive = 0;
    int maxAlive = 0;
    int bestYearStart = 0;
    int bestYearEnd = 0;

    for (int i = 0; i < totalEvents; i++) {
        if (events[i].type == EVENT_BIRTH) {
            currentAlive++;
            if (currentAlive > maxAlive) {
                maxAlive = currentAlive;
                bestYearStart = events[i].year;
            }
        } else if (events[i].type == EVENT_DEATH) {
            if (currentAlive == maxAlive && bestYearEnd < bestYearStart) {
                bestYearEnd = events[i].year;
            }
            currentAlive--;
        }
    }

    if (bestYearEnd < bestYearStart) {
        bestYearEnd = bestYearStart;
    }

    printf("Analysis Results:\n");
    printf("  Maximum scientists alive concurrently: %d\n", maxAlive);
    printf("  Peak period: %d to %d (Peak year: %d)\n\n", bestYearStart, bestYearEnd, bestYearStart);

    int peakYear = bestYearStart;
    printf("Scientists alive during year %d:\n", peakYear);
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (scientists[i].birthYear <= peakYear && scientists[i].deathYear > peakYear) {
            count++;
            int age = peakYear - scientists[i].birthYear;
            printf("  %2d. %-26s (Born %4d, Died %4d, Age %2d)\n",
                   count, scientists[i].name, scientists[i].birthYear, scientists[i].deathYear, age);
        }
    }
    printf("\n");

    free(events);
}

int main(void) {
    printf("DAA Lab 07 - Question 6: The Best Time to be Alive\n\n");

    Scientist index[] = {
        {"Albert Einstein",           1879, 1955},
        {"Blaise Pascal",             1623, 1662},
        {"Christiaan Huygens",        1629, 1695},
        {"Galileo Galilei",           1564, 1642},
        {"Gottfried Wilhelm Leibniz", 1646, 1716},
        {"Isaac Newton",              1643, 1727},
        {"Johannes Kepler",           1571, 1630},
        {"Marie Curie",               1867, 1934},
        {"Max Planck",                1858, 1947},
        {"Niels Bohr",                1885, 1962},
        {"Pierre de Fermat",          1601, 1665},
        {"Rene Descartes",            1596, 1650},
        {"Robert Boyle",              1627, 1691},
        {"Robert Hooke",              1635, 1703}
    };

    int n = sizeof(index) / sizeof(index[0]);
    findBestTimeToBeAlive(index, n);

    return 0;
}
