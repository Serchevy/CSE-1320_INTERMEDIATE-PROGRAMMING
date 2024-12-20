#include "hash_map_utils.h"

int hash_function(char *key) {
    int hash = 0;

    for (int i = 0; i < strlen(key); i++) {
        hash += key[i];
    }

    return hash;
}

int compute_index(char *key, int map_size) {
    int hash = hash_function(key);
    int index = hash % map_size;

    return index;
}

double compute_load_factor(int num_keys, int bucket_size) {
    return (double)num_keys / bucket_size;
}

/*
 * N - Current map size (# of buckets)
 * K - Current number of keys in the map
 * M - Number of keys to be added
 * R - The number of old keys to move during an incremental rehash
 * bound - A load factor boundary in range (0, 1)
 */
double compute_resize_factor(int N, int K, int M, int R, double bound) {
    int items_added = ceil((double) K / R) + K + M;
    int new_size = ceil((double) items_added / bound);
    return (double)new_size / N;
}

int matches_key(const void *elem, char *key) {
    hash_element_t *hash_elem = (hash_element_t *) elem;
    printd("[DEBUG] hash_map_utils.c::matches_key: hash_elem->key = %s, key = %s\n", hash_elem->key, key);
    return !strcmp(hash_elem->key, key);
}

/*
 * Initializes the map to a given `size`.
 */
void init_map(hash_map_t *map, int size) {
    map->primary = calloc(size, sizeof(void *));
    map->map_size = size;
    map->r_value = (int) ceil(1.0 / (DEFAULT_RESIZE_FACTOR - 1));
}

/*
 * Creates a new map to initiate incremental rehashing.
 */
void resize_map(hash_map_t *map, double factor) {
    map->temp = map->primary;
    map->temp_size = map->map_size;
    map->temp_index = 0;
    map->primary = calloc(map->map_size * (int) factor, sizeof(void *));
    map->map_size *= (int) factor;
    //printf("New Map Size = %d\n", map->map_size);
    map->num_keys = 0; 
    map->r_value = (int) ceil(1.0 / (factor - 1));
}

/*
 * Searches a map that implements incremental rehashing.
 * It is necessary to check both the old and new maps
 * when searching for a key.
 *
 * Returns NULL if no such key was found.
 */
hash_element_t *search(hash_map_t *map, char *key) {
    if (map->temp != NULL) {
        int index = compute_index(key, map->temp_size);
        dynamic_array_t *elem = map->temp[index];

        if (elem != NULL) {
            // Search inside dynamic array to find the matching key
            hash_element_t *t = find_item(elem, key, matches_key);

            if (t != NULL) {
                return t;
            }
        }
    }

    if (map->primary != NULL) {
        int index = compute_index(key, map->map_size);
        dynamic_array_t *elem = map->primary[index];

        prints("[DEBUG] hash_map_utils.c::search: elem = %p\n", elem);

        if (elem != NULL) {
            // Search inside dynamic array to find the matching key
            hash_element_t *t = find_item(elem, key, matches_key);

            if (t != NULL) {
                return t;
            }
        }
    }

    return NULL;
}

/*
 * Performs incremental rehashing on the map.
 */
void rehash_inc(hash_map_t *map) {
    for (int i = 0; i < map->r_value; i++) {
        // If there is nothing to rehash at the moment, return immediately.
        if (map->temp == NULL) {
            return;
        }

        // Iterate to next non-null value
        while (map->temp_index < map->temp_size && map->temp[map->temp_index] == NULL) {
            map->temp_index++;
        }

        // Check if temp map is empty
        if (map->temp_index == map->temp_size) {
            free(map->temp);
            map->temp = NULL;

            return;
        }

        hash_element_t *elem = pop_item(map->temp[map->temp_index], 0);
        int index = compute_index(elem->key, map->map_size);

        insert_item(&map->primary[index], elem);
        map->num_keys++;

        printd("[DEBUG] Rehashing %s into %d\n", elem->key, index);

        if (map->temp[map->temp_index]->size == 0) {
            free(map->temp[map->temp_index]);
            map->temp[map->temp_index] = NULL;
        }
    }
}

/*
 * Inserts an element into the map bucket, represented by a dynamic_array_t.
 */
void insert_item(dynamic_array_t **map, hash_element_t *elem) {
    if (*map == NULL) {
        *map = calloc(1, sizeof(dynamic_array_t));
    }
		
    array_insert(*map, elem, -1);
}

/*
 * Assumes that the element does not currently exist.
 */
void insert(hash_map_t *map, hash_element_t *elem, int added) {
    int index = compute_index(elem->key, map->map_size);

    double factor = compute_load_factor(map->num_keys + 1, map->map_size);
    prints("[DEBUG] factor = %.2lf\n", factor);
    
    if (factor >= LOAD_FACTOR) {
        printa("[DEBUG] Beginning rehash...\n");
        
        double resize_f = compute_resize_factor(map->map_size, map->num_keys, added, map->r_value, LOAD_FACTOR);
        prints("[DEBUG] Map Resize Factor = %lf\n", resize_f);
        // Begin rehash
        resize_map(map, resize_f);
    }

    printd("[DEBUG] Inserting %s at %d\n", elem->key, index);

    insert_item(&map->primary[index], elem);
    map->num_keys++;

    rehash_inc(map);
}

void insert_no_rehash(hash_map_t *map, hash_element_t *elem) {
	int index = compute_index(elem->key, map->map_size);
	
	printd("[DEBUG] Inserting %s at %d\n", elem->key, index);

    insert_item(&map->primary[index], elem);
    map->num_keys++;
}

