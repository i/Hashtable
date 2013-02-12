#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "hash.h"

struct Hash_Table * hash_table_create(int size){
    struct Hash_Table * table = malloc(sizeof(struct Hash_Table));

    table->population = 0;
    table->size = size;
    table->loadfactor = .75;
    table->lists = calloc(size, sizeof(struct Node *));

    return table;
}

void table_destroy(struct Hash_Table * table){
    int i;

    for(i = 0; i < table->size; i++){
        list_destroy(table->lists[i]);printf("%d",i);
    }
    free(table);
    return;
}

struct Node * node_new(char * key, void * value){
    struct Node * node = malloc(sizeof(struct Node));
    char * temp = malloc(sizeof(key)+1);
    node->key = strcpy(temp, key);
    node->value = value;
    node->occur = 1;
    node->versions = 1;
    node->next = NULL;

    return node;
}


void list_destroy(struct Node * node){
    struct Node * next;
    
    while(node){
        if(node->similar){
            sim_destroy(node->similar);
        }
        next = node->next;
        free(node->key);
        free(node->value);
        free(node);
        node = next;
    }
    return;
}

void sim_destroy(struct Node * node){
    struct Node * next;
    while(node->similar){
        next = node->similar;
        free(node->similar);
        free(node->value);
        free(node);
        node = next;
    }
    return;
}

void set(struct Hash_Table * table, char * key, void * value){
    struct Node * temp, * curr, * prev;
    int index;
    index = hash_fn(key) % table->size;

    if(table->population / table->size > table->loadfactor){
        rehash(table);
    }

    temp = table->lists[index];

    if(temp == NULL){
        temp = node_new(key, value);
        table->lists[index] = temp;
        table->population++;
        return;
    }

    while(temp){
        if(strcasecmp(temp->key, key) == 0){
/*            printf("found occurence\n");*/
            temp->occur++;
            curr = temp;
            while(curr != NULL){
                if( strcmp(curr->key, key) == 0){
/*                    printf("existing found version\n");*/
                    return;
                }
                prev = curr;
                curr = curr->similar;
            }

            temp->versions++;
            temp = node_new(key, value);
            prev->similar = temp;
            return;
        }

        prev = temp;
        temp = temp->next;
    }
        temp = node_new(key, value);
        prev->next = temp;
        table->population++;
        return;
}

void * get(struct Hash_Table * table, char * key){
    int index = hash_fn(key) % table->size;
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


size_t hash_fn(char * key){
    size_t ret, i;
    ret = 2113;

    for(i = 0; i < strlen(key); i++){
        ret = abs(ret * tolower(key[i]));
    }

    return ret;
}


struct Hash_Table * rehash(struct Hash_Table * table){
    struct Hash_Table * newtable;
    struct Node * curr, * prev, * sim, * temp;
    int i;

    newtable = hash_table_create(table->size*2);
    for(i=0; i<table->size; i++){
        curr = table[i];
        while(curr){
            set(newtable, curr->key, 0);
            if(sim = (curr->similar)){
                while(sim){
                    
                }
            }
        }
    }


    table_destroy(table);
    return newtable;
}

/*returns an array of pointers to everything in hash table */
struct Node ** get_all_entries(struct Hash_Table * table){
    struct Node ** ret = calloc(table->population, sizeof(struct Node *));
    struct Node * curr;
    int i, j = 0;

    for(i=0; i < table->size; i++){
        curr = table->lists[i];
        while(curr != NULL){
            ret[j] = curr;
/*            printf("%s\t%i\n", ret[j]->key,j);*/
            j++;
            curr = curr->next;
        }
    }
    return ret;
}

char * wordtolower(char * word){
    int i;
    for(i = 0; i < sizeof(word)/sizeof(char); i++){
        word[i] = tolower(word[i]);
    }
    return word;
}



int cmpstringp(const void *p1, const void *p2){
    return strcasecmp(* (char * const *)((struct Node *) p1)->key, * (char * const *) ((struct Node *)p2)->key);
}
