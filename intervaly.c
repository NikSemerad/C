#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Interval {
    int x;
    int y;
} INTERVAL;

typedef struct Array {
    INTERVAL * intervals;
    int capacity;
    int used;
} ARRAY;

ARRAY * initArray(int lenght) {
    ARRAY * array = (ARRAY *) malloc (sizeof(ARRAY));
    array->capacity = lenght;
    array->used = 0;
    array->intervals = (INTERVAL *) malloc (sizeof(INTERVAL) * lenght);
    return array;
}

void addInterval (ARRAY * array, int x, int y) {
    if (array->used < array->capacity) {
        array->intervals[array->used].x = x;
        array->intervals[array->used].y = y;
        array->used ++;
    } else {
        array->intervals = realloc (array->intervals, sizeof(INTERVAL) * array->capacity * 2);
        array->capacity *= 2;
        array->intervals[array->used].x = x;
        array->intervals[array->used].y = y;
        array->used ++;
    }
}

void printIntervals(ARRAY * array) {
    for (int i = 0; i < array->used; i++) {
        printf("[%d, %d]\n", array->intervals[i].x, array->intervals[i].y);
    }
}

void freeArray (ARRAY * array) {
    free(array->intervals);
    free(array);
}


int getInput (ARRAY * array) {
    
    int x, y;
    
    while (1) {
        if ( scanf(" [ %d, %d ] ", &x, &y) != 2) {
            if (feof(stdin)) {
                return 1;
            } else {
                printf("Nespravny vstup\n");
                return 0;
            }
        } else {
            addInterval(array, x, y);
        }
    }
}

int cmpFunction (const void * a, const void * b) {
    INTERVAL * aa = (INTERVAL *) a;
    INTERVAL * bb = (INTERVAL *) b;
    if ((bb->x < aa->x) - (aa->x < bb->x) == 0) {
        return (bb->y < aa->y) - (aa->y < bb->y);
    }
    return (bb->x < aa->x) - (aa->x < bb->x);
}

void sortArray (ARRAY * array) {
    qsort(array->intervals, array->used, sizeof(INTERVAL), cmpFunction);
}

int calcInterval (ARRAY * array) {
    int celkem = 0;

    for (int i = 0; i < array->used; i++) {
        int x = array->intervals[i].x;
        int y = array->intervals[i].y;
        int sum = y - x;

        // printf("%d\n", sum);

        celkem += sum;

        if (i < array->used - 1 && y > array->intervals[i + 1].x) {
            int overlay = array->intervals[i + 1].x - y;
            celkem += overlay;
        }
    }
    
    return celkem;
}


int main (void) {

    ARRAY * array = initArray (20);

    if (!getInput(array)) {
        freeArray(array);
        return 1;
    }

    sortArray(array);

    printIntervals(array);

    printf("Celkova delka intervalu: %d\n", calcInterval(array));

    freeArray(array);

    return 0;
}

