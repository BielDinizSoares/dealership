#include "utils.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *vet, int a, int b) {
    int t = vet[b];
    vet[b] = vet[a];
    vet[a] = t;
}

void shuffle(int *vet, int size) {
    srand(time(NULL));
    for (int i = size-1; i > 0; i--) {
        int j = rand() % (i+1);
        swap(vet, i, j);
    }
}


