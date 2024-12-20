#ifndef CUSTOMERDB_H
#define CUSTOMERDB_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int ID;
    char *name;
    char *address;
    char *email;
} custdb_t;

int csv_file(char *str, custdb_t ***data, int *n_cus);
custdb_t *line(char *buffer);
void trim(char *str);

int b_file(char *str, custdb_t ***data, int *n_cus);
custdb_t *read_entry(FILE *fp);
char *readstring(FILE  *fp);

void display_data(custdb_t ***data, int *n_cus);
int add_entry(custdb_t ***data, int *n_cus);

void save_csv(custdb_t ***data, int *n_cus);
void save_bfile(custdb_t ***data, int *n_cus);

void free_data(custdb_t ***data, int *n_cus);
void free_cust(custdb_t *c);

#endif
