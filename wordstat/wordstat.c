#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#include "node.h"

int main(int argc, char ** argv){
    struct node * list; 
/*    struct node * ptr;*/
    FILE * input;
    int wc = 0;
    char character;
    char * buffer ;

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

    buffer = (char * )malloc(2000);
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
                list = insert(list, buffer);
            }
            bzero(buffer, sizeof(char)*strlen(buffer)+1 );
            wc = 0;
        }
    }
    printf("In order traversal:\n");
    iot(list);
/*    ptr = list;*/
/*    while (ptr != NULL){*/
/*        printf("%s\n",ptr->data);*/
/*        ptr = ptr->next;*/
/*    }*/

return 0;
}
