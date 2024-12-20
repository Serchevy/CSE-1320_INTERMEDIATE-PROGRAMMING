#include "customerdb.h"

int main() {
    
    custdb_t **data = NULL;
    int selection = 0;
    int n_cus = 0;
    
    while(selection != 7) {
        printf("******************************\n");
        printf("  [ Main Menu ]\n");
        printf("1. Load CSV File\n");
        printf("2. Load Binary File\n");
        printf("3. Display Data\n");
        printf("4. Add Entry\n");
        printf("5. Export as CSV\n");
        printf("6. Export as Binary\n");
        printf("7. Quit\n");
    
        printf("Enter Selection: ");
        scanf("%d", &selection);
        getchar();
        printf("------------------------------\n");
    
        char str[20] = { 0 };
      
        if(selection == 1) {
            printf(">Enter File Name: ");
            fgets(str, 20, stdin);
            trim(str);
            printf("Number of Samples Loaded From File: %d\n", csv_file(str, &data, &n_cus));
            printf("Number Of Customers Stored In Data: %d\n", n_cus);
            printf("******************************\n");
            printf("\n");
        }
        else if(selection == 2) {
            printf(">Enter File Name: ");
            fgets(str, 20, stdin);
            trim(str);
            printf("Number of Samples Loaded From File: %d\n", b_file(str, &data, &n_cus));
            printf("Number Of Customers Stored In Data: %d\n", n_cus);
            printf("******************************\n");
            printf("\n");
        }
        else if(selection == 3) {
            if(data == NULL) {
                printf("There Is No Data To Display\nLoad Some Data Fisrt Or Add Entry(s)\n");
                continue;
            }
            display_data(&data, &n_cus);
            printf("******************************\n");
            printf("\n");
        }
        else if(selection == 4) {
            printf("Please Input Data For New Customer.\n");
            printf("Number Of Customers Stored In Data: %d\n", add_entry(&data, &n_cus));
            printf("******************************\n");
            printf("\n");
        }
        else if(selection == 5) {
            if(data == NULL) {
                printf("There Is No Data In Memory!\nYou Require Data In Order To Save!\n");
                continue;
            }
            else {
                save_csv(&data, &n_cus);
                printf("******************************\n");
                printf("\n");
            }
        }
        else if(selection == 6) {
            if(data == NULL) {
                printf("There Is No Data In Memory!\nYou Require Data In Order To Save!\n");
                continue;
            }
            else {
                save_bfile(&data, &n_cus);
                printf("******************************\n");
                printf("\n");
            }
        }
        else if(selection == 7) {
            break;
        }
        else {
            printf("\n");
            printf("THAT'S NOT WHAT I EXPECTED! DON'T BREAK ME!\n");
        }
    }
    free_data(&data, &n_cus);
    printf("******************************\n");
    return 0;
}


int csv_file(char *str, custdb_t ***data, int *n_cus) {
    int l = strlen(str);
    if(str[l-4] == '.' && str[l-3] == 'c' && str[l-2] == 's' && str[l-1] == 'v') {
        FILE *fp = fopen(str, "r");
        
        if(!fp) {
            printf("Error Opeing File!\n");
            return 0;
        }
        
        custdb_t *temp = NULL;
        
        char buffer[256] = { 0 };
        int num_customers = 0;
        
        while(fgets(buffer, 256, fp)) {
            trim(buffer);
            temp = line(buffer);

            if(temp) { 
                *data = realloc(*data, ((*n_cus) + 1) * sizeof(custdb_t *));
                (*data)[*n_cus] = temp;
            }
            num_customers++;
            (*n_cus)++;
        }

        fclose(fp);
        
        return num_customers;
    }
    else {
       printf("Wrong File Type!\n"); 
       return 0;
    }   
}

custdb_t *line(char *buffer) {
    custdb_t *customer = calloc(1, sizeof(custdb_t));
  
    int num_feature = 0;
    char *token = strtok(buffer, ",");

    while (token) {
        switch (num_feature) {
            case 0:
                customer->ID = atoi(token);
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


void trim(char *str) {
    int l = strlen(str);
    if (str[l-1] == '\n') {
        str[l-1] = 0;
    }
}

void free_data(custdb_t ***data, int *n_cus) {
    for (int i = 0; i < *n_cus; i++) {
        free((*data)[i]->name);
        free((*data)[i]->address);
        free((*data)[i]->email);
        free((*data)[i]);
    }
    free(*(data));
}


int b_file(char *str, custdb_t ***data, int *n_cus) {
    FILE *fp = fopen(str, "rb");
        
    if(!fp) {
        printf("Error Opeing File!\n");
        return 0;
    }
    
    char a;
    char b;
    fread(&a, 1, 1, fp);
    fread(&b, 1, 1, fp);
    
    if(a == 0x13 && b == 0x20) {
        int num_customers = 0;
    
        while(1) {
            custdb_t *temp = read_entry(fp);
            
            if(temp) {
                *data = realloc(*data, ((*n_cus) + 1) * sizeof(custdb_t *));
                (*data)[*n_cus] = temp;
            }
            if(feof(fp)) {
                break;
            }
            num_customers++;
            (*n_cus)++;
        }
        fclose(fp);
        return num_customers;
    }
    else {
        fclose(fp);
        printf("Wrong File Type!\n"); 
        return 0;
    }    
}

custdb_t *read_entry(FILE *fp) {
    custdb_t *c = calloc(1, sizeof(custdb_t));
    
    fread(&c->ID, 1, sizeof(int), fp);
    c->name = readstring(fp);
    c->address = readstring(fp);
    c->email = readstring(fp);
    
    return c;
}

void free_cust(custdb_t *c) {
    free(c->name);
    free(c->address);
    free(c->email);
    free(c);
}

char *readstring(FILE *fp) {
    long p = ftell(fp);
    int count = 0;
    
    while(fgetc(fp) && !feof(fp)) { 
        count++;
    }
    
    char *str = calloc(count + 1, sizeof(char));
    fseek(fp, p, SEEK_SET);
    fread(str, sizeof(char), count + 1, fp);
    
    return str;
}


void display_data(custdb_t ***data, int *n_cus) { 
    if(data == NULL) { 
        printf("There Is No Data To Display\n");
    }   
    else {
        for(int i = 0; i < *n_cus; i++) {
            printf("ID: %-10d", (*data)[i]->ID);
            printf("Name: %-25s", (*data)[i]->name);
            printf("Address: %-30s", (*data)[i]->address);
            printf("E-mail: %-25s\n", (*data)[i]->email);
        }
    }
} 


int add_entry(custdb_t ***data, int *n_cus) { 
    int add_ID = 0;
    char add_name[20] = { 0 };
    char add_address[20] = { 0 };
    char add_email[20] = { 0 };
    
    printf(">Enter ID: ");
    scanf("%d", &add_ID);
    getchar();
    printf(">Enter Name: ");
    fgets(add_name, 20, stdin);
    trim(add_name);
    printf(">Enter Address: ");
    fgets(add_address, 20, stdin);
    trim(add_address);
    printf(">Enter Email: ");
    fgets(add_email, 20, stdin);
    trim(add_email);
    
    custdb_t *temp = calloc(1, sizeof(custdb_t));
    *data = realloc(*data, (*n_cus + 1) * sizeof(custdb_t *));
    
    temp->ID = add_ID;
    temp->name = malloc((strlen(add_name) + 1) * sizeof(char));
    strcpy(temp->name, add_name);
    temp->address = malloc((strlen(add_address) + 1) * sizeof(char));
    strcpy(temp->address, add_address);
    temp->email = malloc((strlen(add_email) + 1) * sizeof(char));
    strcpy(temp->email, add_email);
    
    (*data)[*n_cus] = temp;
    
    printf("New Customer Added!\n");
    (*n_cus)++;

    return *n_cus;
} 


void save_csv(custdb_t ***data, int *n_cus) {
    int done_for = 0;
    while(1) {
        char str[20] = { 0 };
        if(done_for == 0 ) {
            printf("Enter Name For File: ");
            done_for++;
        }
        else {
            printf("Enter Another Name For File: ");
        }
        fgets(str, 20, stdin);
        trim(str);
        
        FILE *fp;
        
        if((fp = fopen(str, "r"))) {
            fclose(fp);
            
            char option;
            printf("File Alredy Exists! Do You Wish To Overwrite It (Y/N)? ");
            scanf("%c", &option);
            getchar();
            if(option == 'Y') {
                fp = fopen(str, "w+");
                if(!fp) {
                    printf("Error Opeing File!\n");
                    return;
                }
                
                for(int i = 0; i < *n_cus; i++) {
                    fprintf(fp,"%d,%s,%s,%s\n", (*data)[i]->ID, (*data)[i]->name, (*data)[i]->address, (*data)[i]->email);
                }
                fclose(fp);
                printf("File Saved Successfully!\n");
                return;
            }
        }
        else {
            fp = fopen(str, "w+");  
            if(!fp) {
                printf("Error Opeing File!\n");
                return;
            }
            
            for(int i = 0; i < *n_cus; i++) {
                fprintf(fp,"%d,%s,%s,%s\n", (*data)[i]->ID, (*data)[i]->name, (*data)[i]->address, (*data)[i]->email);
            } 
            fclose(fp); 
            printf("File Saved Successfully!\n");
            return;
        }
    }
}



void save_bfile(custdb_t ***data, int *n_cus) {
    int done_for = 0;
    while(1) {
        char str[20] = { 0 };
        if(done_for == 0 ) {
            printf("Enter Name For File: ");
            done_for++;
        }
        else {
            printf("Enter Another Name For File: ");
        }
        fgets(str, 20, stdin);
        trim(str);
        
        FILE *fp;
        
        if((fp = fopen(str, "r"))) {
            fclose(fp);
            
            char option;
            printf("File Alredy Exists! Do You Wish To Overwrite It (Y/N)? ");
            scanf("%c", &option);
            getchar();
            if(option == 'Y') {
                fp = fopen(str, "wb+");
                if(!fp) {
                    printf("Error Opeing File!\n");
                    return;
                }
                
                char a = 0x13;
                char b = 0x20;
                fwrite(&a, 1, 1, fp);
                fwrite(&b, 1, 1, fp);
                
                for(int i = 0; i < *n_cus; i++) {
                    int id = (*data)[i]->ID;
                    fwrite(&id, sizeof(id), 1, fp);
    
                    char *name = (*data)[i]->name;
                    char *address = (*data)[i]->address;
                    char *email = (*data)[i]->email;
    
                    fwrite(name, sizeof(char), strlen(name) + 1, fp);
                    fwrite(address, sizeof(char), strlen(address) + 1, fp);
                    fwrite(email, sizeof(char), strlen(email) + 1, fp); 
                }
                
                fclose(fp);
                printf("File Saved Successfully!\n");
                return;
            }
        }
        else {
            fp = fopen(str, "w+");  
            if(!fp) {
                printf("Error Opeing File!\n");
                return;
            }
            
            char a = 0x13;
            char b = 0x20;
            fwrite(&a, 1, 1, fp);
            fwrite(&b, 1, 1, fp);
                
            for(int i = 0; i < *n_cus; i++) {
                int id = (*data)[i]->ID;
                fwrite(&id, sizeof(id), 1, fp);
    
                char *name = (*data)[i]->name;
                char *address = (*data)[i]->address;
                char *email = (*data)[i]->email;
    
                fwrite(name, sizeof(char), strlen(name) + 1, fp);
                fwrite(address, sizeof(char), strlen(address) + 1, fp);
                fwrite(email, sizeof(char), strlen(email) + 1, fp); 
            }
            
            fclose(fp); 
            printf("File Saved Successfully!\n");
            return;
        }
    }
    
} 


