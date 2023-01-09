#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


// Struct

typedef struct {
    int * values;
    int lenght;
    int used;
} TArray;


// Create an array

TArray * createArray (int lenght) {
    TArray * array = (TArray *) malloc (sizeof(*array));
    array->lenght = lenght;
    array->values = (int *) malloc (lenght * sizeof(int));
    array->used = 0;
    return array;
}


// Add item to array

void addItem (TArray * array, int number) {
    
    if (array->used < array->lenght) {
        array->values[array->used] = number;
        array->used += 1;
    } else {
        array->values = (int *) realloc (array->values, array->lenght * 2 * sizeof(int));
        array->lenght *= 2;
        array->values[array->used] = number;
        array->used += 1;
    }

}

// Print array

void printArray (TArray * array) {
    for (int i = 0; i < array->used; i++) {
        printf("%d\n", array->values[i]);
    }
}


// Free array

void freeArray (TArray * array) {
    free(array->values);
    free(array);
}




// void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));

int cmpFunction (const void * a, const void * b) {
    return ( *(int *)b < *(int *)a ) - ( *(int *)a < *(int *)b );
}


int main (void) {

    TArray * myArray = createArray(3);

    addItem(myArray, 3012);
    addItem(myArray, 50123);
    addItem(myArray, 201234);
    addItem(myArray, 301234);
    addItem(myArray, 501234);
    addItem(myArray, 10);
    addItem(myArray, 20);
    addItem(myArray, 30);
    addItem(myArray, 50);
    addItem(myArray, 201);
    

    printArray(myArray);

    printf("\n");

    qsort(myArray->values, myArray->used, sizeof(int), cmpFunction);

    printArray(myArray);

    freeArray(myArray);
    
    return 1;
}

