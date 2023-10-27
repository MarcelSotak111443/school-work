#include <stdio.h>
#include <math.h>
#include <float.h>

double sinus(double radiants,double epsilon);
double factorial(int n);
#define M_PI 3.14159265358979323846
int main() {


    int radiant;
    double shortenRadiant;
    double doubleEpsilon = 1.0f;
    scanf("%d",&radiant);

    shortenRadiant = radiant-((radiant/360)*360);
    shortenRadiant = shortenRadiant * M_PI/180.0f;

    while ((1 + doubleEpsilon / 2 ) != 1.0)
    {
        doubleEpsilon = doubleEpsilon / 2;
    }
    printf("epsilon je %.35f \n", doubleEpsilon);

    sinus(shortenRadiant, doubleEpsilon);
    return 0;
}
double sinus( double radiants, double epsilon){

     double sum=0,x,y,division=1,help;
     int n = 0;

     do {
        x = (pow(-1.0f,n))*(pow(radiants,2.0f*n+1.0f));
        y = (factorial(n));
        division = x/y;
        sum = sum + division;
        help = division;
        printf(" X je %lf Y JE %lf",x,y);
        printf(" zlomok je %lf  ",division);
        printf(" suma je %lf \n ",sum);
        n++;

    } while (fabs(help) > epsilon);

     printf("\n vysledok je %lf",sum);
}
double factorial(int n){
    int f = 2*n + 1;
    float fact = 1;

    for (int i = 1; i <= f; ++i) {
        fact *= i;
    }
    return fact;
}