#ifndef CUSTOMERQUEUE_H
#define CUSTOMERQUEUE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char *name;
    char *address;
    char *email;
} custq_t;

typedef struct node Node;
struct node {
    custq_t *data;
    Node *next;
};

void free_data(Node *cust_list);
void trim(char *str);
void process_data(Node **cust_list, int *num_cust);
int load_csv(FILE *fp, Node ***cust_list, int *num_cust);
custq_t *line(char *buffer);
void display_data(Node **cust_list);
Node *create_node(custq_t *);
void insert_node(Node **, Node *);


#endif
