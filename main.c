#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

int main(int argc, char ** argv){

    struct Hash_Table * table = hash_table_create(15, .75);

    set(table, "foo", strdup("bar"));
    set(table, "foo", strdup("uccclelele"));
    set(table, "hot", strdup("dog"));
    printf("%s\n", (char *)get(table, "hot"));
    printf("%s\n", (char *)get(table, "foo"));

    return 0;
}
