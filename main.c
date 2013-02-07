#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

int main(int argc, char ** argv){

    struct Hash_Table * table;

    hash("test 1");
    hash("TEST 1");
    hash("TEST 3");

    return 0;
}
