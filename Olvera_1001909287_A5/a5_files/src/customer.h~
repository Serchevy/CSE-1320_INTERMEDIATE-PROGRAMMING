#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/hash_map_utils.h"

#ifndef BUF_SIZE
#define BUF_SIZE 64
#endif

typedef struct {
    int id;
    char *name;
    char *address;
    char *email;
} customer_t;

customer_t *input_customer(customer_t *c);
dynamic_array_t *load_customers(char *filename, hash_map_t *map, int *num_cust);
void print_customer(customer_t *c);
void trim(char *str);
void print_array(dynamic_array_t *array);
void print_map(dynamic_array_t **map, int array_size);
void put_customers_in_map(hash_map_t *map, dynamic_array_t *customers, int n_keys);
customer_t *parse_line(char *buffer);
void free_map(hash_map_t *map);
void free_element(hash_element_t *elem);

#endif
