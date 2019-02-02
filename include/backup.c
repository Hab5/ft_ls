#include <stdio.h>

int function();

int main()
{
    function();
    return 0;
}

int function()
{
    int *ptr;
    int chiffre;
    chiffre = 0;
    ptr = &chiffre;
    printf("Chiffre avant boucle : %d\n", *ptr);

    while(chiffre <= 10)
    {
        printf("Chiffre : %d\n", (int)ptr);
        chiffre = chiffre + 1;
        ptr = &chiffre;
    }

    return 0;
}