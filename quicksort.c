#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "hash.h"
#include "quicksort.h"

void quicksort (struct Node ** a, int l, int r){
    int j;

    if( l < r ){
        j = partition(a, l, r);
        quicksort(a, l, j-sizeof(struct Node *));
        quicksort(a, j, r);
    }
}

int partition(struct Node ** a, int l, int r){
    struct Node * pivot, *t;
    int i, j;

    pivot = a[l];
    i = l; j = r+sizeof(*a);

    while(1){
        do i+=sizeof(struct Node *); while( i <= r && a[i] && strcasecmp(a[i]->key, pivot->key) <= 0);
        do j-=sizeof(struct Node *); while( j > r && a[j] && strcasecmp(a[j]->key, pivot->key) > 0 );
        if( i >= j) break;
    }
    t = a[i]; a[l] = a[j]; a[j]= t;
    return j;
}
