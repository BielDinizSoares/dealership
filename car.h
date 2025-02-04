#ifndef CARS_H_INCLUDED
#define CARS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct Car {
  int id;
  double price;
  char name[50];
  char brand[20];
  double weight;
  int idOwner;
}TCar;


TCar *car(int id, double price, char *name, char *brand, double weight);
int car_register_size();
void saveCar(TCar *car, FILE *out);
int cars_file_size(FILE *file);
TCar *readCar(FILE *in);
void printCar(TCar *car);
void createCarsDatabase(FILE *out, int size);
void printCarsDatabase(FILE *out);
int compareCars(TCar *c1, TCar *c2);


#endif //CARS_H_INCLUDED
