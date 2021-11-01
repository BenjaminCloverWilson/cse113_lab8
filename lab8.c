/**
 * @file lab8.c
 * @brief A linked list of user-inputted numbers
 * @author Benjamin Wilson
 * @date Fall 2021
 * @todo none
 * @bug none
 */

#include "lab8.h"

int main()
{
    /* Stack pointers to access the list on the heap */
    struct node *head = NULL;
    struct node *tail = NULL;
    struct node *marker = NULL; /* Helps to keep track of a particular node */
    struct node *cnode = NULL; /* last node created */
    struct node *head_check = head; /* Used to check the current head after a function call */

    /* Menu/user-input option trackers */
    int menu = 0; /* Used for main menu and sub-menus */
    int position = 0;
    int node_count;
    double number;
    char in[LEN];

    /* Menu */
    printf("---Welcome to Benjamin Wilson's Doubles List---\n\n");
    /* Did not indent in while loop that spans basically whole main function for space */
    while(menu == 0)
    {
    printf("1) Enter a number\n");
    printf("2) Delete a number\n");
    printf("3) Delete entire list\n");
    printf("4) Print all numbers\n");
    printf("5) Print how many numbers are in the list\n");
    printf("6) Find a number in the list\n");
    printf("7) Quit\n\n");
    /* User-input */
    printf("Please enter an option (only integers): ");
    fgets(in, LEN, stdin);
        menu = atoi(in);

    /* Main-Menu options */
    switch(menu)
    {
    /* Enter a new number to the list */
    case 1:
        /* Resets menu option to 0 to re-use menu tracker */
        menu = 0;

        /* Sub-menu */
        printf("\n1) Enter item at head of list\n");
        printf("2) Enter item in middle of list\n");
        printf("3) Enter item at tail of list\n");
        
        /* User-input */
        printf("Please enter an option: ");
        fgets(in, LEN, stdin);
            menu = atoi(in);

        /* Sub-menu options */
        switch(menu)
        {
        /* Insert new number at head */
        case 1:
            /* Creates new node and makes it the head */
            cnode = create_node();
            head_check = insert_head(&head, &cnode, &tail);
            printf("\n");
            /* Confirms what node was just made */
            print_node(cnode);
            /* Prints out current head address for user */
            printf("Current head address of list: %p\n\n", head_check);
        
            break;

        /* Insert new number in middle */
        case 2:
            /* printf() split for display purposes */
            printf("\nSome notes: The position number entered must be at least 1, ");
            printf("which represents the head.\nEntering a position larger than ");
            printf("the current length of the list, causes the number to be simply ");
            printf("placed at the tail.\nFurther implements of other numbers does ");
            printf("not change which number is the tail, unless going through option ");
            printf("of the above menu.\n\n");
            
            /* User-input and error check */
            while(position < 1)
            {
                printf("Please enter position of the number into the current list: ");
                fgets(in, LEN, stdin);
                    position = atoi(in);
                
                if(position < 1)
                    printf("Error: Please input a valid position number!\n\n");
            }

            /* Creates new node and inserts it into the position indicated */
            cnode = create_node();
            head_check = insert_middle(&head, &cnode, &tail, &marker, position);
            printf("\n");
            /* Confirms what node was just made */
            print_node(cnode);
            /* Prints out current head address for user */
            printf("Current head address of list: %p\n\n", head_check);

            /* Resets menu options for recycling */
            position = 0;
            break;

        /* Inserts new number onto tail */
        case 3:
            /* Creates new node and inserts it into the position indicated */
            cnode = create_node();
            head_check = insert_tail(&tail, &cnode, &head);
            printf("\n");
            /* Confirms what node was just made */
            print_node(cnode);
            /* Prints out current head address for user */
            printf("Current head address of list: %p\n\n", head_check);

            break;
        
        default:
            printf("Error: Please input a valid menu option!\n\n");
        }

        /* Resets menu options for recycling */
        menu = 0;
        break;
    
    /* Delete a single node by number */
    case 2:
        /* User-input */
        printf("What number would you like to be deleted: ");
        fgets(in, LEN, stdin);
            number = atof(in);

        /* Deletes node and prints current head address */
        head_check = delete_node(number, &head, &tail, &marker);
        printf("Current head address of list: %p\n\n", head_check);

        /* Resets menu options for recycling */
        menu = 0;
        break;
    
    /* Deletes whole list */
    case 3:
        printf("\nDeleting List...\n");
        head_check = delete_list(&head, &marker);
        /* Prints current head address */
        printf("Current head address of list: %p\n\n", head_check);

        /* Resets menu options for recycling */
        menu = 0;
        break;

    /* Prints out the entire list */
    case 4:
        printf("\n===============================\n");
        printf("        The List So Far\n");
        printf("===============================\n\n");
        print_list(head);

        /* Resets menu options for recycling */
        menu = 0;
        break;
    
    /* Prints out the number nodes/items/numbers in the list */
    case 5:
        printf("\n===============================\n");
        printf("        Number of Nodes\n");
        printf("===============================\n\n");
        node_count = count_nodes(head);
        /*Prints current head address */
        printf("Node/Item Count: %d\n\n", node_count);

        /* Resets menu options for recycling */
        menu = 0;
        break;
    
    /* Finds a node and returns it as marker */
    case 6:
        printf("What number would like to be found: ");
        fgets(in, LEN, stdin);
            number = atof(in);

        marker = find_node(number, &head);

        /* Resets menu options for recycling */
        menu = 0;
        break;

    /* Frees allocated memory in the list, and terminates the program */    
    case 7:
        delete_list(&head, &marker);
        /**No head-check as program is being terminated. Relaunching the
         * program would just make head set to NULL anyways
         */

        printf("Terminating Program... Have a lovely day <3\n");
        return 0;
    
    /* Error with main menu option */
    default:
        printf("Error: Please input a valid menu option!\n\n");
        /* Resets menu options for recycling */
        menu = 0;
    }
    }
}

/** Allocates memory for new node in linked list as long as there is space
 * in the computer and takes user input for the content of the node;
 * new nodes always start by pointing to NULL as the next node. Other functions
 * manipulate this.
 * @return a struct node *pointer to the allocated space and its contents
 */
struct node *create_node()
{
    char in[LEN];

    double num;

    /* Allocates space for new node on heap */
    struct node *tmp;
    tmp = malloc(sizeof(struct node));

    /* Makes sure that there is enough memory for allocation */
    if(tmp == NULL)
    {
        printf("Malloc failed, computer out of memory\n");
        exit(ENOMEM);
    }

    /* printf() split for display purposes */
    printf("\nPlease enter the number to be included in the list ");
    printf("(negatives & decimals accepted): ");
    fgets(in, LEN, stdin);
        num = atof(in);

    /* Assigns new node values */
    tmp->x = num;
    tmp->next = NULL;

    return tmp;
}

/** Prints out the node address, its associated number, and the node
 * that it points to next. This next node is often what's next in the list
 * or NULL if it's the last node
 * @param n The node to be printed
 */
void print_node(struct node *n)
{
    printf("Node Address: %p\n", n);
    printf("Node Double: %lf\n", n->x);
    
    /* Determines if node the end of the list */
    if(n->next != NULL)
        printf("Next node in list: %p\n\n", n->next);
    
    else
        printf("NULL\n\n");
}

/** Inserts a node at the head of the list. It also sets the head pointer to
 * this new insertion. If it's the first node in the list, it also modifies the
 * tail pointer.
 * @param head The head pointer of the list passed by reference
 * @param n The node to be inserted into the list passed by reference
 * @param tail The tail pointer of the list passed by reference
 * @return The struct node address that head points to after insertion.
 */
struct node *insert_head(struct node **head, struct node **n, struct node **tail)
{
    /* First item in list */
    if(*head == NULL)
    {
        *head = *n;
        *tail = *n;

    } else
    {
        /* Adjusts head and maintains rest of list */
        (*n)->next = *head;
        *head = *n;

        /* Finds end of the list */
        struct node *index = *head;

        while(index->next != NULL)
            index = index->next;
        
        /* Sets tail to the new end of the list */
        *tail = index;
    }

    return *head;
}

/** Inserts a node into the middle of the list. It also sets head and tail to
 * this node if it's the first item in the list, or just tail to this node
 * if it's added to the end of the list.
 * @param head The head pointer of the list passed by reference
 * @param n The node to be inserted into the list passed by reference
 * @param tail The tail pointer of the list passed by reference
 * @param marker The marker pointer of the list that's used for indexing
 * or accessing/modifying the list at a certain node.
 * @param position The exact place in the list and order the node should be
 * inserted in.
 * @return The struct node address that head points to after insertion.
 */
struct node *insert_middle(struct node **head, struct node **n, struct node **tail, struct node **marker, int position)
{
    /* First item in the list */
    if(*head == NULL)
    {
        *head = *n;
        *tail = *n;
        *marker = *n;
    } else
    {
        /* Accesses and indexes list */
        struct node *index = *head;
        int count = 1;

        /* Similar to insert_head with just the head position */
        if(position == 1)
        {
            (*n)->next = index;
            *head = *n;
        
        /* Inserts at any other position */
        } else
        {
            /* Finds position and/or tail of list */
            while(count < position && index->next != NULL)
            {
                *marker = index;
                index = index->next;
                count++;
            }

            /* If the tail is found first insert at tail and reset tail pointer */
            if(count != position)
            {
                (*tail)->next = *n;
                *tail = *n;
            
            /* If position is before the tail or at the current tail position, insert into middle */
            } else if(count == position)
            {
                (*n)->next = index;
                (*marker)->next = *n;
            
            /* Error check for debugging */
            } else
                printf("This doesn't work for some reason and I'm sad\n");
        }
    }

    return *head;
}

/** Inserts a node at the tail of the list. It also sets the tail pointer to
 * this new insertion. If it's the first node in the list, it also modifies the
 * head pointer.
 * @param tail The tail pointer of the list passed by reference
 * @param n The node to be inserted into the list passed by reference
 * @param head The head pointer of the list passed by reference
 * @return The struct node address that head points to after insertion.
 */
struct node *insert_tail(struct node **tail, struct node **n, struct node **head)
{
    /* First item in list */
    if(*tail == NULL)
    {
        *tail = *n;
        *head = *n;

    } else
    {
        /* Inserts new node at tail */
        (*tail)->next = *n;
        *tail = *n;
    }

    return *head;
}

/** Prints out the entire list with head as the start
 * @param head The pointer to the start of the list to be printed passed by copy
 */
void print_list(struct node *head)
{
    /* Tracks index of list and used for while loop */
    int position = 1;
    int loop = 1;

    /* List is empty */
    if(head == NULL)
        printf("Nothing in the list so far\n\n");
    
    else
    {
        /* Prints each node until the tail is found */
        while(loop == 1)
        {
            if(head->next != NULL)
            {
                printf("Position: %d\n", position);
                print_node(head);
                head = head->next;
            } else if(head->next == NULL)
            {
                printf("Position: %d\n", position);
                print_node(head);
                /* Exits the list after tail is printed */
                loop = 0;
            }

            position++;
        }
    }
}

/** Deletes a specific node in the list by its double number value. It's memory
 * is freed after deletion from the list.
 * @param d The number that specifies which node is deleted from the list
 * @param head The head pointer of the list passed by reference
 * @param tail The tail pointer of the list passed by reference
 * @param marker The marker pointer of the list used for indexing and marking
 * certain nodes for either deletion or adjusting list pointers.
 * @return A pointer to the head of the list
 */
struct node *delete_node(double d, struct node **head, struct node **tail, struct node **marker)
{
    /* List is empty */
    if(*head == NULL)
    {
        printf("\nThe list is empty, number not found!\n\n");
    
    /* Number is the head of the list and it's the only number in the entire list */
    } else if((*head)->next == NULL && (*head)->x == d)
    {
        /* Free allocated memory (delete) */
        free(*head);
        /* Reset stack pointers to NULL */
        *head = NULL;
        *tail = NULL;
        *marker = NULL;
        printf("Number was deleted successfully!\n\n");

    /* Number is the head of the list but there are subsequent numbers */
    } else if((*head)->next != NULL && (*head)->x == d)
    {
        /* Keep track of rest of list and set marker to node for deletion */
        *marker = *head;
        *head = (*head)->next;
        /* Free allocated memory (delete) */
        free(*marker);
        /* Resest stack pointers to NULL */
        *marker = NULL;
        printf("Number was deleted successfully!\n\n");
    
    /* Number is not the head */
    } else
    {
        /* Access and index list */
        struct node *index = *head;

        /* Find number or tail */
        while(index->x != d && index->next != NULL)
        {
            *marker = index;
            index = index->next;
        }
        
        /*Number found not at the tail and in the middle */
        if(index->x == d && index->next != NULL)
        {
            /* Keep tack of list after node being deleted */
            (*marker)->next = index->next;
            *marker = index;
            /* Free allocated memory (delete) */
            free(*marker);
            /* Reset stack pointers to NULL */
            *marker = NULL;
            printf("Number was deleted successfully!\n\n");

        /* Number found and it's at the tail */
        } else if(index->x == d && index->next == NULL)
        {
            /* Set new end of list and reset tail to new end */
            (*marker)->next = NULL;
            *tail = *marker;
            *marker = index;
            /* Free allocated memory (delete) */
            free(*marker);
            /* Reset stack pointers to NULL */
            *marker = NULL;
            printf("Number was deleted successfully!\n\n");

        /* Number found in the list */
        } else if(index->x != d)
        {
            printf("\nNumber not found in the list!\n\n");
        }
    }

    return *head;
}

/** Deletes entire list and frees all its allocated memory
 * @param head The head pointer of the list passed by reference
 * @param marker The marker pointer of the list passed by reference
 * @return A pointer to the new head of the list, which is NULL
 */
struct node *delete_list(struct node **head, struct node **marker)
{
    /* Frees allocated dynamic memory for the entire list */
    if(*head !=  NULL)
    {
        while((*head)->next != NULL)
        {
            *marker = *head;
            *head = (*head)->next;
            free(*marker);
        }

        free(*head);
    }

    /* Resets stack pointers to NULL */
    *marker = NULL;
    *head = NULL;

    printf("List has been successfully deleted!\n\n");

    return *head;
}

/** Counts the number of items in the list so far
 * @param head The head pointer of the list passed by copy
 * @return The number of nodes/items/numbers inputted into the list
 */
int count_nodes(struct node *head)
{
    /* Keeps track of count */
    int count = 0;

    /* List is not empty */
    if(head != NULL)
    {
        /* At least head node is present */
        count = 1;

        /* Accesses list though head until end is reacahed */
        while(head->next != NULL)
        {
            count++;
            head = head->next;
        }
    }

    return count;
}

/** Finds if a specific number/item is present in the list
 * by its number value (not address). Prints node info if it's found.
 * @param d The number to be found
 * @param head The head pointer of the list passed by reference
 * @return A pointer to the item/node's address if it's found
 */
struct node *find_node(double d, struct node **head)
{
    /* List is empty */
    if(*head == NULL)
    {
        printf("The list is currently empty, number not found!\n\n");
        return NULL;
    
    /* List has at least one value */
    } else
    {
        /* Used to access list and find a node number */
        struct node *find = *head;

        /* Finds number or tail */
        while(find->x != d && find->next != NULL)
            find = find->next;
        
        /* If the number was found using math.h functions */
        if(isgreaterequal(find->x, d) && islessequal(find->x, d))
        {
            printf("The number was found!\n\n");
            print_node(find);
            return find;
        
        /* Number was not found */
        } else
        {
            printf("The number was not found!\n\n");
            return NULL;
        }
    }
}
