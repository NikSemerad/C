#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// kruhovy buffer

typedef struct TData {
    int x;
    int y;
} TDATA;

typedef struct TQueue {
    int max;
    int lenght;
    int read;
    int write;
    TDATA * data;
} TQUEUE;

void queueInit (TQUEUE * q, int capacity) {
    q->max = capacity;
    q->lenght = 0;
    q->read = 0;
    q->write = 0;
    q->data = (TDATA *) malloc (sizeof(*q->data) * capacity);
}

void queueDone (TQUEUE * q) {
    free(q->data);
    q->data = NULL;
}

int queuePut (TQUEUE * q, int x, int y) {

    if (q->lenght >= q->max) {
        return 0;
    }
    q->data[q->write].x = x;
    q->data[q->write].y = y;
    q->write = (q->write + 1) % q->max;
    q->lenght ++;

    return 1;

}

int queueGet (TQUEUE * q, int * x, int * y) {
    if (q->lenght == 0) {
        return 0;
    }

    *x = q->data[q->read].x;
    *y = q->data[q->read].y;
    q->lenght --;
    q->read = (q->read + 1) % q->max;

    return 1;
}

int queueLenght (TQUEUE * q) {
    return q->lenght;
}

int main (void) {

    TQUEUE q;

    int x,y;

    queueInit (&q, 5);

    assert( queuePut(&q, 10, 20) );
    assert( queuePut(&q, 30, 40) );
    assert( queuePut(&q, 50, 60) );
    assert( queuePut(&q, 70, 80) );
    assert( queuePut(&q, 90, 0) );
    assert( ! queuePut(&q, 10, 10) );

    assert( queueLenght(&q) == 5);

    assert( queueGet(&q, &x, &y) && x == 10 && y == 20);
    assert( queueGet(&q, &x, &y) && x == 30 && y == 40);
    assert( queueGet(&q, &x, &y) && x == 50 && y == 60);
    assert( queueGet(&q, &x, &y) && x == 70 && y == 80);
    assert( queueGet(&q, &x, &y) && x == 90 && y == 0);

    queueDone (&q);

    return 1;
}

