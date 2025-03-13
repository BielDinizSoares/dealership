#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "car.h"
#include "client.h"
#include "partitionsMethods.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>

 int has_unfrozen_valid(int *frozen, int *valid, int M){
    for (int i = 0; i < M; i++) {
        if (valid[i] && !frozen[i]) return 1;
    }
    return 0;
}

// Função para classificação de carros usando Seleção por Substituição
int substitution_method_car(FILE *arq, int M){
    int nCar = cars_file_size(arq);

    if (nCar == 0) {
        return 0;
    }
    rewind(arq);
    printf("\nIniciando substituição com M = %d, nCar = %d\n", M, nCar);

    int regSize = car_register_size();
    int reg = 0;
    int qtdParticoes = 0;
    char nomeParticao[20];

    // Alocar memória para os registros
    TCar **v = calloc(M, sizeof(TCar*));
    int *frozen = calloc(M, sizeof(int));
    int *valid = calloc(M, sizeof(int));

    // Ler os primeiros M registros
    int m_size = 0;
    while (m_size < M && reg < nCar) {
        printf("Foram carregados %d registros iniciais para memória.\n", m_size);
        fseek(arq, reg * regSize, SEEK_SET);
        v[m_size] = readCar(arq);
        if (v[m_size]) {
            valid[m_size] = 1;
            frozen[m_size] = 0;
            m_size++;
            reg++;
        }
    }
    M = m_size;
    if (M == 0) {
        free(v);
        free(frozen);
        free(valid);
        return 0;
    }

    qtdParticoes++;
    sprintf(nomeParticao, "partition%d.dat", qtdParticoes);
    FILE *p = fopen(nomeParticao, "wb+");
    if (!p) {
        perror("Erro ao criar partição");
        goto cleanup;
    }

    int last_key = INT_MIN;
    while (1) {
        printf("Antes de verificar congelados: ");
        for (int i = 0; i < M; i++) {
            printf("[%d: %d] ", i, frozen[i]);
        }
        printf("\n");

        if (!has_unfrozen_valid(frozen, valid, M)) {
            // Ver se ainda tem entradas válidas
            int any_valid = 0;
            for (int i = 0; i < M; i++) {
                if (valid[i]) {
                    any_valid = 1;
                    break;
                }
            }
            if (!any_valid) {
                break; // Sai do loop
            }

            printf("Todos congelados! Criando nova partição...\n");
            fclose(p);
            qtdParticoes++;
            printf("Criando nova partição: partition%d.dat\n", qtdParticoes);
            sprintf(nomeParticao, "partition%d.dat", qtdParticoes);
            p = fopen(nomeParticao, "wb+");
            if (!p) break;
            for (int i = 0; i < M; i++) {
                if (valid[i]) frozen[i] = 0;
            }
            last_key = INT_MIN;
        }

        // Encontrar o menor registro
        int min_idx = -1;
        int min_id = INT_MAX;
        for (int i = 0; i < M; i++) {
            if (valid[i] && !frozen[i] && v[i]->id < min_id) {
                min_id = v[i]->id;
                min_idx = i;
            }
        }
        if (min_idx == -1) break;

        saveCar(v[min_idx], p);
        printf("Registrando carro ID %d na partição %d\n", v[min_idx]->id, qtdParticoes);
        last_key = v[min_idx]->id;

        // Substituir pelo próximo registro
        fseek(arq, reg * regSize, SEEK_SET);
        TCar *next = readCar(arq);
        if (next) {
            printf("Próximo carro lido: ID %d (Última chave: %d) -> Vai congelar? %d\n",
           next->id, last_key, (next->id <= last_key));
            free(v[min_idx]);
            v[min_idx] = next;
            frozen[min_idx] = (next->id < last_key);
            reg++;
        } else {
            valid[min_idx] = 0;
        }
    }

    fclose(p);
    cleanup:
    for (int i = 0; i < M; i++) {
        free(v[i]);
    }
    free(v);
    free(frozen);
    free(valid);
    return qtdParticoes;
}

int substitution_method_client(FILE *arq, int M){

     int nClient = clients_file_size(arq);

     if (nClient == 0) {
         return 0;
     }

     rewind(arq);
     printf("\nIniciando substituição com M = %d, nCar = %d\n", M, nClient);

     int regSize = client_register_size(arq);
     int reg = 0;
     int qtdParticoes = 0;
     char nomeParticao[20];

    // Alocar memória para os registros
     TClient **v = calloc(M, sizeof(TClient*));
     int *frozen = calloc(M, sizeof(int));
     int *valid = calloc(M, sizeof(int));

    // Ler os primeiros M registros
     int m_size = 0;
     while (m_size < M && reg < nClient) {
        printf("Foram carregados %d registros iniciais para memória.\n", m_size);
        fseek(arq, reg * regSize, SEEK_SET);
        v[m_size] = read_client(arq);
        if (v[m_size]) {
            valid[m_size] = 1;
            frozen[m_size] = 0;
            m_size++;
            reg++;
        }
     }

     M = m_size;
     if (M == 0) {
        free(v);
        free(frozen);
        free(valid);
        return 0;
     }

     qtdParticoes++;
     sprintf(nomeParticao, "partition%d.dat", qtdParticoes);
     FILE *p = fopen(nomeParticao, "wb+");
     if (!p) {
        perror("Erro ao criar partição");
        goto cleanup;
     }

     int last_key = INT_MIN;
     while (1) {
        printf("Antes de verificar congelados: ");
        for (int i = 0; i < M; i++) {
            printf("[%d: %d] ", i, frozen[i]);
        }
        printf("\n");

        if (!has_unfrozen_valid(frozen, valid, M)) {
            // Ver se ainda tem entradas válidas
            int any_valid = 0;
            for (int i = 0; i < M; i++) {
                if (valid[i]) {
                    any_valid = 1;
                    break;
                }
            }
            if (!any_valid) {
                break; // Sai do loop
            }

            printf("Todos congelados! Criando nova partição...\n");
            fclose(p);
            qtdParticoes++;
            printf("Criando nova partição: partition%d.dat\n", qtdParticoes);
            sprintf(nomeParticao, "partition%d.dat", qtdParticoes);
            p = fopen(nomeParticao, "wb+");
            if (!p) break;
            for (int i = 0; i < M; i++) {
                if (valid[i]) frozen[i] = 0;
            }
            last_key = INT_MIN;
        }

        // Encontrar o menor registro
        int min_idx = -1;
        int min_id = INT_MAX;
        for (int i = 0; i < M; i++) {
            if (valid[i] && !frozen[i] && v[i]->id < min_id) {
                min_id = v[i]->id;
                min_idx = i;
            }
        }
        if (min_idx == -1) break;

        save_client(v[min_idx], p);
        printf("Registrando cliente ID %d na partição %d\n", v[min_idx]->id, qtdParticoes);
        last_key = v[min_idx]->id;

        // Substituir pelo próximo registro
        fseek(arq, reg * regSize, SEEK_SET);
        TClient *next = read_client(arq);
        if (next) {
            printf("Próximo cliente lido: ID %d (Última chave: %d) -> Vai congelar? %d\n",
            next->id, last_key, (next->id <= last_key));
            free(v[min_idx]);
            v[min_idx] = next;
            frozen[min_idx] = (next->id < last_key);
            reg++;
        } else {
            valid[min_idx] = 0;
        }
    }

     fclose(p);
     cleanup:
     for (int i = 0; i < M; i++) {
        free(v[i]);
     }
     free(v);
     free(frozen);
     free(valid);
     return qtdParticoes;

 }