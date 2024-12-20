#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define SIZE 64


int main()
{
    // char a is a temporary holder. It will be used later for the letter swap
    char str[SIZE], a;
    int indx_1, indx_2;
    
    printf("Enter a string (up to 64 characters): ");
    fgets(str, SIZE, stdin);
    
    printf("Enter index 1: ");
    scanf("%d", &indx_1);
    
    printf("Enter index 2: ");
    scanf("%d", &indx_2);
    
    // I first verify that both indices are valid and if so I proceed to use the temporary char-holder to swap the leters and then print string to terminal. 
    if (( indx_1 >= 0 && indx_1 < SIZE) && (indx_2 >= 0 && indx_2 < SIZE))
    {
        a = str[indx_1];
        str[indx_1] = str[indx_2];
        str[indx_2] = a;
        
        printf("%s", str);
    }
    else
    {
        printf("Error! Invalid Indices\n");
        return 0;
    }
   
    return 0;
 
}



