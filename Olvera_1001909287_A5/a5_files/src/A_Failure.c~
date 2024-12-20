#include "utils/hash_map_utils.h"
#include "customer.h"

int main() {
    hash_map_t *map = calloc(1, sizeof(hash_map_t));
    init_map(map, 4);
    
    printa("[DEBUG] Programm Running In Debug Version\n");
    
    int selection = 0;
    char str[20] = { 0 };
    char buffer[BUF_SIZE] = { 0 };
    
    
    while(selection != 5) {
        printf("**********************************\n");
        printf("  [ Main Menu ]\n");
        printf("1. Add Customer\n");
        printf("2. Import CSV File\n");
        printf("3. Customer Look Up\n");
        printf("4. Print Map\n");
        printf("5. Quit\n");
    
        printf("> ");
        scanf("%d", &selection);
        getchar();
        printf("<-------------------------------->\n");
    
        switch(selection) {
            case 1:
                printf("Enter Email: ");
                fgets(buffer, BUF_SIZE, stdin);
                trim(buffer);

                hash_element_t *elem = search(map, buffer);

                if(elem != NULL) {
                    printf("WARNING!!!\nCustomer Associated With [%s] Alredy Exists!\n", buffer);
                    printf("<-------------------------------->\n\n");
                    //print_customer(elem->value);
                    continue;
                }

                elem = calloc(1, sizeof(hash_element_t));
                elem->key = malloc(sizeof(char) * (strlen(buffer) + 1));
                strcpy(elem->key, buffer);

                customer_t *v = calloc(1, sizeof(customer_t));

                v->email = calloc(strlen(elem->key) + 1, sizeof(char));
                strcpy(v->email, elem->key);

                input_customer(v);

                elem->value = v;
                
                insert(map, elem, 1);
                printf("<-------------------------------->\n\n");
                break;    
            case 2:
                printf("Enter File Name: ");
                fgets(str, 20, stdin);
                trim(str);
                int num_cust = 0;
                int l = strlen(str);
            	if(str[l-4] == '.' && str[l-3] == 'c' && str[l-2] == 's' && str[l-1] == 'v') {
            		dynamic_array_t *customers = load_customers(str, map, &num_cust);
            		if(customers == NULL) {
            			continue;
            		}
            		printf("%d Entries To Be Entered...\n", num_cust);
            		
            		put_customers_in_map(map, customers, num_cust);
            		printf("Import Complete...\n");
            		
            	} else {
            		printf("Wrong File Type!\n");
            		printf("<-------------------------------->\n\n");
            	}                 
                break;
            case 3:
                printf("Enter Customer's Email: ");
                fgets(buffer, BUF_SIZE, stdin);
                trim(buffer);
                
                hash_element_t *elem1 = search(map, buffer);

                if(elem1 != NULL) {
                    printf("Customer Found!\n");
                    print_customer(elem1->value);
                } else {
                	printf("Customer Not Found!\n");
                }
                
                printf("<-------------------------------->\n\n");
               
                break;
            case 4:
                print_map(map->primary, map->map_size);
                printf("<-------------------------------->\n\n");
                break;
            case 5:
                printf("Bye...\n");
                break;
            default:
                printf("\nTHAT'S NOT WHAT I EXPECTED! DON'T BREAK ME!\n");
                break;
        } 
    }
    free_map(map);
    printf("**********************************\n");
    
    return 0;
}

void free_arr(dynamic_array_t *array) {
    if (array) {
    	for(int i = 0; i < array->size; i++) {
    		free(array->data[i]);
    	}
        /*free(elem->key);
        free(elem->value);
        free(elem);*/
    }
}

void free_map(hash_map_t *map) {
    if (map) {
        if (map->temp) {
            for (int i = 0; i < map->temp_size; i++) {
                free_arr(map->temp[i]);
                free(map->temp[i]);
            }

            free(map->temp);
        }

        if (map->primary) {
            for (int i = 0; i < map->map_size; i++) {
                free_arr(map->primary[i]);
                free(map->primary[i]);
            }

            free(map->primary);
        }

        free(map);
    }
}


void trim(char *str) {
    int l = strlen(str);
    if (str[l-1] == '\n') {
        str[l-1] = 0;
    }
}

void print_array(dynamic_array_t *array) {
    for (int i = 0; i < array->size - 1; i++) {
        hash_element_t *elem = array->data[i];
        printf("%s, ", ((customer_t *)elem->value)->email);
    }
    hash_element_t *elem = array->data[array->size - 1];
    printf("%s\n", ((customer_t *)elem->value)->email);
}

void print_map(dynamic_array_t **map, int array_size) {
    for (int i = 0; i < array_size; i++) {
        printf("map[%d] = ", i);
        if (map[i] == NULL) {
            printf("EMPTY\n");
        } else {
            print_array(map[i]);
        }
    }
}
