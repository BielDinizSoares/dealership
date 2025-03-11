#include "operations.h"
#include "car.h"
#include "client.h"
#include "utils.h"
#include "sequentialSearch.h"
#include "BinarySearch.h"

void car_purchase(int id_Client, int id_Car, FILE *Cars_file, FILE *Client_file, const char *log_purchase){
    double time_car = 0, time_client = 0;
    const char *log_temp = "useless.txt";
    const char *log_temp2 = "useless2.txt";

    //sequential search for a car
    int cont_1 = 0, cont_2 = 0;
    TCar *car = sequentialSearchCar(id_Car,Cars_file,&cont_1,&time_car, log_temp);
    //binary search for a client
    int total_clients = clients_file_size(Client_file);
    TClient *client = binary_search_client(id_Client,Client_file,0,total_clients - 1,  &cont_2,&time_client, log_temp2);


    FILE *log = fopen(log_purchase, "a");
    if (log == NULL) {
        printf("Error opening log file\n");
        return;
    }
        fprintf(log, "PURCHASE | Client %d -> Car %d | Total Time: %.6f | Total Comparisons: %d\n",
        id_Client, id_Car, (time_car + time_client), (cont_1 + cont_2));
        fclose(log);



    if (!client || !car) {
        printf("Car purchase error\n");
        free(car);
        free(client);
        return;
    }

    if (car->idOwner != 0) {
        printf("The car already has an owner!\n");
        free(car);
        free(client);
        return;
    }

    car->idOwner = id_Client;
    fseek(Cars_file, -car_register_size(), SEEK_CUR);
    saveCar(car, Cars_file);
    fflush(Cars_file);

    printf("Car purchase successfully!\n");
    printf("Client %d -> Car %d\n", id_Client, id_Car);
    free(car);
    free(client);


}




