// Q1. Write a program to reverse a string without using libraries.
// Submitted by Debonil Ghosh (M21AIE225)

#include <stdio.h>

int strlen(char *s)
{
    int i = 0;
    while (*(s + i) != '\0')
        i++;
    return i;
}

void reverse(char *s)
{
    int length = strlen(s);
    char *begin = s, *end = s + length - 1;
    for (int i = 0; i < length / 2; i++)
    {
        char temp = *end;
        *end = *begin;
        *begin = temp;

        begin++;
        end--;
    }
}

int main()
{
    char s[50];
    printf("Enter a string to reverse...\n");
    scanf("%s", s);
    printf("Reversed string is...\n");
    reverse(s);
    printf("%s\n", s);
    return 0;
}
