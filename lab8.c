/**
 * @file lab8.c
 * @brief A linked list of user-inputted numbers
 * @author Benjamin Wilson
 * @date Fall 2021
 * @todo Write & implement functions
 * @bug Probably everything here
 */

#include "lab8.h"

int main()
{
    /* Stack pointers to access the list on the heap */
    struct node *head = NULL;
    struct node *tail = NULL;
    struct node *marker = NULL;
    struct node *cnode = NULL; /* last node created or being referenced */

    /* Menu/user-input option tracker */
    int menu = 0;
    int position = 0;

    /* Menu */
    printf("---Welcome to Benjamin Wilson's Doubles List---\n\n");    
    while(menu == 0)
    {
    printf("1) Enter a number\n");
    printf("2) Delete a number\n");
    printf("3) Print all numbers\n");
    printf("4) Print how many numbers are in the list\n");
    printf("5) Find a number in the list\n");
    printf("6) Quit\n\n");
    /* Checks for valid menu option */
    while(menu < 1 || menu > 6)
    {
        printf("Please enter an option: ");
        scanf(" %d", &menu);
        if(menu < 1 || menu > 6)
            printf("Error: Please input a valid menu option!\n\n");
    }

    /* Menu options */
    switch(menu)
    {
    /* Enter a new number to the list */
    case 1:
        /* Resets menu option to 0 to re-use menu tracker */
        menu = 0;

        printf("\n1) Enter item at head of list\n");
        printf("2) Enter item in middle of list\n");
        printf("3) Enter item at tail of list\n");
        while(menu == 0)
        {
            printf("Please enter an option: ");
            scanf(" %d", &menu);
            if(menu < 1 || menu > 3)
                printf("Error: Please input a valid position number!\n\n");
        }

        switch(menu)
        {
        case 1:
            /* Creates new node and makes it the head */
            cnode = create_node();
            insert_head(&head, &cnode, &tail);
            print_list(head);
            printf("Head: %p", head);
            printf("Tail: %p", tail);
        
            /* Resets menu option to 0 to re-use menu tracker */
            menu = 0;
            break;

        case 2:
            /* printf() split for display purposes */
            printf("\nSome notes: The position number entered must be at least 1, ");
            printf("which represents the head.\nEntering a position larger than ");
            printf("the current length of the list, causes the number to be simply ");
            printf("placed at the tail.\nFurther implements of other numbers does ");
            printf("not change which number is the tail, unless going through option ");
            printf("of the above menu.\n\n");
            while(position < 1)
            {
                printf("Please enter position of the number into the current list: ");
                scanf(" %d", &position);
                if(position < 1)
                    printf("Error: Please input a valid position number!\n\n");
            }

            /* Creates new node and inserts it into the position indicated */
            cnode = create_node();
            insert_middle(&head, &cnode, &tail, &marker, position);
            print_list(head);

            /* Resets menu options for recycling */
            position = 0;
            menu = 0;
            break;

        case 3:
            /* Creates new node and inserts it into the position indicated */
            cnode = create_node();
            insert_tail(&tail, &cnode, &head);
            printf("Head: %p\t", head);
            printf("Tail: %p\n", tail);
            print_list(head);

            /* Resets menu options for recycling */
            menu = 0;
            break;
        }
        
    case 2:
        menu = 0;
        break;
            
    case 3:
        menu = 0;
        break;
    
    case 4:
        menu = 0;
        break;
    
    case 5:
        menu = 0;
        break;
        
    case 6:
        /* Frees allocated dynamic memory */
        free(cnode);

        printf("Terminating Program... Have a lovely day <3\n");
        return 0;
    }
    }
}


struct node *create_node()
{
    double num;

    struct node *tmp;
    tmp = malloc(sizeof(struct node));

    if(tmp == NULL)
    {
        printf("Malloc failed, computer out of memory\n");
        exit(ENOMEM);
    }

    /* printf() split for display purposes */
    printf("\nPlease enter the number to be included in the list ");
    printf("(negatives & decimals accepted): ");
    scanf(" %lf", &num);

    tmp->x = num;
    tmp->next = NULL;

    return tmp;
}


void print_node(struct node *n)
{
    printf("Node Address: %p\n", n);
    printf("Node Double: %lf\n", n->x);
    
    if(n->next != NULL)
        printf("Next node in list: %p\n\n", n->next);
    
    else
        printf("NULL\n\n");
}


void insert_head(struct node **head, struct node **n, struct node **tail)
{
    if(*head == NULL)
    {
        *head = *n;
        *tail = *n;
    } else
    {
        (*n)->next = *head;
        *head = *n;

        struct node *index = *head;

        while(index->next != NULL)
            index = index->next;
        
        *tail = index;
    }
}


void insert_middle(struct node **head, struct node **n, struct node **tail, struct node **marker, int position)
{
    if(*head == NULL)
    {
        *head = *n;
        *tail = *n;
        *marker = *n;
    } else
    {
        struct node *index = *head;
        int count = 0;

        while(count < position && index->next != NULL)
        {
            *marker = index;
            index = index->next;
            count++;
        }


        if(index->next != NULL)
        {
            (*marker)->next = *n;
        } else
        {
            (*n)->next = index;
            (*marker)->next = *n;
        }
    }
}


void insert_tail(struct node **tail, struct node **n, struct node **head)
{
    if(*tail == NULL)
    {
        *tail = *n;
        *head = *n;
    } else
    {
        struct node *index = *head;

        while(index->next != NULL)
            index = index->next;
        
        *tail = index;

        (*tail)->next = *n;
        *tail = *n;
    }
}


void print_list(struct node *head)
{
    int position = 1;
    int loop = 1;

    while(loop == 1)
    {
        if(head->next != NULL)
        {
            printf("Position: %d\n", position);
            print_node(head);
            head = head->next;
        } else
        {
            printf("Position: %d\n", position);
            print_node(head);
            loop = 0;
        }
        
        position++;
    }
}


int count_nodes(struct node *head)
{
    int count = 0;
    struct node *tmp = head;

    while(tmp->next != NULL)
    {
        count++;
        tmp = tmp->next;
    }

    return count;
}