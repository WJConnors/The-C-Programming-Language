#include <stdio.h>

int main()
{
    /*long nc;

    nc = 0;
    while (getchar() != '\n') 
    ++nc;
    
    printf("%ld\n", nc);*/

    double nc;

    for (nc = 0; getchar() != '\n'; ++nc)
        ;
    printf("%.0f\n", nc);

}