#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"

struct Hash_Table * create(int size, float maxload){
    struct Hash_Table * table;

    table->population = 0;
    table->size = size;
    table->maxload = maxload;
    table->loadfactor = 0;
    table->lists = calloc(size, sizeof(struct Node));

    return table;
}

struct Node * new_node(char * key, void * value, struct Node * next){
    struct Node * node = malloc(sizeof(struct Node));
    node->key = malloc(sizeof(key));
    node->value = malloc(sizeof(value));
    node->next = NULL;

    return node;
}

void destroy_node(struct Node * node){
    free(node->key);
    free(node->value);
    free(node);
    return;
}

void destroy_list(struct Node * node){
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
            if(strcasecmp(temp->key, key) == 0){ //found a match
                // do more things
                //table->population++;
                break;
            }
            temp = temp->next;
        }

        if(temp == NULL){ // didn't find a match
            temp = new_node(key, value, table->lists[index]);
            table->lists[index] = temp;
            table->population++;
            return;
        }

        printf("Error. Shouldn't be here.");
    }

    temp = new_node(key, value, NULL);
    table->lists[index] = temp;
    table->population++;
    return;
}


int hash(char * key){
    int ret, i;
    ret = 2113;

    for(i = 0; i < strlen(key); i++){
        ret = abs(ret * strlen(key) * (i+13) * tolower(key[i]));
    }
    printf("%d\n",ret);
    return ret;
}




