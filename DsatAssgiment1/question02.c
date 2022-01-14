// Q2. Given a string S, check if it is a palindrome or not, without using libraries.
// Submitted by Debonil Ghosh (M21AIE225)

#include <stdio.h>

int strlen(char *s)
{
    int i = 0;
    while (*(s + i) != '\0')
        i++;
    return i;
}

int isPalindrome(char *s)
{
    int length = strlen(s);
    char *begin = s, *end = s + length - 1;
    for (int i = 0; i < length / 2; i++)
    {
        if (*end != *begin)
            return 0;

        begin++;
        end--;
    }
    return 1;
}

int main()
{
    char s[50];
    printf("Enter a string to check palindrome ...\n");
    scanf("%s", s);
    printf("String is...\n");
    if (isPalindrome(s))
    {
        printf("Palindrome\n");
    }
    else
    {
        printf("Not a Palindrome\n");
    }

    return 0;
}
