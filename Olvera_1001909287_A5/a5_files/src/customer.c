#include "customer.h"
#include "utils/hash_map_utils.h"

/*
 * Reads in customer data for a single customer from the user.
 * If the input customer is NOT NULL, only the NON-NULL entries
 * will be requested from the user.
 */
customer_t *input_customer(customer_t *c) {
    char buffer[BUF_SIZE] = { 0 };

    if (c == NULL) {
        c = calloc(1, sizeof(customer_t));
    }

    if (c->id == 0) {
        printf("Enter ID: ");
        scanf("%d", &c->id);
        while (getchar() != '\n');
    }

    if (c->name == NULL) {
        printf("Enter name: ");
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strlen(buffer) - 1] = 0;
        c->name = calloc(strlen(buffer) + 1, sizeof(char));
        strcpy(c->name, buffer);
    }

    if (c->address == NULL) {
        printf("Enter address: ");
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strlen(buffer) - 1] = 0;
        c->address = calloc(strlen(buffer) + 1, sizeof(char));
        strcpy(c->address, buffer);
    }

    if (c->email == NULL) {
        printf("Enter email: ");
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strlen(buffer) - 1] = 0;
        c->email = calloc(strlen(buffer) + 1, sizeof(char));
        strcpy(c->email, buffer);
    }

    return c;
}

/*
 * Loads customers from a file.
 * If `keys` is NOT NULL, this function will not save any customer
 * that has a key in `keys`.
 */
dynamic_array_t *load_customers(char *filename, hash_map_t *map, int *num_cust) {
    dynamic_array_t *customers = { 0 };
    
    FILE *fp = fopen(filename, "r"); //Open File
    if(!fp) {
		printf("Error Opeing File!\n");
        return customers;
	}
    
    customer_t *temp = NULL; //Temp Customer Struct
    
    char buffer[256] = { 0 };
        
    while(fgets(buffer, 256, fp)) {
		trim(buffer);
		temp = parse_line(buffer); //Parse line
		
		hash_element_t *elem = search(map, temp->email); //search for key
		if(elem != NULL) {
			//If key exists, free memory for customer
            free(temp->name);
            free(temp->address);
            free(temp->email);
        	free(temp);
        } else {
        	elem = calloc(1, sizeof(hash_element_t));
            elem->key = malloc(sizeof(char) * (strlen(temp->email) + 1));
            strcpy(elem->key, temp->email);
            elem->value = temp;
        	insert_item(&customers, elem); //otherwise add to dynamic array
        } 
        (*num_cust)++;
    }
    
    fclose(fp);
    return customers;
}

void put_customers_in_map(hash_map_t *map, dynamic_array_t *customers, int n_keys) {
	double resize_f = compute_resize_factor(map->map_size, map->num_keys, n_keys, 6, LOAD_FACTOR);
	prints("[DEBUG] Resize Factor = %lf\n", resize_f);
	printf("Beginning rehash...\n");
	resize_map(map, resize_f); //call resize_map

	for(int i = 0; i < n_keys; i++) {	//loop trhu customers
		hash_element_t *elem = customers->data[i];
		insert_no_rehash(map, elem); //insert each via insert_no_rehash
	}	
}

void print_customer(customer_t *c) {
    printf("%-10d%-15s%-20s%-20s\n", c->id, c->name, c->address, c->email);
}

customer_t *parse_line(char *buffer) {
    customer_t *customer = calloc(1, sizeof(customer_t));
  
    int num_feature = 0;
    char *token = strtok(buffer, ",");

    while (token) {
        switch (num_feature) {
            case 0:
                customer->id = atoi(token);
                break;
            case 1:
                customer->name = malloc((strlen(token) + 1) * sizeof(char));
                strcpy(customer->name, token);
                break;
            case 2:
                customer->address = malloc((strlen(token) + 1) * sizeof(char));
                strcpy(customer->address, token);
                break;
            case 3:
                customer->email = malloc((strlen(token) + 1) * sizeof(char));
                strcpy(customer->email, token);
                break;
        }
        num_feature++;
        token = strtok(NULL, ",");
    }
      
    return customer;
}

