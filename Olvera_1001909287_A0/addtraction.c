#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 8

float addtraction(float arr1[], float arr2[], int n );


int main()
{
    
    float arr1[SIZE];
    float arr2[SIZE];
    int n = SIZE; 

    printf("Enter %d numbers: ", n*2);

    // Basic loop to store the values in the respetive array
    for(int i = 0; i < SIZE*2; i++)
    {
        if( i < SIZE)
        {
	    scanf("%f", &arr1[i]);
	    }
        else
        {
            scanf("%f", &arr2[i - SIZE]);
        }
    }
    
    // Call function inside new variable and then print variable to terminal
    float num = addtraction(arr1, arr2, n);
    
    printf("%0.2f\n", num);


    return 0;
}

float addtraction(float arr1[], float arr2[], int n )
{
    float result = 0;
    
    // Statement to loop through arrays 
    for( int i = 0; i < n; i++)
    {
        float sum = 0;
        sum = arr1[i] + arr2[i]; 
        // Statement to check for even or odd indices and  add or substract, respectively 
        if( i % 2 == 0)
        {
            result += sum;
        }
        else 
        {
            result -= sum;
        }
    }

    return result;
}

