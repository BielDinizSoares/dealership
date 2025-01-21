#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "car.h"
#include <math.h>


int car_register_size() {
    return sizeof(int)  //id
           + sizeof(double) //price
           + sizeof(char) * 50 //name
           + sizeof(char) * 20 //brand
           + sizeof(double); //weight
}

// Creates car.
TCar *car(int id, double price, char *name, char *brand, double weight) {

    TCar *car = (TCar *) malloc(sizeof(TCar));
    //inicialize
    if (car) memset(car, 0, sizeof(TCar));
    //copy the values
    car->id = id;
    car->price = price;
    strcpy(car->name, name);
    strcpy(car->brand, brand);
    car->weight = weight;

    return car;
}

//saves car in out file
void saveCar(TCar *car, FILE *out) {
    fwrite(&car->id, sizeof(int), 1, out);
    fwrite(&car->price, sizeof(double), 1, out);
    fwrite(car->name, sizeof(char), sizeof(car->name), out);
    fwrite(car->brand, sizeof(char), sizeof(car->brand), out);
    fwrite(&car->weight, sizeof(double), 1, out);
}

//returns the amount of registers
int cars_file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    int size = trunc(ftell(file) / car_register_size() );
    return size;
}

//reads a car
//returns a pointer to a car read from a file

TCar *readCar(FILE *in) {
    TCar *car = (TCar *) malloc(sizeof(TCar));
    if (0 >= fread(&car->id, sizeof(int), 1, in)) {
        free(car);
        return NULL;
    }
    fread(&car->price, sizeof(double), 1, in);
    fread(&car->name, sizeof(char), sizeof(car->name), in);
    fread(&car->brand, sizeof(char), sizeof(car->brand), in);
    fread(&car->weight, sizeof(double), 1, in);
    return car;
}

// Prints a cart
void printCar(TCar *car) {
    printf("**********************************************");
    printf("\nCar of id: ");
    printf("%d", car->id);
    printf("\nName: ");
    printf("%s", car->name);
    printf("\nBrand: ");
    printf("%s", car->brand);
    printf("Price: \n");
    printf("%4.2f", car->price);
    printf("\nWeight: ");
    printf("%f", car->weight);
    printf("\n**********************************************");
}

// Creates database
void createCarsDatabase(FILE *out, int size){

    int vet[size];
    TCar *c;

    for(int i=0;i<size;i++)
        vet[i] = i+1;

    // shuffle

    printf("\nGenerating cars database...\n");

    for (int i=0;i<size;i++){
        c = car(vet[i], 10000, "Focus", "Ford", 10000);
        saveCar(c, out);
    }

    free(c);
}

void shuffle(int *vet, int  MAX, int MIN) {
    srand(time(NULL));
    for (int i= MAX - MIN -1;i>0;i--) {
        int j = rand() % (i);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

void printCarsDatabase(FILE *out){

    printf("\nPrinting cars database...\n");

    rewind(out);
    TCar *c;

    while ((c = readCar(out)) != NULL)
        printCar(c);
    free(c);
}


int compareCars(TCar *c1, TCar *c2){
    if (c1 == NULL) {
        return (c2 == NULL);
    }
    if (c1->id != c2->id) {
        return 0;
    }
    if (strcmp(c1->name, c2->name) != 0) {
        return 0;
    }
    return 1;
}













