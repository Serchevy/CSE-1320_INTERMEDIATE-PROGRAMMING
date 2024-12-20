#ifndef DYNAMIC_ARRAYS_H_
#define DYNAMIC_ARRAYS_H_

#ifdef DEBUG
#define printa(s) printf(s);
#define prints(s,a) printf(s,a);
#define printd(s,a,b) printf(s,a,b);
#else
#define printa(s)
#define prints(s,a)
#define printd(s,a,b)
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    void **data;
} dynamic_array_t;

void array_insert(dynamic_array_t *array, void *item, int index);
void *pop_item(dynamic_array_t *array, int index);
void *get_item(dynamic_array_t *array, int index);
//void *find_item(dynamic_array_t *array, char *key);
void *find_item(dynamic_array_t *array, char *key, int (*check_fn)(const void *, char *));

#endif
