/*
Q. 1) Alice has a standard deck of 52 cards. She wants to play a card game with K−1
of her friends. This particular game requires each person to have an equal
number of cards, so Alice needs to discard a certain number of cards from her
deck so that she can equally distribute the remaining cards amongst her and her
friends. Find the minimum number of cards Alice has to discard such that she
can play the game.

 Submitted by Debonil Ghosh (M21AIE225)
*/

#include <stdio.h>

int main()
{
    int T, k;
    scanf("%d", &T);

    while (T--)
    {
        scanf("%d", &k);
        printf("%d \n", 52%k);
    }

    return 0;
}
