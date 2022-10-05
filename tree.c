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
struct tree *initize_node(struct tree *parent, char *message, int key);
char *message(void);
int priorinput(void);
struct tree *find(int key, struct tree *head);

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
 * @brief finds a given value based upon its key value. Keeps going until it
 * finds it.
 * @param key the key value we are looking for.
 * @param head the head of the tree we are looking.
 * @return the string we are looking for.
 */
struct tree *find(int key, struct tree *head)
{
    if (head != NULL){
        if(key == head->key){
            printf("%d with message %s located at depth %d\n", key, head->message, head->depth);
            return head;
        } else if (key < head->key){
            find(key, head->LChild);
        } else {
            find(key, head->RChild);
        }
    } else{
        printf("ERROR | Node does not exist\n");
        return NULL;
    }

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
 * @brief perfroms an in order traversal of a tree.
 * 
 * @param head the head of the tree or the curretn node we are in.
 */ 
void inorder(struct tree *head)
{
    if (head != NULL){
        inorder(head->LChild);
        printf("%s | Key: %d. ", head->message, head->key);
        inorder(head->RChild);
    }

}


/**
 * @brief perfroms an pre order traversal of a tree.
 * 
 * @param head the head of the tree or the curretn node we are in.
 */ 
void preorder(struct tree *head)
{
    if (head != NULL){
        printf("%s | Key: %d. ", head->message, head->key);
        preorder(head->LChild);
        preorder(head->RChild);
    }

}


/**
 * @brief perfroms an post order traversal of a tree.
 * 
 * @param head the head of the tree or the curretn node we are in.
 */ 
void postorder(struct tree *head)
{
    if (head != NULL){
        postorder(head->LChild);
        postorder(head->RChild);
        printf("%s | Key: %d. ", head->message, head->key);
    }

}


/**
 * @brief a recurisve function that adds a new node
 * 
 * @param head the starting point of the node
 * @param key the key value of the node
 */
void newnode(struct tree *head, int key)
{
    if(head != NULL){
        if(key < head->key){
            if(head->LChild == NULL)
                head->LChild = initize_node(head, message(), key);
            else
                newnode(head, key);
        } else{
            if(head->RChild == NULL)
                head->RChild = initize_node(head, message(), key);
            else
                newnode(head, key);
        }
        }
} 


/**
 * @brief prints out the tree.
 * 
 * @param head the start of the tree.
 * @param st the current string we are
 */
void printtree(struct tree *head, char *st)
{

}


/**
 * @breif initalizes a tree node first mallocs the space for the tree and then fills out the required
 * variables.
 * 
 * @param parent the parent of the node we are creating.
 * @param message the message we are storing.
 * @param key the priority of the element.
 * @return the memory address of the new element
 */
struct tree *initize_node(struct tree *parent, char *message, int key)
{

    struct tree *new = malloc(sizeof(struct tree));
    if (!new){
        printf("Malloc failed closing");
        exit(0);
    }
    if(parent == NULL)
        new->depth = 0;
    else
        new->depth = parent->depth + 1;
    new->Parent = parent;
    new->key = key;
    new->message = message;
    new->LChild = NULL;
    new->RChild = NULL;
    return new;
}


struct tree *delete(struct tree *head, int key)
{
    struct tree *cur = find(key, head);
    struct tree *par = find(cur->Parent->key, head);
    if (cur == NULL){
        printf("Node does not exist.\n");
        return head;
    } else if (cur->LChild == NULL && cur->RChild == NULL){
        free(cur);
        return head;
    } else if (cur->LChild == NULL){
        struct tree *temp = cur;
        cur = cur->RChild;
        cur->depth = temp->depth;
        cur->Parent = temp->Parent;
        if (par->key < key){
            par->LChild = cur;
        } else{
            par->RChild = cur;
        }
        free(temp);
    } else if (cur->RChild == NULL){
        struct tree *temp = cur;
        cur = cur->LChild;
        cur->depth = temp->depth;
        cur->Parent = temp->Parent;
        if (par->key < key){
            par->LChild = cur;
        } else{
            par->RChild = cur;
        }
        free(temp);
    } else {
        
    }
}