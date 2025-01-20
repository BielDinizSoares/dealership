#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct Car {
  int id;
  double price;
  char name[50];
  char brand[20];
  double weight;
}TCar;

TCar *car(int id, double price, char *name, char *brand, double weight);
void saveCar(TCar *car, FILE *out);
int cars_file_size(FILE *file);
TCar *readCar(FILE *in);
void printCar(TCar *car);
void createCarsDatabase(FILE *out, int size);
void shuffle(int *vet, int  MAX, int MIN);
void printCarsDatabase(FILE *out);
int compareCars(TCar *c1, TCar *c2);


#endif //CAR_H_INCLUDED
