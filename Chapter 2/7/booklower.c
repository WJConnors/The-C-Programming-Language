#include <stdio.h>

int lower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;
}

int main()
{
    char s[] = "Hello, World!";
    for (int i = 0; s[i] != '\0'; ++i)
        printf("%c", lower(s[i]));
    printf("\n");
    return 0;
}