#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"

struct Hash_Table * hash_table_create(int size, float maxload){
    struct Hash_Table * table = malloc(sizeof(struct Hash_Table));

    table->population = 0;
    table->size = size;
    table->maxload = maxload;
    table->loadfactor = 0;
    table->lists = calloc(size, sizeof(struct Node));

    return table;
}

struct Node * node_new(char * key, void * value){
    struct Node * node = malloc(sizeof(struct Node));
    node->key = strdup(key);
    node->value = value;
    node->next = NULL;

    return node;
}

void node_destroy(struct Node * node){
    free(node->key);
    free(node->value);
    free(node);

    return;
}

void list_destroy(struct Node * node){
    struct Node * next;

    while(node){
        next = node->next;
        free(node->key);
        free(node->value);
        free(node);
        node = next;
    }

    return;
}

void set(struct Hash_Table * table, char * key, void * value){
    struct Node * temp;
    int index = hash(key) % table->size;

    if(table->lists[index]){
        temp = table->lists[index];
        while(temp){
            printf("%s\n",temp->key);
            if(strcasecmp(temp->key, key) == 0){ //found a match
                printf("found match\n");
                // do more things
                //table->population++;
                break;
            }
            temp = temp->next;
        }

        if(temp == NULL){ // didn't find a match
            temp = node_new(key, value);
            table->lists[index] = temp;
            table->population++;
            return;
        }

        printf("Error: key already in use!\n");
        return;
    }
    table->population++;

    temp = node_new(key, value);
    table->lists[index] = temp;
    return;
}

void * get(struct Hash_Table * table, char * key){

    int index = hash(key) % table->size;
    struct Node * ptr;
    if(table == NULL){
        printf("Error: no table!\n");
        return NULL;
    }
    if(table->lists[index] == NULL){
        printf("Error1: no matching key!\n");
        return NULL;
    }

    ptr = table->lists[index];
    while(ptr != NULL){
        if(strcmp(key, ptr->key) == 0){
            return ptr->key;
        }
        ptr = ptr->next;
    }
    printf("Error2: no matching key!\n");
    return NULL;
}


int hash(char * key){
    int ret, i;
    ret = 2113;

    for(i = 0; i < strlen(key); i++){
        ret = abs(ret * strlen(key) * tolower(key[i]));
    }

    return ret;
}




