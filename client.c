#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "utils.h"

int client_register_size() {
    return sizeof(int)         // id
           + sizeof(char) * 50 // name
           + sizeof(char) * 50 // email
           + sizeof(char) * 20; // phone
}


TClient *client(int id, char *name, char *email, char *phone) {
    TClient *client = (TClient *)malloc(sizeof(TClient));
    if (client) memset(client, 0, sizeof(TClient));
    client->id = id;
    strcpy(client->name, name);
    strcpy(client->email, email);
    strcpy(client->phone, phone);
    return client;
}

void save_client(TClient *client, FILE *out) {
    fwrite(&client->id, sizeof(int), 1, out);
    fwrite(client->name, sizeof(char), 50, out);
    fwrite(client->email, sizeof(char), 50, out);
    fwrite(client->phone, sizeof(char), 20, out);
}

int clients_file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    int size = trunc(ftell(file) / client_register_size() );
    return size;
}

TClient *read_client(FILE *in) {
    TClient *client = (TClient *)malloc(sizeof(TClient));
    if (0 >= fread(&client->id, sizeof(int), 1, in)) {
        free(client);
        return NULL;
    }
    fread(client->name, sizeof(char), 50, in);
    fread(client->email, sizeof(char), 50, in);
    fread(client->phone, sizeof(char), 20, in);
    return client;
}

void print_client(TClient *client) {
    printf("**********************************************\n");
    printf("Client ID: %d\n", client->id);
    printf("Name: %s\n", client->name);
    printf("Email: %s\n", client->email);
    printf("Phone: %s\n", client->phone);
    printf("**********************************************\n");
}


void create_clients_database(FILE *out, int size) {
    int vet[size];
    TClient *c;

    for (int i = 0; i < size; i++) {
      vet[i] = i + 1;
    }

    // shuffle(vet, size);
    printf("\nGenerating clients database...\n");

    for (int i = 0; i < size; i++) {
      c = client(vet[i], "fulano", "fulano@gmail.com", "XXXX-XXXX");
      save_client(c, out);
    }
    free(c);
}


void print_clients_database(FILE *out) {
    printf("\nPrinting clients database...\n");

    rewind(out);
    TClient *client;

    while ((client = read_client(out)) != NULL) {
        print_client(client);
        free(client);
    }
}

int compareClients(TClient *c1, TClient *c2){
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





