#ifndef HASH_H
#define HASH_H


struct Node{
    char * key;
    void * value;
    int occur, versions;
    struct Node * next, * similar;
};

struct Node * node_new(char * key, void * value);
void node_destroy(struct Node * node);
void list_destroy(struct Node * head);


struct Hash_Table{
    int size;
    int population;
    double loadfactor;
    struct Node ** lists;
};

struct Hash_Table * hash_table_create(int size);
void destroy(struct Hash_Table *);

size_t hash_fn(char * key);
void set(struct Hash_Table * table, char * key, void * data);
void * get(struct Hash_Table * table, char * key);
void rehash(struct Hash_Table * table);
struct Node ** get_all_entries(struct Hash_Table * table);
struct Node ** get_sorted(struct Hash_Table * table);

struct Node ** quicksort(struct Node ** ary);

#endif
