/**
 * @file lab8.h
 * @brief Function prototypes for lab8.c
 * @author Benjamin Wilson
 * @date Fall 2021
 * @todo none
 * @bug none
 */

#ifndef LAB8_H
#define LAB8_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

struct node
{
    double x;

    /* Self-referential pointer that points to the next node */
    struct node *next;
};

/* Function Prototypes for lab8.c */
struct node *create_node();
void print_node(struct node *n);
struct node *insert_head(struct node **head, struct node **n, struct node **tail);
struct node *insert_middle(struct node **head, struct node **n, struct node **tail, struct node **marker, int position);
struct node *insert_tail(struct node **tail, struct node **n, struct node **head);
void print_list(struct node *head);
struct node *delete_node(double d, struct node **head, struct node **tail, struct node **marker);
struct node *delete_list(struct node **head, struct node **marker);
int count_nodes(struct node *head);
struct node *find_node(double d, struct node **head);

#endif
