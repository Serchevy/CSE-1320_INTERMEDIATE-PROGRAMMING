#include <stdio.h> 
#include <string.h>


void reverse_half(char str[64]);


int main()
{
    char str[64];
    
    printf("Enter a string: ");
    fgets(str, 64, stdin);
    
    int n = strlen(str);
    //Statement to get rif off "new line" char from read input
    if(str[n - 1] == '\n');
    {
        str[n - 1] = '\0';
    }
    
    reverse_half(str);


    return 0; 
}


void reverse_half(char str[64])
{
    int n = strlen(str);
    //This helps round up to the next letter for odd-numbbered words
    if((n % 2) != 0)
    {
        n++; 
    }
    //set i = (n/2) -1 becasue of how indices work
    for(int i = (n/2) - 1; i >= 0; i--)
    {
        printf("%c", str[i]);
    }
    
    for(int i = (n/2); i <= n; i++)
    {
        printf("%c", str[i]);
    }
    //Printed firt half of string backwards starting from half, and then printed out the rest. 
    printf("\n");
}
