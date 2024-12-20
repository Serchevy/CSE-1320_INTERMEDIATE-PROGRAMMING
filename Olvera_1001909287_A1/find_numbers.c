#include <stdio.h> 
#include <string.h>

void find_numbers(int arr[32], int pnt1, int pnt2);

int main()
{
    
    int arr[32];
    int pnt1; 
    int pnt2; 
    int i; 
    int n;
    
    printf("Enter your numbers (MAX 32): ");
    for(i = 0; i < 32; i++)
    {   
        n = scanf("%d", &arr[i]);
        
        if(n != 1) //if not read successfully then get character and break out of loop
        {
            getchar(); // This allows the rest of the code to run
            break;
        }
    }
    
    printf("Enter a range: ");
    scanf("%d", &pnt1);
    scanf("%d", &pnt2);
    
    find_numbers(arr, pnt1, pnt2);
    
    return 0; 
}

void find_numbers(int arr[32], int pnt1, int pnt2)
{
    int i;
    
    for(i = 0; i < 32; i++)
    {
        if(arr[i] >= pnt1 && arr[i] <= pnt2)
        {
            printf("[%d], %d\n", i, arr[i]); 
        }
    }
    
}





