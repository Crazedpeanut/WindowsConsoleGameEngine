#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include <stdbool.h>

typedef struct node
{
    void *data;
    struct node *next;
    struct node *previous;
} node;

typedef struct
{
    node *root_node;
    int list_size;

}linked_list;

linked_list* init_linked_list();
node* init_node(void *data);
void destroy_node(node *n);
bool isEmpty(linked_list *ll);

/* Add a new node onto the linked list then return a pointer to the new node */
node* add_node(linked_list *ll, void *data);

void remove_node(linked_list *ll, node *n);
void traverse(linked_list *ll, void (*functionPtr)(void *data));
void traverse_comparison(linked_list *ll, void(*functionPtr)(linked_list *ll, node *node, void *comparison_data), void *comparison);
void destroy_list(linked_list *ll);

#endif // LINKED_LIST_H_INCLUDED
