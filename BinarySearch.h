#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H
#include "car.h"
#include "client.h"

TCar *binary_search_car(int key, FILE *in, int start_search, int end_search, int *cont, const char *log_file);
TClient *binary_search_client(int key, FILE *in, int start_search, int end_search, int *cont, const char *log_file);

#endif //BINARYSEARCH_H
