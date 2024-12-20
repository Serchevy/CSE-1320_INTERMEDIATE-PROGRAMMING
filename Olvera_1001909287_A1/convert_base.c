#include <stdio.h> 
#include <string.h>


void convert_base(int n);


int main()
{
    int n;
    
    printf("Enter an integer: ");
    if(scanf("%d", &n) != 1)
    {
        printf("INVALUD INPUT!\n"); 
        return 0;
    }
    
    //printf("%x\n", n);
    
    convert_base(n);
    
    printf("\n");


    return 0;
}


void convert_base(int n)
{
    int rem, i;
    char hxn[32];
     
    while( n != 0)
    {
        rem = n%16;
        
        if(rem < 10)
        {
            rem += 48; 
        }
        else
        { 
            rem += 55; 
        } 
        
        hxn[i] = rem;
        i++;
        
        n = n/16;
    }

    for(i -= 1; i >= 0; i--)
    {
        printf("%c", hxn[i]);
    }  

// This equation creates a correlation bewteen values in decimal, hexadecimal, and character
// For intance, decimal 65 to hexadecimal. Take the remainder of 65%16 = 1
// add 48 + 1 = 49, which = "char 1"
// then 65/16 = 4
// since n != 0 loop again and the remainder of 4%16 = 4
// add 48 + 4 = 52, which = "char 4"
// 4/16 = 0. loop ends
// char 1 = 31 in hex 
// char 4 = 34 in hex 
// added together = 65
// print chars backwards and sodecimal 65 is 41 in hex.   
    
}



