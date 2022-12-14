/**
 * @file tree.c
 * 
 * @author Hunter Lane Kassidy Maberry
 * 
 * @date 2022/10/05
 * 
 * Assignment: Self balancing tree
 * 
 * Class: CSE 122
 * 
 * @brief A program that does operations with a self balancing tree
 * 
 * @detail A program that does operations with a self balancing tree. A lot of
 * of the user functions are different versions that print out stuff where we 
 * can also add and remove.
 * 
 * @bugs none
 * 
 * @todo none
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* All the text displayed to the user defined */
#define WELCOME_SCREEN "-=-=-=-=-=-=-=-=-=-=-[Welcome]-=-=-=-=-=-=-=-=-=-\n    /\\  /\\     Made by Miriam and Cas.    *\n   / O  O \\       * Balance Tree +\n   \\  I   /   *                          *\n   /      \\         *             *\n  / |    | \\    +           *                *\n  | |    | |        *                 +\n   W W  W W    *              +           * \n -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- \n"
#define BSIZE 100

struct  tree{
    struct tree *LChild, *RChild, *Parent;
    char *message;
    int key, depth;
};

//BEGIN - function declarations of independences
/* help menu functions */
void helpMenu(void);
struct tree *addMenu(struct tree *master);
struct tree *deleteMenu(struct tree *master);

/* memory functions */
char *message(void);
char *rm_newline(char *message, int dep);

/* tree functions */
struct tree *initize_node(struct tree *parent, char *message, int key);
int priorinput(void);
struct tree *find(int key, struct tree *head);
void insert(struct tree *head, int key, char *message);
void inorder(struct tree *head);
void keyvalprint(struct tree *head);
void preorder(struct tree *head);
void postorder(struct tree *head);
void settle(struct tree *cur, struct tree *add);
struct tree *delete(struct tree *head, int key);
void printtree(struct tree *head);
int depthupdate(struct tree *head, int dep);
void spaceprintt(int dep, char *message, int key);
struct tree *left(struct tree *node);
struct tree *right(struct tree *node);
int height(struct tree *head, int dep);
int difference(struct tree *node);
struct tree *balance(struct tree *node, int key);
//END

int main(void)
{
    //set up the user input variables
    struct tree *masterptr;
    char Buffer[BSIZE], com;
    printf(WELCOME_SCREEN);
    printf("In order for the program to contiue please follow dicrections and add new node.\n");
    masterptr = initize_node(NULL, message(), priorinput());
    while (1) {
        printf("User>");
        fgets(Buffer, BSIZE, stdin);
        //take the user input buffer and find the command
        sscanf(Buffer, "%c", &com);
        //Select command 
        switch(com)
        {
            case 'o':
                printf("%d\n", height(masterptr, 0));
                break;
            case 'c':
                //print the tree in order
                inorder(masterptr);
                break;
            case 'a':
                //add a new node
                masterptr = addMenu(masterptr);
                break;
            case 'k':
                keyvalprint(masterptr);
                break;
            case 'h':
                //print the help menu
                helpMenu();
                break;
            case 'e':
                //close the program
                exit(0);
                break;
            case 'd':
                //Deletes an element
                deleteMenu(masterptr);
                break;
            case 'i':
                //print postorder tree
                postorder(masterptr);
                break;
            case 'm':
                //print preorder tree
                preorder(masterptr);
                break;
            case 'p':
                //Prints the tree in a visually understandable manner.
                printtree(masterptr);
                break;
            default:
                //the command didn't exist
                printf("Command does not exist...\n");
        }
    }
    return 0;

}


/**
 * @brief THe menu for deleting a node
 * 
 * @param master the pointer to the head of the tree
 */
struct tree *deleteMenu(struct tree *master)
{
    int key = priorinput();
    master = delete(master, key);
    master =  balance(master, key);
    return master; 
}


/**
 * @brief Runs the add menu
 * 
 * @param master a pointer to the tree
 */
struct tree *addMenu(struct tree *master)
{
    int key = priorinput();
    char *msg = message();
    insert(master, key, msg);
    master =  balance(master, key);
    return master;
}

/**
 * @brief prints help menu
 * 
 */
void helpMenu(void)
{
    printf("-=-=-=-=-=-=-[Help]-=-=-=-=-=-=-\n");
    printf("Pritning the help page.\n");
    printf("k prints they key values\n");
    printf("a adds a node to the tree\n");
    printf("d removes a node from the tree\n");
    printf("p prints the tree in a visually understandable manner\n");
    printf("m preorder transersal\n");
    printf("i post order transversal\n");
    printf("e exits the program\n");
    printf("c prints in a post order transveral\n");
    printf("-=-=-=-=-=-=-[END]-=-=-=-=-=-=-=-\n");
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
            return head;
        } else if (key < head->key){
            return find(key, head->LChild);
        } else {
            return find(key, head->RChild);
        }
    } else{
        printf("ERROR | Node does not exist\n");
        return NULL;
    }
    return NULL;
}

/**
 * @brief a function for grabbing messages.
 * 
 * @return the user input.
 */
char *message()
{
    char *buff = malloc(100 * sizeof(char));
    if (buff == NULL)
        exit(-10);
    printf("Insert message(string): ");
    fgets(buff, 100, stdin);
    buff = rm_newline(buff, 0);
    return buff;
}

/**
 * @brief removes the new line makes printing out things look better.
 * 
 * @param message the message we are removing
 * @param dep the length of the string we are looking at.
 */
char *rm_newline(char *message, int dep)
{
    if(message[dep] == '\n' || message[dep] == '\0'){
        message[dep] = '\0';
        return message;
    }
    return rm_newline(message, ++dep);
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
    printf("Insert Key(int): ");
    fgets(buff, 100, stdin);
    sscanf(buff, "%d", &val);
    return val;  
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
        printf("%s | Key: %d. \n", head->message, head->key);
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
        printf("%s | Key: %d. \n", head->message, head->key);
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
        printf("%s | Key: %d. \n", head->message, head->key);
    }

}


/**
 * @brief a recurisve function that adds a new node
 * 
 * @param head the starting point of the node
 * @param key the key value of the node
 */
void insert(struct tree *head, int key, char *msg)
{
    if(head != NULL){
        if(key < head->key){
            if(head->LChild == NULL)
                head->LChild = initize_node(head, msg, key);
            else
                insert(head->LChild, key, msg);
        } else{
            if(head->RChild == NULL)
                head->RChild = initize_node(head, msg, key);
            else
                insert(head->RChild, key, msg);
        }
    }
} 


/**
 * @brief initalizes a tree node first mallocs the space for the tree and then fills out the required
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


/**
 * @brief a function that will aid when deleting nodes in trees
 * 
 * @param cur the larger key of the two nodes of which we going to be adding 
 * onto.
 * @param add the smaller key of the two nodes of which we will be adding
 * this one to the other.
 */
void settle(struct tree *cur, struct tree *add)
{
    if (cur->key < add->key){
        if(cur->RChild != NULL){
            settle(cur->RChild, add);
        } else{
            cur->RChild = add;
        }
    } else {
        if (cur->LChild != NULL){
            settle(cur->LChild, add);
        } else {
            cur->LChild = add;
        }
    }
}


/**
 * @brief deletes a specified node by its key.
 * @remark finds the parent as well to add onto the new child to it.
 * 
 * @param head the head of the tree
 * @param key the key we are looking to delete
 * @return returns the new head if it was updated.
 */
struct tree *delete(struct tree *head, int key)
{
    struct tree *cur = find(key, head);
    struct tree *par = cur->Parent;
    if (cur == NULL){
        return head;
    // No child.
    } else if (cur->LChild == NULL && cur->RChild == NULL){
        free(cur);
        return head;
    // only one child and right.
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
    // only one child and left.
    } else if (cur->RChild == NULL){
        struct tree *temp = cur;
        cur = cur->LChild;
        cur->depth = temp->depth;
        cur->Parent = temp->Parent;
        if (par->key > key){
            par->LChild = cur;
        } else{
            par->RChild = cur;
        }
        free(temp);
    // if two children
    } else {
        struct tree *rig = cur->RChild;
        struct tree *left = cur->LChild; 
        // comparison decides where to add onto parent.
        if(cur == par->LChild){
            settle(left, rig);
        } else {
            settle(rig, left);
        }
        free(cur);
    }
    return head;
}

/**
 * @brief prints out all the key values in said function. 
 * 
 * @param head the head of the trees.
 */
void keyvalprint(struct tree *head)
{
    if (head != NULL){
        inorder(head->LChild);
        printf("%d ", head->key);
        inorder(head->RChild);
    }
}

/**
 * @brief Prints it in a preorder traversal method.
 * @remark Prints sideways and common indentation tells us what we are at
 * but appears to work.
 * 
 * @param head the head of the tree.
 */
void printtree(struct tree *head)
{
    if (head != NULL){
        // helper function that deals with the printing.
        spaceprintt(head->depth, head->message, head->key);
        printtree(head->LChild);
        printtree(head->RChild);
    }
}

/**
 * @brief Helper function for printtree because you can't multiply strings/chars
 * in C. As per usual a recurisve loop.
 * 
 * @param dep the depth of the function
 * @param message the message we are writing to the function.
 */
void spaceprintt(int dep, char *message, int key)
{
    if (dep > 0){
        printf("    ");
        spaceprintt(--dep, message, key);
    } else {
        printf("%s |Key: %d\n", message, key);
    }
}

/**
 * @brief updates the depth of all variables
 * 
 * @param head the starting point of the tree
 * @param dep the starting depth of the function. PASS 0 HERE.
 * @return 0
 */
int depthupdate(struct tree *head, int dep)
{
    if (head == NULL)
        return 0;
    head->depth = dep;
    depthupdate(head->LChild, ++dep);
    depthupdate(head->RChild, ++dep);
}


/**
 * @brief determines the height of two nodes.
 * @remarks The original calculations seem to add 2 so we subtract two on each
 * return
 * 
 * @param head the head of the tree
 * @param dep the current height we are at
 * @return the height of the given tree.
 */
int height(struct tree *head, int dep)
{
    if(head == NULL)
        return 0;
    int z = height(head->LChild, ++dep);
    int h = height(head->RChild, ++dep);
    if(dep < z){
        dep = z;
    } else if (dep < h){
        dep = h;
    }
    return dep;
}


/**
 * @brief determines the dispairty and balances the two nodes.
 * 
 * @param node the head node.
 * @return the balance between the two.
 */
int difference(struct tree *node)
{
    return height(node->LChild, 1) - height(node->RChild, 1);
}

/**
 * @brief Comits a left rotation and returns the new address for the root.
 * 
 * @param zero Root node that first comes in
 * @return struct tree* 
 */
struct tree *left(struct tree *zero)
{
    struct tree *one = zero->RChild;
    struct tree *two = one->LChild;

    // rotation itself
    one->LChild = zero;
    zero->RChild = two;
    // Update parents
    one->Parent = zero->Parent;
    zero->Parent = one;
    if (two != NULL)
        two->Parent = zero;

    // updates the depth
    depthupdate(zero, zero->depth);

    return one; 
}



/**
 * @brief does a right rotation.
 * @remark the nodes we are working with are called zero, one, and two because
 * it represents their original depth.
 * 
 * @param zero Named because that is the index relative to our rotation.
 * @return the new zero node.
 */
struct tree *right(struct tree *zero)
{
    // named after distance from tree.
    struct tree *one = zero->LChild;
    struct tree *two = one->RChild;

    // Move node one to be parent of var node.
    one->RChild = zero;
    // Move node two to be L child of node two.
    zero->LChild = two;

    // Update parents
    one->Parent = zero->Parent;
    zero->Parent = one;
    if (two != NULL);
        two->Parent = zero;

    // updates the depth
    depthupdate(zero, zero->depth);

    return one; 
}

/**
 * @brief a function to balance out a tree
 * 
 * @param node the head node
 * @param key the key we are using to compare
 * @return the updated node.
 */
struct tree *balance(struct tree *node, int key)
{
    int balance = difference(node);

    // safe guards incase a node we are accessing values that don't exist.
    if (node->LChild == NULL)
    {
        if (balance < -1 && key > node->RChild->key) {
            node = left(node);
        }
        else if (balance > 1 && key > node->RChild->key){
            node->LChild = left(node->LChild);
            node = right(node);
        }
    } else if (node->RChild == NULL)
    {
        if (balance < -1 && key < node->LChild->key){
            node->RChild = right(node->RChild);
            node = left(node);
        }
        else if (balance > 1 && key < node->LChild->key){
            node = right(node);
        }
    } else {
    //  left right
    if (balance < -1 && key < node->RChild->key){
        node->RChild = right(node->RChild);
        node = left(node);
    // right right
    } else if (balance < -1 && key > node->LChild->key){
        node = left(node);
    // left left
    } else if (balance > 1 && key < node->RChild->key){
        node = right(node);
    // right left
    } else if (balance > 1 && key > node->LChild->key){
        node->LChild = left(node->LChild);
        node = right(node);
    }
    }
    return node;
}