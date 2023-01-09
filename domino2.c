#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Tile {
    int x;
    int y;
    int count;
} TILE;

typedef struct Array {
    TILE * tiles;
    int capacity;
    int used;
} ARRAY;

ARRAY * initArray (int lenght) {
    ARRAY * array = (ARRAY *) malloc (sizeof(ARRAY));
    array->capacity = lenght;
    array->used = 0;
    array->tiles = (TILE *) malloc (sizeof(TILE) * lenght);
    return array;
}

void cleanArray (ARRAY * array) {
    free(array->tiles);
    free(array);
}

void addTile (ARRAY * array, int x, int y) {
    if (array->used < array->capacity) {
        array->tiles[array->used].x = x;
        array->tiles[array->used].y = y;
        array->tiles[array->used].count = 1;
        array->used ++;
    } else {
        array->tiles = (TILE *) realloc (array->tiles, sizeof(TILE) * array->capacity * 2);
        array->capacity *= 2;
        array->tiles[array->used].x = x;
        array->tiles[array->used].y = y;
        array->tiles[array->used].count = 1;
        array->used ++;
    }
}

void printArray (ARRAY * array) {
    for (int i = 0; i < array->used; i++) {
        printf("%dx [%d|%d] ", array->tiles[i].count, array->tiles[i].x, array->tiles[i].y);
    }
    printf("\n");
}

void getInput (ARRAY * array) {
    while (1) {
        int x, y;
        if (scanf(" [%d|%d] ", &x, &y) != 2) {
            if (feof(stdin)) {
                break;
            } else {
                printf("Nespravny vstup.\n");
                break;
            }
        } else {
            addTile(array, x, y);
        }
    }
}

void swapNumbers (ARRAY * array, int index) {
    int tmp = array->tiles[index].x;
    array->tiles[index].x = array->tiles[index].y;
    array->tiles[index].y = tmp;
}

int cmpFunction (const void * a, const void * b) {
    TILE * aa = (TILE *) a;
    TILE * bb = (TILE *) b;
    if ((bb->x < aa->x) - (aa->x < bb->x) == 0) {
        return (bb->y < aa->y) - (aa->y < bb->y) ;
    }
    return (bb->x < aa->x) - (aa->x < bb->x) ;
}

void sortTiles (ARRAY * array) {

    for (int i = 0; i < array->used; i++) {
        if (array->tiles[i].x > array->tiles[i].y) {
            swapNumbers(array,i);
        }
    }

    qsort(array->tiles, array->used, sizeof(TILE), cmpFunction);

}

void findDuplicates (ARRAY * array) {

    // int celkem = array->used;

    for (int i = 0; i < array->used; i++) {

        if (array->tiles[i].count == 0) {
            continue;
        }

        // celkem ++;

        int x = 1;

        while (array->tiles[i].x == array->tiles[i + x].x && array->tiles[i].y == array->tiles[i + x].y) {

            array->tiles[i].count++;
            array->tiles[i + x].count = 0;

            x++;
        }
        
    }

    // printf("Celkem kostek: %d\n", celkem);

}

void printResults (ARRAY * array) {
    for (int i = 0; i < array->used; i++) {
        if (array->tiles[i].count == 0) {
            continue;
        } else {
            printf("[%d|%d] %dx\n", array->tiles[i].x, array->tiles[i].y, array->tiles[i].count);
        }
    }
}

int main (void) {

    ARRAY * array = initArray(2);
    
    getInput(array);

    // printArray(array);

    sortTiles(array);

    findDuplicates(array);

    printResults(array);

    cleanArray(array);

    return 0;

}

