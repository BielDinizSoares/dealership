#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "car.h"
#include "client.h"
#include "partitionsMethods.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>


// Função auxiliar para verificar se há registros válidos e não congelados
int has_unfrozen_valid(int *frozen, int *valid, int M) {
    for (int i = 0; i < M; i++) {
        if (valid[i] && !frozen[i]) return 1;
    }
    return 0;
}

// Função para classificação de carros usando Seleção por Substituição
int substitution_method_car(FILE *arq, int M) {
    rewind(arq);
    int nCar = cars_file_size(arq);
    if (nCar == 0) return 0;

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
        if (!has_unfrozen_valid(frozen, valid, M)) {
            fclose(p);
            qtdParticoes++;
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
        last_key = v[min_idx]->id;

        // Substituir pelo próximo registro
        fseek(arq, reg * regSize, SEEK_SET);
        TCar *next = readCar(arq);
        if (next) {
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

// int substitution_method_client(FILE *arq, int M) {
//     rewind(arq);
//     int nClient = client_register_size(arq);
//     if (nClient == 0) return 0;
//
//     int t = client_register_size();
//     int reg = 0;
//     int qtdParticoes = 0;
//     char nomeParticao[20];
//
//     // Alocar memória
//     TClient **v = malloc(M * sizeof(TClient*));
//     int *frozen = malloc(M * sizeof(int));
//     int *valid = malloc(M * sizeof(int));
//
//     // Inicializar arrays
//     for (int i = 0; i < M; i++) {
//         frozen[i] = 0;
//         valid[i] = 0;
//     }
//
//     // Ler primeiros M registros
//     int m_size = 0;
//     while (m_size < M && reg < nClient) {
//         fseek(arq, reg * t, SEEK_SET);
//         v[m_size] = read_client(arq);
//         if (v[m_size]) {
//             valid[m_size] = 1;
//             frozen[m_size] = 0;
//             m_size++;
//             reg++;
//         } else break;
//     }
//     M = m_size;
//
//     if (M == 0) {
//         free(v); free(frozen); free(valid);
//         return 0;
//     }
//
//     FILE *p = NULL;
//     int last_key = INT_MIN;
//
//     while (1) {
//         if (!has_unfrozen_valid(frozen, valid, M)) {
//             if (p) fclose(p);
//             qtdParticoes++;
//
//             // Verificar se ainda há registros válidos
//             int has_valid = 0;
//             for (int i = 0; i < M; i++) {
//                 if (valid[i]) { has_valid = 1; break; }
//             }
//             if (!has_valid) break;
//
//             sprintf(nomeParticao, "partition_cli%d.dat", qtdParticoes);
//             p = fopen(nomeParticao, "wb+");
//             if (!p) {
//                 perror("Erro ao criar partição");
//                 break;
//             }
//             // Descongelar registros
//             for (int i = 0; i < M; i++)
//                 if (valid[i]) frozen[i] = 0;
//             last_key = INT_MIN;
//         }
//
//         // Encontrar menor registro válido e não congelado
//         int min_idx = -1;
//         int min_id = INT_MAX;
//         for (int i = 0; i < M; i++) {
//             if (valid[i] && !frozen[i] && v[i]->id < min_id) {
//                 min_id = v[i]->id;
//                 min_idx = i;
//             }
//         }
//         if (min_idx == -1) continue;
//
//         // Escrever na partição
//         save_client(v[min_idx], p);
//         last_key = v[min_idx]->id;
//
//         // Substituir pelo próximo registro
//         if (reg < nClient) {
//             fseek(arq, reg * t, SEEK_SET);
//             TClient *next = read_client(arq);
//             if (next) {
//                 free(v[min_idx]);
//                 v[min_idx] = NULL;
//
//                 v[min_idx] = next;
//                 frozen[min_idx] = (next->id < last_key) ? 1 : 0;
//                 reg++;
//             } else {
//                 valid[min_idx] = 0;
//                 frozen[min_idx] = 1;
//             }
//         } else {
//             valid[min_idx] = 0;
//             frozen[min_idx] = 1;
//         }
//     }
//
//     // Liberar memória
//     for (int i = 0; i < M; i++)
//         if (valid[i]) free(v[i]);
//     free(v); free(frozen); free(valid);
//     return qtdParticoes;
// }