/**
 * @file lab8.c
 * @brief A linked list of user-inputted numbers
 * @author Benjamin Wilson
 * @date Fall 2021
 * @todo Write & implement functions
 * @bug DO NOT ENTER ANYTHING BUT AN INTEGER OR ELSE YOU GET AN INFINITE LOOP!
 */

#include "lab8.h"

int main()
{
    /* Stack pointers to access the list on the heap */
    struct node *head = NULL;
    struct node *tail = NULL;
    struct node *marker = NULL;
    struct node *cnode = NULL; /* last node created or being referenced */
    struct node *head_check = head;

    /* Menu/user-input option tracker */
    int menu = 0;
    int position = 0;
    int node_count;
    double number;

    /* Menu */
    printf("---Welcome to Benjamin Wilson's Doubles List---\n\n");    
    while(menu == 0)
    {
    printf("1) Enter a number\n");
    printf("2) Delete a number\n");
    printf("3) Delete entire list\n");
    printf("4) Print all numbers\n");
    printf("5) Print how many numbers are in the list\n");
    printf("6) Find a number in the list\n");
    printf("7) Quit\n\n");
    printf("Please enter an option (only integers): ");
    scanf(" %d", &menu);

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
            {
                printf("Error: Please input a valid position number!\n\n");
                menu = 0;   
            }
        }

        switch(menu)
        {
        case 1:
            /* Creates new node and makes it the head */
            cnode = create_node();
            head_check = insert_head(&head, &cnode, &tail);
            printf("\n");
            print_node(cnode);
            printf("Current head address of list: %p\n\n", head_check);
        
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
            head_check = insert_middle(&head, &cnode, &tail, &marker, position);
            printf("\n");
            print_node(cnode);
            printf("Current head address of list: %p\n\n", head_check);

            /* Resets menu options for recycling */
            position = 0;
            break;

        case 3:
            /* Creates new node and inserts it into the position indicated */
            cnode = create_node();
            head_check = insert_tail(&tail, &cnode, &head);
            printf("\n");
            print_node(cnode);
            printf("Current head address of list: %p\n\n", head_check);

            break;
        }

        menu = 0;
        break;
        
    case 2:
        printf("What number would you like to be deleted: ");
        scanf(" %lf", &number);

        head_check = delete_node(number, &head, &tail, &marker);
        printf("Current head address of list: %p\n\n", head_check);

        menu = 0;
        break;
    
    case 3:
        printf("\nDeleting List...\n");
        head_check = delete_list(&head, &marker);
        printf("Current head address of list: %p\n\n", head_check);

        menu = 0;
        break;

    case 4:
        printf("\n===============================\n");
        printf("        The List So Far\n");
        printf("===============================\n\n");
        print_list(head);

        menu = 0;
        break;
    
    case 5:
        printf("\n===============================\n");
        printf("        Number of Nodes\n");
        printf("===============================\n\n");
        node_count = count_nodes(head);
        printf("Node/Item Count: %d\n\n", node_count);

        menu = 0;
        break;
    
    case 6:
        printf("What number would like to be found: ");
        scanf(" %lf", &number);

        marker = find_node(number, &head);

        menu = 0;
        break;
        
    case 7:
        delete_list(&head, &marker);

        printf("Terminating Program... Have a lovely day <3\n");
        return 0;
    
    default:
        printf("Error: Please input a valid menu option!\n\n");
        menu = 0;
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


struct node *insert_head(struct node **head, struct node **n, struct node **tail)
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

    return *head;
}


struct node *insert_middle(struct node **head, struct node **n, struct node **tail, struct node **marker, int position)
{
    if(*head == NULL)
    {
        *head = *n;
        *tail = *n;
        *marker = *n;
    } else if (position < 1)
        position = 1; 
    else
    {
        struct node *index = *head;
        int count = 1;

        if(position == 1)
        {
            (*n)->next = index;
            *head = *n;
        } else
        {
            while(count < position && index->next != NULL)
            {
                *marker = index;
                index = index->next;
                count++;
            }

            if(count != position)
            {
                (*tail)->next = *n;
                *tail = *n;
            } else if(count == position)
            {
                (*n)->next = index;
                (*marker)->next = *n;
            } else
                printf("This doesn't work for some reason and I'm sad\n");
        }
    }

    return *head;
}


struct node *insert_tail(struct node **tail, struct node **n, struct node **head)
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

    return *head;
}


void print_list(struct node *head)
{
    int position = 1;
    int loop = 1;

    if(head == NULL)
        printf("Nothing in the list so far\n\n");
    else
    {
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
                loop = 0;
            }

            position++;
        }
    }
}


struct node *delete_node(double d, struct node **head, struct node **tail, struct node **marker)
{ 
    if(*head == NULL)
    {
        printf("\nThe list is empty, number not found!\n\n");
    } else if((*head)->next == NULL && (*head)->x == d)
    {
        free(*head);
        *head = NULL;
        *tail = NULL;
        *marker = NULL;
        printf("Number was deleted successfully!\n\n");
    } else if((*head)->next != NULL && (*head)->x == d)
    {
        *marker = *head;
        *head = (*head)->next;
        free(*marker);
        *marker = NULL;
        printf("Number was deleted successfully!\n\n");
    } else
    {
        struct node *index = *head;

        while(index->x != d && index->next != NULL)
        {
            *marker = index;
            index = index->next;
        }
        
        if(index->x == d && index->next != NULL)
        {
            (*marker)->next = index->next;
            *marker = index;
            free(*marker);
            *marker = NULL;
            printf("Number was deleted successfully!\n\n");
        } else if(index->x == d && index->next == NULL)
        {
            (*marker)->next = NULL;
            *tail = *marker;
            *marker = index;
            free(*marker);
            *marker = NULL;
            printf("Number was deleted successfully!\n\n");
        } else if(index->x != d)
        {
            printf("\nNumber not found in the list!\n\n");
        }
    }

    return *head;
}


struct node *delete_list(struct node **head, struct node **marker)
{
    /* Frees allocated dynamic memory */
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

    *marker = NULL;
    *head = NULL;

    printf("List has been successfully deleted!\n\n");

    return *head;
}


int count_nodes(struct node *head)
{
    int count = 0;

    if(head != NULL)
    {
        count = 1;

        while(head->next != NULL)
        {
            count++;
            head = head->next;
        }
    }

    return count;
}


struct node *find_node(double d, struct node **head)
{
    if(*head == NULL)
    {
        printf("The list is currently empty, number not found!\n\n");
        return NULL;
    } else
    {
        struct node *find = *head;

        while(find->x != d && find->next != NULL)
            find = find->next;
        
        if(isgreaterequal(find->x, d) && islessequal(find->x, d))
        {
            printf("The number was found!\n\n");
            print_node(find);
            return find;
        } else
        {
            printf("The number was not found!\n\n");
            return NULL;
        }
    }
}
