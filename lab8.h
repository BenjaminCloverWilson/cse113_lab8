/**
 * @file lab8.h
 * @brief Function prototypes for lab8.c
 * @author Benjamin Wilson
 * @date Fall 2021
 * @todo Write & implement functions
 * @bug Probably everything here
 */

#ifndef LAB8_H
#define LAB8_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct node
{
    double x;

    /* Self-referential pointer that points to the next node */
    struct node *next;
};

/* Function Prototypes */
struct node *create_node();
void print_node(struct node *n);
void insert_head(struct node **head, struct node **n, struct node **tail);
void insert_middle(struct node **head, struct node **n, struct node **tail, struct node **marker, int position);
void insert_tail(struct node **tail, struct node **n, struct node **head);
void print_list(struct node *head);
void delete_node(double x);
void delete_list();
int count_nodes(struct node *head);
struct node *find_node(double x);

#endif