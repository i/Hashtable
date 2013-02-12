#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#include "hash.h"
#include "quicksort.h"

int main(int argc, char ** argv){
    struct Hash_Table * table = hash_table_create(20);
    FILE * input;
    int i, wc = 0;
    char character;
    char * buffer ;
    struct Node * currnode, ** ary;

    if(argc != 2){
        printf("Error. Do you need help?\n");
        return 0;
    }

    if(strcmp(argv[1],"-h") == 0){
        printf("HELP\n");
        return 0;
    }

    input = fopen(argv[1], "r");
    if(input == NULL){
        printf("Couldn't open file: %s!\n", argv[1]);
        return 1;
    }

    buffer = calloc(2000, sizeof(char));
    while( (character = fgetc(input)) != EOF){
        if(wc == 0 && isalpha(character) ){ /*add to beginning of word*/
/*          printf("adding \"%c\" to front of buffer\n", character);*/
            buffer[wc] = character;
            wc++;
        }
        else if( wc > 0 && isalnum(character)  ){
/*          printf("adding %c to buffer\n", character);*/
            buffer[wc] = character;
            wc++;
        }
        else{
            if(buffer[0] != '\0'){
/*                printf("%s\n",buffer);*/
                set(table, buffer, 0);
            }
            bzero(buffer, sizeof(char)*strlen(buffer)+1 );
            wc = 0;
        }
    }
    if (buffer[0] != '\0')
        set(table, buffer, 0);
    free(buffer);

    ary =  get_all_entries(table);
    qsort(ary, table->population, sizeof(struct Node *), cmpstringp);

    printf("-------------------------\n");
    for(i=0; i<table->population; i++){
        currnode = (ary[i]);
        if(currnode)
            printf("%s\t%d\t%d\n", wordtolower(currnode->key),
                    currnode->occur, currnode->versions);
    }

    table_destroy(table);
    free(ary);
    return 0;
}
