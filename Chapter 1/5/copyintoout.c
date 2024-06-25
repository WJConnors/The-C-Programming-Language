#include <stdio.h>

int main()
{
    int c;

    /*c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }*/
   
    while ((c = getchar()) != '\n') {
        putchar(c);
    }
    
}