#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define HALF_CIRCLE 180
#define FULL_CIRCLE 360


float rad_to_deg(float deg);


int main()
{

    float deg; 
    
    printf("Enter an angle in degrees: ");
    scanf("%f", &deg);
    
    // Print float to terminal through calling function
    printf("Angle in Radian is %0.2f\n", rad_to_deg(deg));    


    return 0; 
}


float rad_to_deg(float deg)
{
    // Change deg (the given) to positive
    if( deg < 0 )
    {
        deg = -1 * deg; 
    }
    // If deg (given) is bigger than 360 (2pi) loop until deg is smaller than 360. 360 is one cycle so it won't affect the degree. 
    while( deg > FULL_CIRCLE )
    {
       deg -= FULL_CIRCLE; 
    }
    // Simple equation to convert to radians
    float rad = deg * (M_PI / HALF_CIRCLE);

    return rad; 

}
