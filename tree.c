#include <stdio.h>
#include <stdlib.h>

/* All the text displayed to the user defined */
#define WELCOME_SCREEN "-=-=-=-=-=-=-=-=-=-=-[Welcome]-=-=-=-=-=-=-=-=-=-\n    /\\  /\\     Made by Miriam and Cas.    *\n   / O  O \\       * Balance Tree +\n   \\  I   /   *                          *\n   /      \\         *             *\n  / |    | \\    +           *                *\n  | |    | |        *                 +\n   W W  W W    *              +           * \n -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- \n Type help for help. Welcome to tree balancer. \n Console>"
#define BSIZE 100

typedef struct {
    void *LChild, *RChild;
    char *message;
    int key;
} tree;

/* function declarations of independence */
int compare_string(int start, int stop, char *s1, char *s2);

int main(void)
{
    char Buffer[BSIZE];
    printf(WELCOME_SCREEN);
    fgets(Buffer, BSIZE, stdin);
    if (compare_string(0, 4, Buffer, "help") == 0)
        printf("You typed help! Go fuck yourself\n");
    return 0;

}

int compare_string(int start, int stop, char *s1, char *s2)
{
    int cmp;
    for (int i = start; i < stop; i++)
        cmp = s1[i] - s2[i];
    return cmp;
}
