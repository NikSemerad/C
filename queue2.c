#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct TData {
    int x;
    int y;
} TDATA;


typedef struct TElement {
    int x;
    int y;
    struct TElement * next;
} TELEMENT;

typedef struct TQueue {
    TELEMENT * head;
    TELEMENT * tail;
    int lenght;

} TQUEUE;


int queueInit (TQUEUE * q) {
    q->head = NULL;
    q->tail = NULL;
    q->lenght = 0;
    return 1;
}

void queueDone (TQUEUE * q) {
    TELEMENT * tmp = q->head;
    while (tmp) {
        TELEMENT * next = tmp->next;
        free(tmp);
        tmp = next;
    }
    q->head = NULL;
    q->tail = NULL;
    q->lenght = 0;
} 

int queuePut (TQUEUE * q, int x, int y) {

    TELEMENT * new = (TELEMENT *) malloc (sizeof(*new));

    new->x = x;
    new->y = y;
    new->next = NULL;
    
    if (q->tail) {
        q->tail->next = new;
    } else {
        q->head = new;
    }
    q->tail = new;
    q->lenght ++;

    return 1;
}

int queueGet (TQUEUE * q, int * x, int * y) {
    
    if (q->head == NULL) {
        return 0;
    }

    *x = q->head->x;
    *y = q->head->y;

    TELEMENT * tmp = q->head->next;
    free(q->head);
    q->head = tmp;

    if (q->head == NULL) {
        q->tail = NULL;
    }

    q->lenght --;

    return 1;
}

int queueLenght (TQUEUE * q) {
    return q->lenght;
}
 
int main (void) {

    TQUEUE q;

    int x,y;

    queueInit (&q);

    assert( queuePut(&q, 10, 20) );
    assert( queuePut(&q, 30, 40) );
    assert( queuePut(&q, 50, 60) );
    assert( queuePut(&q, 70, 80) );
    assert( queuePut(&q, 90, 0) );

    assert( queueLenght(&q) == 5);

    assert( queueGet(&q, &x, &y) && x == 10 && y == 20);
    assert( queueGet(&q, &x, &y) && x == 30 && y == 40);
    assert( queueGet(&q, &x, &y) && x == 50 && y == 60);
    assert( queueGet(&q, &x, &y) && x == 70 && y == 80);
    assert( queueGet(&q, &x, &y) && x == 90 && y == 0);

    assert( queueLenght(&q) == 0);

    assert( queuePut(&q, 10, 20) );
    assert( queuePut(&q, 30, 40) );
    assert( queuePut(&q, 50, 60) );
    assert( queuePut(&q, 70, 80) );
    assert( queuePut(&q, 90, 0) );
    assert( queuePut(&q, 10, 10) );

    queueDone(&q);

    return 1;
}

