#include "customerqueue.h"


int main() {
    Node **cust_list = calloc(1, sizeof(Node));
    char str[20] = { 0 };
    int selection = 0;
    int num_cust = 0;
    FILE *fp;
    
    while(selection != 4) {
        printf("**********************************\n");
        printf("  [ Main Menu ]\n");
        printf("1. Load CSV File\n");
        printf("2. Process Next\n");
        printf("3. View Queue\n");
        printf("4. Quit\n");
    
        printf("Enter Selection: ");
        scanf("%d", &selection);
        getchar();
        printf("----------------------------------\n");
        
        //  LOAD DATA
        if(selection == 1) { 
            printf(">Enter File Name: ");
            fgets(str, 20, stdin);
            trim(str);
            int l = strlen(str);
            if(str[l-4] == '.' && str[l-3] == 'c' && str[l-2] == 's' && str[l-1] == 'v') {
                fp = fopen(str, "r");
                if(!fp) {
                    printf("Error Opeing File!\n");
                    continue;
                }
                printf("\nLoaded [%d] Customers From File...\n", load_csv(fp, &cust_list, &num_cust));
                printf("**********************************\n\n");
            } 
            else {
                printf("Wrong File Type!\n\n"); 
                continue;
            } 
        }// PROCESS NEXT CUSTOMER
        else if(selection == 2) { 
            process_data(cust_list, &num_cust);
            if(num_cust < 5) {
                printf("\nLoaded [%d] Customers From File...\n", load_csv(fp, &cust_list, &num_cust));
            }
            printf("**********************************\n\n");
        }// DISPLAY THE DATA ON QUEUE
        else if(selection == 3) {
            if(cust_list == NULL) {
                printf("There Is No Data....\n");
                continue;
            }
            display_data(cust_list);
            printf("**********************************\n\n");
        }// QUIT BUT WITH EXTRA STEPS
        else if(selection == 4) {
            break;
        }// IF SELECTION IS.... UNEXPECTED
        else {
            printf("\nTHAT'S NOT WHAT I EXPECTED! DON'T BREAK ME!\n");
        }
    }
    free_data(*cust_list);
    printf("**********************************\n");
    
    return 0;
}

void trim(char *str) {
    int l = strlen(str);
    if (str[l-1] == '\n') {
        str[l-1] = 0;
    }
}

void free_data(Node *cust_list) {
    if(cust_list != NULL) {
        custq_t *c = cust_list->data;
        free(c->name);
        free(c->address);
        free(c->email);
        free(c);
        Node *n = cust_list->next;
        free(cust_list);
        free_data(n);
    }
}

int load_csv(FILE *fp, Node ***cust_list, int *num_cust) {    
        custq_t *temp = NULL;
        
        char buffer[256] = { 0 };
        int num_customers = 0;
        
        while(*num_cust < 10 && fgets(buffer, 256, fp)) {
            trim(buffer);
            temp = line(buffer);
            
            if(temp) { 
                Node *n = create_node(temp);
                insert_node(*cust_list, n);
            }
            num_customers++;
            (*num_cust)++;
        }
        if(feof(fp)){
            fclose(fp);
        }
        return num_customers;
}

custq_t *line(char *buffer) {
    custq_t *customer = calloc(1, sizeof(custq_t));
  
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
    
    if(num_feature != 4) {
        if(customer->name) {
            free(customer->name);
        }
        if(customer->address) {
            free(customer->address);
        }
        if(customer->email) {
            free(customer->email);
        }
        free(customer);
        customer = NULL;
    } 
      
    return customer;
}

void process_data(Node **cust_list, int *num_cust) {
    printf("\nProcessing customer...\n");
    Node *temp = NULL;
    printf("%-10d", (*cust_list)->data->id);
    printf("%-25s", (*cust_list)->data->name);
    printf("%-30s", (*cust_list)->data->address);
    printf("%-25s\n", (*cust_list)->data->email);
    temp = *cust_list;
    *cust_list = (*cust_list)->next;
    free(temp);
    *num_cust = *num_cust - 1;
}

void display_data(Node **cust_list) { 
    printf("\nCurrent Queue\n=============\n");
    int n = 0;
    Node *head = *cust_list;
    while(head != NULL) {
        printf("%d. %-10d", n + 1, head->data->id);
        printf("%-25s", head->data->name);
        printf("%-30s", head->data->address);
        printf("%-25s\n", head->data->email);
        head = head->next;
        n++;
    }
    free_data(head);
}

Node *create_node(custq_t *temp) {
    Node *n = malloc(sizeof(Node));
    n->data = malloc(sizeof(custq_t));
    n->data = temp;

    return n;
}

void insert_node(Node **head, Node *new_node) {
    Node *prev = NULL;
    Node *current = *head;

    while (current != NULL) {
        prev = current;
        current = current->next;
    }

    if (current == *head) {
        new_node->next = current;
        *head = new_node;
    } else {
        new_node->next = current;
        prev->next = new_node;
    }
}

