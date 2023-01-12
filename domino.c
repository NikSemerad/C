#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct Domino {
    char id [10];
    int a;
    int b;
    int c;
    int d;
    int haveTwin;
    int isPrinted;
} DOMINO ;

typedef struct Array {
    DOMINO * dominos;
    int capacity;
    int used;
} ARRAY;


ARRAY * initArray (int lenght) {
    ARRAY * array = (ARRAY *) malloc (sizeof(ARRAY));
    array->capacity = lenght;
    array->used = 0;
    array->dominos = (DOMINO *) malloc (lenght * sizeof(DOMINO));
    return array;
}

int addDomino (ARRAY * array, char * id, int a, int b, int c, int d) {

    if (array->capacity > array->used) {
        array->dominos[array->used].a = a;
        array->dominos[array->used].b = b;
        array->dominos[array->used].c = c;
        array->dominos[array->used].d = d;
        array->dominos[array->used].haveTwin = 0;
        array->dominos[array->used].isPrinted = 0;
        strcpy(array->dominos[array->used].id, id);
        array->used ++;
    } else {
        array->dominos = (DOMINO *) realloc (array->dominos, sizeof(DOMINO) * array->capacity * 2);
        array->capacity *= 2;
        
        array->dominos[array->used].a = a;
        array->dominos[array->used].b = b;
        array->dominos[array->used].c = c;
        array->dominos[array->used].d = d;
        array->dominos[array->used].haveTwin = 0;
        array->dominos[array->used].isPrinted = 0;
        strcpy(array->dominos[array->used].id, id);

        array->used ++;
    }

    return 1;
}

void freeArray (ARRAY * array) {
    free(array->dominos);
    free(array);
}

int getInput (ARRAY * array) {

    while (1) {
        char id [10];
        int a, b, c, d;
        if (scanf("%9s [%d, %d, %d, %d]", id, &a, &b, &c, &d) != 5) {
            break;
        } else {
            addDomino (array, id, a, b, c, d);
        }
    }

    return 1;

}



void printDominos (ARRAY * array) {
    for (int i = 0; i<array->used; i++) {
        printf("%s [%d, %d, %d, %d] %d\n",
        array->dominos[i].id,
        array->dominos[i].a,
        array->dominos[i].b,
        array->dominos[i].c,
        array->dominos[i].d,
        array->dominos[i].haveTwin);
    }
}

int areSame (DOMINO dominoA, DOMINO dominoB) {

    int a[4] = {dominoA.a, dominoA.b, dominoA.c, dominoA.d};
    int b[4] = {dominoB.a, dominoB.b, dominoB.c, dominoB.d};

    for (int i = 0; i < 4; i++) {
        if (a[i] == b[0]) {
            if (a[(i + 1) % 4] == b[1] &&
            a[(i + 2) % 4] == b[2] &&
            a[(i + 3) % 4] == b[3]) {
                return 1;
            }
        }
    }
    return 0;
}

void printSame (ARRAY * array) {

    int count = 0;

    for (int i = 0; i<array->used; i++) {
        if (array->dominos[i].haveTwin == 1 && array->dominos[i].isPrinted == 0) {
            printf("%s%s ", count ? "= " : "", array->dominos[i].id);
            array->dominos[i].isPrinted = 1;
            count ++;
        }
    }
    
    if (count) {
        printf("\n");
    }
    
}

void checkDominos (ARRAY * array, int * count) {
    
    int tmp = 0;

    // Spocitat unikaty
    for (int i = 0; i < array->used; i++) {

        // k nemu vsechny zbyvajici
        tmp = 0;

        for (int j = i + 1; j < array->used; j++) {

            if (areSame(array->dominos[i], array->dominos[j])) {
                
                if (tmp == 0) {
                    tmp = 2;
                    *count += 1;
                } else {
                    tmp ++;
                }
            }
        }
    }

    
    printf("%d\n", *count);

    
    for (int i = 0; i < array->used; i++) {
        
        for (int j = i + 1; j < array->used; j++) {

            if (areSame(array->dominos[i], array->dominos[j])) {
        
                array->dominos[i].haveTwin = 1;
                array->dominos[j].haveTwin = 1;

            }

        }

        printSame(array);
    
    }
    

    


}



int main (void) {

    ARRAY * array = initArray(3);

    int count = 0;

    getInput(array);

    

    checkDominos(array, &count);

    // printDominos(array);

    freeArray(array);
    
    return 1;

}


