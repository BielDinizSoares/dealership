#include "sequentialSearch.h"
#include "car.h"
#include "client.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>

TCar *sequentialSearchCar(int key, FILE *in, int *cont, const char *log_file) {

    TCar *c;
    int x;
    rewind(in);

    clock_t start, end;
    double time_spent;

    start = clock();
    while ((c = readCar(in)) != NULL){
        (*cont)++;
        if(c->id == key){
            x = 1;
            break;
        }
    }
    end = clock();
    time_spent = (end-start)/(double)CLOCKS_PER_SEC;

    FILE *log = fopen(log_file, "a");
    if (log) {
        fprintf(log, "Key: %d, Time of execution: %f seconds, Comparisons: %d\n", key, time_spent, *cont);
        fclose(log);
    } else {
        printf("Error! Could not open log file!\n");
    }

    if(x == 1)
        return c;
    else printf("Car not found!\n");

    free(c);
}

TClient *sequentialSearchClient(int key, FILE *in, int *cont, const char *log_file) {

    TClient *c;
    int x;
    rewind(in);

    clock_t start, end;
    double time_spent;

    start = clock();
    while ((c = read_client(in)) != NULL){
        (*cont)++;
        if(c->id == key){
            x = 1;
            break;
        }
    }
    end = clock();
    time_spent = (end-start)/(double)CLOCKS_PER_SEC;

    FILE *log = fopen(log_file, "a");
    if (log) {
        fprintf(log, "Key: %d, Time of execution: %f seconds, Comparisons: %d\n", key, time_spent, *cont);
        fclose(log);
    } else {
        printf("Error! Could not open log file!\n");
    }

    if(x == 1)
        return c;
    else printf("CLient not found!\n");

    free(c);
}

