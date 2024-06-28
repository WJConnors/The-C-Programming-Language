#include <stdio.h>

int atoi(char s[])
{
    int i, n;
    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}

int main()
{
    char s[] = "12345";
    printf("%d\n", atoi(s));
    char s2[] = "12345abc";
    printf("%d\n", atoi(s2));
    char s3[] = "abc12345";
    printf("%d\n", atoi(s3));
    return 0;
}