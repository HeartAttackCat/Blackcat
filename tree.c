#include <stdio.h>
#include <stdlib.h>

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
void addMenu(struct tree *master);
void deleteMenu(struct tree *master);

/* memory functions */
char *message(void);

/* tree functions */
struct tree *initize_node(struct tree *parent, char *message, int key);
int priorinput(void);
struct tree *find(int key, struct tree *head);
void newnode(struct tree *head, int key, char *message);
void inorder(struct tree *head);
//END

int main(void)
{
    //set up the user input variables
    struct tree master;
    master.key = 1;
    master.message = "Hello world";
    struct tree *masterptr = &master;
    char Buffer[BSIZE], com;
    printf(WELCOME_SCREEN);
    while (1) {
        printf("User>");
        fgets(Buffer, BSIZE, stdin);
        //take the user input buffer and find the command
        sscanf(Buffer, "%c", &com);
        //Select command 
        switch(com)
        {
            case 'o':
                //print the depth
                break;
            case 'p':
                //print the tree in order
                inorder(masterptr);
                break;
            case 'a':
                //add a new node
                addMenu(masterptr);
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
                deleteMenu(masterptr);
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
void deleteMenu(struct tree *master)
{

}

/**
 * @brief Runs the add menu
 * 
 * @param master a pointer to the tree
 */
void addMenu(struct tree *master)
{
    char *msg = message();
    int key = priorinput();
    newnode(master, key, msg);
}

/**
 * @brief prints help menu
 * 
 */
void helpMenu(void)
{
    printf("-=-=-=-=-=-=-[Help]-=-=-=-=-=-=-\n");
    printf("Pritning the help page.\n");
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
    printf("What key are we storing: ");
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
void newnode(struct tree *head, int key, char *msg)
{
    if(head != NULL){
        if(key < head->key){
            if(head->LChild == NULL)
                head->LChild = initize_node(head, msg, key);
            else
                newnode(head->LChild, key, msg);
        } else{
            if(head->RChild == NULL)
                head->RChild = initize_node(head, msg, key);
            else
                newnode(head->RChild, key, msg);
        }
    }
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

/**
 * @brief a function that will settle the disparity between two trees
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
 * @brief deletes a specified node by its key
 * 
 * @param head the head of the tree
 * @param key the key we are looking to delete
 * @return returns the new head if it was updated.
 */
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
        struct tree *rig = cur->RChild;
        struct tree *left = cur->LChild; 
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
 * @remark seems to create problems printing sideways in a preorder
 * must be a way to print rightside up.
 * 
 * @param head the head of the tree.
 */
void printtree(struct tree *head, int m_depth)
{
    if (head != NULL){
        spaceprintt(head->depth, head->message);
        printtree(head->LChild, m_depth);
        printtree(head->RChild, m_depth);
    }
}




/**
 * @brief Helper function for printtree because you can't multiply strings/chars
 * in C. As per usual a recurisve loop.
 * 
 * @param dep the depth of the function
 * @param message the message we are writing to the function.
 */
void spaceprintt(int dep, char *message)
{
    if (dep >= 0){
        printf("    ");
        spaceprintt(--dep, message);
    } else {
        printf("%s\n", message);
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