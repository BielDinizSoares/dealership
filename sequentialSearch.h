#ifndef SEQUENTIALSEARCH_H_INCLUDED
#define SEQUENTIALSEARCH_H_INCLUDED
#include "car.h"
#include "client.h"

TCar *sequentialSearchCar(int key, FILE *in, int *cont,double *time_spent, const char *log_file);
TClient *sequentialSearchClient(int key, FILE *in, int *cont, double *time_spent, const char *log_file);

#endif //SEQUENTIALSEARCH_H_INCLUDED