/**
 * @file collatz.h
 * @brief Completes the Collatz Conjecture on an inputted function
 * @author Benjamin Wilson
 * @date Fall 2021
 * @todo none
 * @bug none
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* Input length */
#define LEN 10

/* Node struct for storing values and for linked list */
struct node
{
    int x;
    struct node *next;
};

/* Function prototypes */
struct node *create_node(int n);
void insert(struct node **tail, struct node **cnode, struct node **head);
void print_sequence(struct node *head, int n);

int main()
{
    /* Stack pointers to keep track/access the dynamic linked list */
    struct node *head = NULL;
    struct node *tail = NULL;
    struct node *cnode = NULL;

    /* Hardcoded test value */
    //int n = 3;

    /* User-input variables */
    char in[LEN];
        int n;

    printf("=================\n");
    printf("    Hailstone\n");
    printf("=================\n\n");

    /* User-input, no error checking required! */
    printf("Please enter value of n for its hailstone sequence: ");
    fgets(in, LEN, stdin);
        n = atoi(in);

    /* A copy of n for maniputaltion of the sequence */
    int seq_num = n;

    /* Starting node for n to start sequence */
    cnode = create_node(n);
    insert(&tail, &cnode, &head);

    /* Complete sequence */
    while(seq_num > 1)
    {
        /* Even number in sequence */
        if((seq_num % 2) == 0)
            seq_num = seq_num / 2;
        
        /* Odd number in sequence */
        else
            seq_num = (seq_num * 3) + 1;
        
        /* place new sequence number into the linked list */
        cnode = create_node(seq_num);
        insert(&tail, &cnode, &head);
    }

    /* Place 1 into the sequence */
    cnode = create_node(seq_num);
    insert(&tail, &cnode, &head);

    /* Print out the seuqnce information for the user-inputted n */
    print_sequence(head, n);

    /* Free dynamic memory of the list */
    while(head->next != NULL)
    {
        cnode = head->next;
        free(head);
        head = cnode;
    }

    /* Free 1 from the sequence */
    free(head);

    return 0;
}

/** Dynamically allocates memory for a sequence number and creates a pointer for it
 * @param n The sequence number to have memory stored for list
 * @return A pointer to the newly allocated/created node
 */
struct node *create_node(int n)
{
    /* Temporary struuct pointer */
    struct node *tmp = NULL;

    /* Allocates memory for new node */
    tmp = malloc(sizeof(struct node));

    /* Error checks that enough memory is present in the computer */
    if(tmp == NULL)
    {
        printf("Malloc has falled. Computer out of memory for sequence!\n");
        exit(ENOMEM);
    }

    /* Creates new node */
    tmp->x = n;
    tmp->next = NULL;

    return tmp;
}

/** Inserts a sequence number into the list through the tail. If it's the first
 * sequence number, the head also set to point to the number.
 * @param tail The tail pointer of the list passed by reference
 * @param cnode The current node marker to the struct that contains the sequence number
 * to placed into the list
 * @param head The head pointer of the list passed by reference
 */
void insert(struct node **tail, struct node **cnode, struct node **head)
{
    /* First node/item in the list */
    if(*tail == NULL)
    {
        *head = *cnode;
        *tail = *cnode;

    /* Makes current tail point to new node and sets new tail address */
    } else
    {
        (*tail)->next = *cnode;
        *tail = *cnode;
    }
}

/** Prints out the number for the seuqnce basis, the length of the sequence
 * and all the numbers in the seuqnce/linked list after 1 is found
 * @param head The head pointer of the list passed by copy
 * @param n The number that the sequence was based on
 */
void print_sequence(struct node *head, int n)
{
    printf("\nn = %d\n", n);

    /* New length of the list */
    int length = 0;

    /* Copy of the list before using head to count the list item # */
    struct node *sequence = head;

    /* Counts the length of the sequence */
    if(head != NULL)
    {
        while(head->next != NULL)
        {
            head = head->next;
            length++;
        }
    }

    printf("Cycle Length = %d\n", length);

    /**Prints out all the values of the list until 1 is reached, which ends the
     * list with a new line.
     */
    while(sequence->next != NULL)
    {
        if(sequence->x != 1)
            printf("%d, ", sequence->x);
        else
            printf("%d\n\n", sequence->x);
        
        sequence = sequence->next;
    }
}