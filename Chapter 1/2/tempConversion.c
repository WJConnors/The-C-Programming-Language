#include <stdio.h>

int main()
{
    float fahr;
    int lower, upper, step;

    lower = 0;      // lower limit of temperature table
    upper = 300;    // upper limit
    step = 20;      // step size

    fahr = lower;

    printf("Fahrenheit to Celsius Conversion Table\n");

    while (fahr <= upper)
    {
        float celsius = (5.0/9.0) * (fahr-32.0);
        printf("%3.0f\t%6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

    printf("\nCelsius to Fahrenheit Conversion Table\n");

    float celsius = lower;
    
    while (celsius <= upper)
    {
        fahr = (celsius * 9.0/5.0) + 32.0;
        printf("%3.0f\t%3.1f\n", celsius, fahr);
        celsius = celsius + step;
    }

}