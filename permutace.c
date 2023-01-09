#include <stdio.h>
#include <stdlib.h>


void swap (int * a, int * b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void printPermutations (int * start, int * end, int * position) {

    if (position == end - 1) {
        for (int * i = start; i < end; i++) {
            printf("%s%d", i > start ? " " : "", *i);
        }
        printf("\n");
    }

    for (int * i = position; i < end; i++) {
        swap(position, i);
        printPermutations(start, end, position + 1);
        swap(position, i);
    }

}


int main (void) {

    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printPermutations (data, data + sizeof(data)/sizeof(data[0]), data);

    return 1;

}

