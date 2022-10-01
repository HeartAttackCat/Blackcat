#include <stdio.h>
#include <stdlib.h>

/* All the text displayed to the user defined */
#define WELCOME_SCREEN "-=-=-=-=-=-=-=-=-=-=-[Welcome]-=-=-=-=-=-=-=-=-=-\n    /\\  /\\     Made by Miriam and Cas.    *\n   / O  O \\       * Balance Tree +\n   \\  I   /   *                          *\n   /      \\         *             *\n  / |    | \\    +           *                *\n  | |    | |        *                 +\n   W W  W W    *              +           * \n -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- \n Type help for help. Welcome to tree balancer. \n Console>"
#define BSIZE 100
struct  tree{
    struct tree *LChild, *RChild, *Parent;
    char *message;
    int key, depth;
};

/* function declarations of independence */
int compare_string(int start, int stop, char *s1, char *s2);
struct tree *initize_node(struct tree *parent, char *message, int key, int dep);
char *message(void);
int priorinput(void);


int main(void)
{
    char Buffer[BSIZE];
    printf(WELCOME_SCREEN);
    fgets(Buffer, BSIZE, stdin);
    if (compare_string(0, 4, Buffer, "help") == 0)
        printf("You typed help! Print help page\n");
    return 0;

}


/**
 * @brief Compares two strings at a start and end. If it returns a value greater then 0 then they are incorrect
 * 
 * @param start Start index
 * @param stop Stop index
 * @param s1 pointer to string one
 * @param s2 pointer to string two
 * @return int the comparison value
 */
int compare_string(int start, int stop, char *s1, char *s2)
{
    int cmp;
    for (int i = start; i < stop; i++)
        cmp = s1[i] - s2[i];
    return cmp;
}


/**
 * @brief a function for grabbing messages.
 * 
 * @return the user input.
 */
char *message(void)
{

    char buff[100];
    printf("What message are we storing: ");
    fgets(buff, 100, stdin);
    return buff;
}


/**
 * @brief a quick function for getting a key value.
 * 
 * @return the users input key value.
 */
int priorinput(void)
{
    char buff[100];
    int val;
    printf("What message are we storing: ");
    fgets(buff, 100, stdin);
    sscanf(buff, "%d", &val);
    return buff;  

}


/**
 * @breif initalizes a tree node first mallocs the space for the tree and then fills out the required
 * variables.
 * 
 * @param parent the parent of the node we are creating.
 * @param message the message we are storing.
 * @param the priority of the element.
 * @return the memory address of the new element
 */
struct tree *initize_node(struct tree *parent, char *message, int key, int dep)
{
    struct tree *new = malloc(sizeof(struct tree));
    if (!new){
        printf("Malloc failed closing");
        exit(0);
    }
    new->Parent = parent;
    new->message = message;
    new->key = key;
    new->LChild = NULL;
    new->RChild = NULL;
    return new;
}
