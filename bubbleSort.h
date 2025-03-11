#ifndef BUBBLESORT_H_INCLUDED
#define BUBBLESORT_H_INCLUDED
#include "car.h"
#include "operations.h"
#include "utils.h"
#include "client.h"

void bubbleSortCarsDatabase(FILE *arq, int tam, int *cont, const char *log_file);
void bubbleSortClientsDatabase(FILE *arq, int tam, int *cont, const char *log_file);


#endif //BUBBLESORT_H_INCLUDED
