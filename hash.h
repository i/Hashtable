#ifndef HASH_H
#define HASH_H


struct Node{
    char * key;
    void * value;
    struct Node * next;
};

struct Node * new_node(char * key, void * value, struct Node * next);//
void destroy_node(struct Node * node);//
void destroy_list(struct Node * head);//


struct Hash_Table{
    int size;
    int population;
    float maxload;
    float loadfactor;
    struct Node ** lists;
};

struct Hash_Table * create(int size, float maxload);//
void destroy(struct Hash_Table *);

int hash(char * key);//
void set(struct Hash_Table * table, char * key, void * data);
void * get(struct Hash_Table * table, char * key);


#endif
