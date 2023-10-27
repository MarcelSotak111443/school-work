#include <stdio.h>
#include <float.h>


int main()
{
    float floatEpsilon = 1.0f;
    double doubleEpsilon = 1.0f;

    while ((1 + floatEpsilon / 2 ) != 1.0)
    {
        floatEpsilon = floatEpsilon / 2;
    }
    printf("F epsilon = %e \n", floatEpsilon);

    while((1 + doubleEpsilon /2 ) != 1.0 )
    {
        doubleEpsilon = doubleEpsilon / 2;
    }
    printf("D epsilon = %e \n", doubleEpsilon );

    printf( "FLT_EPSILON = %e\n" , FLT_EPSILON );
    printf( "DBL_EPSILON = %e\n" , DBL_EPSILON );

    return 0;

}
