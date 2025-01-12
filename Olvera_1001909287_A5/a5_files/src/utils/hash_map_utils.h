#ifndef HASH_MAP_UTILS_H_
#define HASH_MAP_UTILS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "dynamic_arrays.h"

#define LOAD_FACTOR 0.7
#define DEFAULT_RESIZE_FACTOR 2

typedef struct {
    char *key;
    void *value;
} hash_element_t;

typedef struct {
    dynamic_array_t **temp;
    dynamic_array_t **primary;
    int num_keys;
    int temp_size;
    int map_size;
    int temp_index;
    int r_value;
} hash_map_t;

int hash_function(char *);
int compute_index(char *, int);
double compute_load_factor(int, int);
double compute_resize_factor(int N, int K, int M, int R, double bound);
int matches_key(const void *, char *);
void resize_map(hash_map_t *map, double factor);
void init_map(hash_map_t *, int);
hash_element_t *search(hash_map_t *, char *);
void rehash_inc(hash_map_t *);
void insert_item(dynamic_array_t **, hash_element_t *);
void insert(hash_map_t *, hash_element_t *, int added);
void insert_no_rehash(hash_map_t *map, hash_element_t *elem);

#endif
