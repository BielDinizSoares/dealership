#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    char email[50];
    char phone[20];
} TClient;

int client_register_size();
TClient *client(int id, char *name, char *email, char *phone);
void save_client(TClient *client, FILE *out);
int clients_file_size(FILE *file);
TClient *read_client(FILE *in);
void print_client(TClient *client);
void create_clients_database(FILE *out, int size);
void print_clients_database(FILE *out);
int compareClients(TClient *c1, TClient *c2);

#endif //CLIENT_H_INCLUDED
