#include "dynamic_arrays.h"


/*
 * Inserts a new item into the array at the requested index.
 * If any value below 0 is given as the index, it inserts at the end of the array.
 */
void array_insert(dynamic_array_t *array, void *item, int index) {
    if (index < 0) {
        index = array->size;
    }

    array->data = realloc(array->data, (array->size + 1) * sizeof(void *));

    for (int i = array->size - 1; i > index; i++) {
        array->data[i] = array->data[i-1];
    }

    array->data[index] = item;
    array->size++;
}


/*
 * Pops the item given by the requested index from the array.
 */
void *pop_item(dynamic_array_t *array, int index) {
    if (array == NULL || array->size == 0 || index >= array->size || index < 0) {
        return NULL;
    }

    printd("[DEBUG] dynamic_arrays.c::pop_item: index = %d, array->size = %d\n", index, array->size);

    void *item = array->data[index];

    for (int i = index; i < array->size - 1; i++) {
        array->data[i] = array->data[i + 1];
    }

    array->data = realloc(array->data, (array->size - 1) * sizeof(void *));
    array->size--;

    return item;
}

/*
 * Retrieves the item at the requested index.
 */
void *get_item(dynamic_array_t *array, int index) {
    if (index < 0 || index > array->size || array->size == 0) {
        return NULL;
    }

    return array->data[index];
}

/*
 * Attempts to find an item in the array with a matching
 * Uses a hack that is not recommended
 */
/*void *find_item(dynamic_array_t *array, char *key) {*/
    /*for (int i = 0; i < array->size; i++) {*/
        /*// Taking advantage of the fact that `key` is the first member of the struct*/
        /*if (!strcmp(array->data[i], key)) {*/
            /*return array->data[i];*/
        /*}*/
    /*}*/

    /*return NULL;*/
/*}*/

/*
 * Attempts to find an item in the array with a matching
 */
void *find_item(dynamic_array_t *array, char *key, int (*check_fn)(const void *, char *)) {
    for (int i = 0; i < array->size; i++) {
        // Taking advantage of the fact that `key` is the first member of the struct
        if (check_fn(array->data[i], key)) {
            prints("[DEBUG] dynamic_arrays.c::find_item: Found item %s\n", key);
            return array->data[i];
        }
    }

    return NULL;
}
