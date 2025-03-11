#include "car.h"
#include "client.h"
#include "BinarySearch.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

TCar *binary_search_car(int key, FILE *in, int start_search, int end_search, int *cont, double *time, const char *log_file) {

    TCar *c = NULL;
    int code = -1;

    clock_t start, end;
    start = clock();

    while (start_search <= end_search && code != key) {
        int half_search = trunc((start_search + end_search) / 2);
        printf("Start: %d; End: %d; Half:: %d\n", start_search, end_search, half_search);
        fseek(in, (half_search -1) * car_register_size(), SEEK_SET);
        c = readCar(in);
        (*cont)++;

        if (c) {
            code = c->id;
            if (code > key) {
                end_search = half_search - 1;
            } else if (code < key){
                start_search = half_search + 1;
            }
        }
    }
    end = clock();
    *time = ((double)(end - start)) / CLOCKS_PER_SEC;

    FILE *log = fopen(log_file, "a");
    if (log == NULL) {
        printf("Error opening log file\n");
        return NULL;
    }
    fprintf(log, "Comparisons: %d , Time: %f , Key: %d \n", *cont, *time, key);
    fclose(log);


    if (code == key) {
        return c;
    }
    else {
        if(c) free(c);
        return NULL;
    }
}

TClient *binary_search_client(int key, FILE *in, int start_search, int end_search, int *cont, double *time, const char *log_file) {

    TClient *c = NULL;
    int code = -1;

    clock_t start, end;
    start = clock();

    while (start_search <= end_search && code != key) {
        int half_search = trunc((start_search + end_search) / 2);
        printf("Start: %d; End: %d; Half:: %d\n", start_search, end_search, half_search);
        fseek(in, (half_search -1) * client_register_size(), SEEK_SET);
        c = read_client(in);
        (*cont)++;

        if (c) {
            code = c->id;
            if (code > key) {
                end_search = half_search - 1;
            } else if (code < key){
                start_search = half_search + 1;
            }
        }
    }
    end = clock();
    *time = ((double)(end - start)) / CLOCKS_PER_SEC;

    FILE *log = fopen(log_file, "a");
    if (log == NULL) {
        printf("Error opening log file\n");
        return NULL;
    }
    fprintf(log, "Comparisons: %d , Time: %f , Key: %d \n", *cont, *time, key);
    fclose(log);


    if (code == key) {
        return c;
    }
    else {
        if(c) free(c);
        return NULL;
    }
}




