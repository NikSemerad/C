#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int main (int argc, char * argv []) {

    int max;

    if (argc < 2 || sscanf (argv[1], "%d", &max) != 1 || max <= 1 ) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    int * sieve = (int *) malloc (max * sizeof(int));

    for ( int i = 0; i < max; i ++) {
        sieve[i] = 1;
    }
    
    sieve[0] = sieve[1] = 0;

    for (int i = 2; i < max; i ++) {
        if (sieve[i] == 1) {
            printf("%d ", i);
            for (int j = 2 * i; j < max; j += i) {
                sieve[j] = 0;
            }
        }
    }

    printf("\n");

    free(sieve);

    return 0;

}

