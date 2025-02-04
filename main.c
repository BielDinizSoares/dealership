#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "car.h"
#include "client.h"
#include "operations.h"
#include "utils.h"
#include "sequentialSearch.h"
#include "BinarySearch.h"

int main() {
    const char *log_file1 = "General_log.txt";
    const char *log_file2 = "Sequential_search_car_log.txt";
    const char *log_file3 = "Sequential_search_client_log.txt";
    const char *log_file4 = "Binary_search_car_log.txt";
    const char *log_file5 = "Binary_search_client_log.txt";
    double time_car = 0, time_client = 0;

    FILE *file1 = fopen("cars_database.dat", "w+b");
    FILE *file2 = fopen("clients_database.dat", "w+b");
    int cont_cars = 0, cont_clients = 0;

    if (!file1 || !file2) {
        printf("Error opening files\n");
        exit(1);
    }

    // 1 /2 - Entities and databases implementations
    createCarsDatabase(file1, 10000);
    create_clients_database(file2, 10000);

    // 3 / 4 - sequential searches

    // TCar *car = sequentialSearchCar(5, file1, &cont_cars, &time_car, log_file2);
    // TClient *client = sequentialSearchClient(3, file2, &cont_clients, &time_client, log_file3);
    //
    // if (car) {
    //     printf("Car founded: ID %d\n", car->id);
    //     free(car);
    // } else {
    //     printf("Car not founded!\n");
    // }
    //
    // if (client) {
    //     printf("Client founded: ID %d\n", client->id);
    //     free(client);
    // } else {
    //     printf("Client not founded!\n");
    // }

    // 5 / 6 / 7 - binary searches
    //turn shuffle off
    // TCar *car = binary_search_car(5, file1,0,cars_file_size(file1), &cont_cars, log_file4);
    // if (car) {
    //     printf("Car founded: ID %d\n", car->id);
    //     free(car);
    // } else {
    //     printf("Car not founded!\n");
    // }
    // printf("\n----------------------------------------------------------------\n");
    //
    // TClient *client = binary_search_client(2, file2, 0, clients_file_size(file2), &cont_clients, log_file5);
    //
    // if (client) {
    //     printf("Client founded: ID %d\n", client->id);
    //     free(client);
    // } else {
    //     printf("Client not founded!\n");
    // }

    // turn shuffle on
    // 8 - Relating entities
    car_purchase(267, 983, file1, file2, log_file1);
    TCar *car = sequentialSearchCar(983, file1, &cont_cars,&time_car, log_file2);
    printCar(car);


    fclose(file1);
    fclose(file2);
    return 0;
}
