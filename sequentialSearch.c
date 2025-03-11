#include "sequentialSearch.h"
#include "car.h"
#include "client.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>

TCar *sequentialSearchCar(int key, FILE *in, int *cont,double *time_spent, const char *log_file) {
        TCar *c = NULL;
        *cont = 0;
        rewind(in);

        clock_t start = clock();
        while ((c = readCar(in)) != NULL) {
            (*cont)++;
            if (c->id == key) {
                break;
            }
            free(c);
            c = NULL;
        }
        clock_t end = clock();
        *time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        FILE *log = fopen(log_file, "a");
        if (log == NULL) {
        printf("Error opening log file\n");
        return NULL;
        }
        fprintf(log, "CAR | Key: %d, Time: %.6f, Comparisons: %d\n", key, *time_spent, *cont);
        fclose(log);

        return c;
    }

// sequentialSearch.c
TClient *sequentialSearchClient(int key, FILE *in, int *cont, double *time_spent, const char *log_file) {
    TClient *c = NULL;
    *cont = 0;
    rewind(in);

    clock_t start = clock();
    while ((c = read_client(in)) != NULL) {
        (*cont)++;
        if (c->id == key) {
            break;
        }
        free(c);
        c = NULL;
    }
    clock_t end = clock();
    *time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // Log simplificado
    FILE *log = fopen(log_file, "a");
    if (log) {
        fprintf(log, "CLIENT | Key: %d, Time: %.6f, Comparisons: %d\n", key, *time_spent, *cont);
        fclose(log);
    }


    return c;
}

