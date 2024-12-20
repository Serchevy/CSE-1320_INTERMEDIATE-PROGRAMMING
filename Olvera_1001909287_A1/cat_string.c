#include <stdio.h> 
#include <string.h>


void cat_string(char str1[128], char str2[128]);


int main()
{
    char str1[128];
    char str2[128];
    int l1, l2;
    
    printf("Enter fisrt string: ");
    fgets(str1, 128, stdin);
    l1 = strlen(str1);
    //Statement to get rif off "new line" char from read input
    if(str1[l1 - 1] == '\n');
    {
        str1[l1 - 1] = '\0';
    }
    
    printf("Enter second string: "); 
    fgets(str2, 128, stdin);
    l2 = strlen(str2);
    if(str2[l2 - 1] == '\n');
    {
        str2[l2 - 1] = '\0';
    }
    
    cat_string(str1, str2);

    return 0; 
}

void cat_string(char str1[128], char str2[128])
{
    char c;
    int cons1 = 0;
    int cons2 = 0;
    
    //Statement to determine number of consonants based on vowels
    //Also, empty spaces and new lines are considered
    for(int i = 0; str1[i] != '\0'; i++)
    {
        c = str1[i];
        
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' 
         || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == ' ' || c == '\n')
        {
            continue;
        }
        else
        {
            cons1++; 
        }
    }
    for(int i = 0; str2[i] != '\0'; i++)
    {
        c = str2[i];
        
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' 
         || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == ' ' || c == '\n')
        {
            continue;
        }
        else
        {
            cons2++; 
        }
    }
    
    //Statement which determines which string gets copied first
    if(cons1 > cons2)
    {
        strcat(str1, str2);
        printf("%s\n", str1);
    }
    else
    {
        strcat(str2, str1);
        printf("%s\n", str2);
    }
    
 	//printf("str1 has %d consonants and str2 has %d consonants\n", cons1, cons2);
    
}




