#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

int main(int argc, char ** argv){

    struct Hash_Table * table = create(15, .75);

    set(table, "one", "one");
    set(table, "fef", "bar");
    printf("%s\n",get(table, "one"));
    printf("%s\n",get(table, "fef"));

    return 0;
}
