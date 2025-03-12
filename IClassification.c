#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "car.h"
#include "client.h"
#include "IClassification.h"

int i_classification_car(FILE *arq, int M){
    rewind(arq); //posiciona cursor no inicio do arquivo

    int reg = 0;
    int nCar = car_register_size(arq);
    int qtdParticoes = 0;
    int t = car_register_size();
    char *nomeParticao[20];

    while (reg != nCar) {
        //le o arquivo e coloca no vetor
        TCar *v[M];
        int i = 0;
        while (!feof(arq)) {
            fseek(arq, (reg) * t, SEEK_SET);
            v[i] = readCar(arq);

            i++;
            reg++;
            if(i>=M) break;
        }

        //ajusta tamanho M caso arquivo de entrada tenha terminado antes do vetor
        if (i != M) {
            M = i;
        }

        //faz ordenacao
        for (int j = 1; j < M; j++) {
            TCar *f = v[j];
            i = j - 1;
            while ((i >= 0) && (v[i]->id > f->id)) {
                v[i + 1] = v[i];
                i = i - 1;
            }
            v[i + 1] = f;
        }

        //cria arquivo de particao e faz gravacao

        sprintf(nomeParticao, "partition%i.dat", qtdParticoes);
        //nome = fopen(nomeParticao, "wb");

        //printf("\n%s\n", nome);

        FILE *p;

        if ((p = fopen(nomeParticao, "wb+")) == NULL) {
            printf("Erro criar arquivo de saida\n");
        } else {
            for (int i = 0; i < M; i++) {
                fseek(p, (i) * t, SEEK_SET);
                saveCar(v[i], p);
                //imprime(v[i]);
            }
            printCarsDatabase(p);
            fclose(p);
            qtdParticoes++;
        }
        for(int jj = 0; jj<M; jj++)
            free(v[jj]);
    }

    return qtdParticoes;

}

int i_classification_client(FILE *arq, int M){
    rewind(arq); //posiciona cursor no inicio do arquivo

    int reg = 0;
    int nClient = client_register_size(arq);
    int qtdParticoes = 0;
    int t = client_register_size();
    char *nomeParticao[20];

    while (reg != nClient) {
        //le o arquivo e coloca no vetor
        TClient *v[M];
        int i = 0;
        while (!feof(arq)) {
            fseek(arq, (reg) * t, SEEK_SET);
            v[i] = read_client(arq);

            i++;
            reg++;
            if(i>=M) break;
        }

        //ajusta tamanho M caso arquivo de entrada tenha terminado antes do vetor
        if (i != M) {
            M = i;
        }

        //faz ordenacao
        for (int j = 1; j < M; j++) {
            TClient *f = v[j];
            i = j - 1;
            while ((i >= 0) && (v[i]->id > f->id)) {
                v[i + 1] = v[i];
                i = i - 1;
            }
            v[i + 1] = f;
        }

        //cria arquivo de particao e faz gravacao

        sprintf(nomeParticao, "partition%i.dat", qtdParticoes);
        //nome = fopen(nomeParticao, "wb");

        //printf("\n%s\n", nome);

        FILE *p;

        if ((p = fopen(nomeParticao, "wb+")) == NULL) {
            printf("Erro criar arquivo de saida\n");
        } else {
            for (int i = 0; i < M; i++) {
                fseek(p, (i) * t, SEEK_SET);
                save_client(v[i], p);
                //imprime(v[i]);
            }
            print_clients_database(p);
            fclose(p);
            qtdParticoes++;
        }
        for(int jj = 0; jj<M; jj++)
            free(v[jj]);
    }

    return qtdParticoes;

}
