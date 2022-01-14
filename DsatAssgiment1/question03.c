// Q3. Given two strings A and B, check whether they are Anagrams of each other or not
// Submitted by Debonil Ghosh (M21AIE225)

#include <stdio.h>
#include <stdlib.h>

int strlen(char *s)
{
    int i = 0;
    while (*(s + i) != '\0')
        i++;
    return i;
}
void toLower(char *s)
{
    while (*s != '\0')
    {
        if (*s >= 65 && *s <= 90)
            *s = *s + 32;
        s++;
    }
}

int *letterCount(char *s)
{
    int *lc = (int *)malloc(sizeof(int) * 26);
    int i = 0;
    while (*(s + i) != '\0')
    {
        lc[*(s + i) - 'a']++;
        i++;
    }

    return lc;
}

int isAnagram(char *s1, char *s2)
{
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    if (l1 != l2)
        return 0;
    else
    {
        int *lc1 = letterCount(s1);
        int *lc2 = letterCount(s2);
        for (int i = 0; i < 26; i++)
        {
            if (lc1[i] != lc2[i])
                return 0;
        }
    }
    return 1;
}

int main()
{
    char s1[50], s2[50];
    printf("Enter a string 1\n");
    scanf("%s", s1);
    printf("Enter a string 2\n");
    scanf("%s", s2);

    printf("Strings are ");
    if (isAnagram(s1, s2))
    {
        printf("Anagram\n");
    }
    else
    {
        printf("Not Anagram\n");
    }

    return 0;
}
