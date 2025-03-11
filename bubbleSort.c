#include "bubbleSort.h"

void bubbleSortCarsDatabase(FILE *arq, int tam, int *cont, const char *log_file) {
    int i, change = 1;
    int lastSwap = tam - 1;
    //bubblesort
    while (change) {
        change = 0;
        int newLastSwap = 0;
        for (i = 0; i < lastSwap; i++){
            (*cont)++;
            fseek(arq, i * car_register_size(), SEEK_SET);
            TCar *ci = readCar(arq);

            fseek(arq, (i + 1) * car_register_size(), SEEK_SET);
            TCar *ci2 = readCar(arq);

            if (ci->id > ci2->id){
                change = 1;
                newLastSwap = i + 1;

                fseek(arq, i * car_register_size(), SEEK_SET);
                saveCar(ci2, arq);

                fseek(arq, (i + 1) * car_register_size(), SEEK_SET);
                saveCar(ci, arq);
            }
        }
        lastSwap = newLastSwap;
    }
}

void bubbleSortClientsDatabase(FILE *arq, int tam, int *cont, const char *log_file) {
    int i, change = 1;
    int lastSwap = tam - 1;
    //bubblesort
    while (change) {
        change = 0;
        int newLastSwap = 0;
        for (i = 0; i < lastSwap; i++){
            (*cont)++;
            fseek(arq, i * client_register_size(), SEEK_SET);
            TClient *ci = read_client(arq);

            fseek(arq, (i + 1) * client_register_size(), SEEK_SET);
            TClient *ci2 = read_client(arq);

            if (ci->id > ci2->id){
                change = 1;
                newLastSwap = i + 1;

                fseek(arq, i * client_register_size(), SEEK_SET);
                save_client(ci2, arq);

                fseek(arq, (i + 1) * client_register_size(), SEEK_SET);
                save_client(ci, arq);
            }
        }
        lastSwap = newLastSwap;
    }
}


