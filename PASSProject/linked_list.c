#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

linked_list* init_linked_list()
{
    linked_list *list;

    #ifdef DEBUG
        printf("Init linked list\n");
    #endif // DEBUG

    list = (linked_list*)malloc(sizeof(linked_list));
	list->root_node = init_node(NULL);
    list->list_size = 0;

    #ifdef DEBUG
        printf("Have allocated memory for linked list\n");
    #endif // DEBUG

    return list;
}

node* init_node(void *data)
{
    node *n;

    #ifdef DEBUG
        printf("Init linked node\n");
    #endif // DEBUG

    n = (node*)malloc(sizeof(struct node));
    n->data = data;
    n->next = NULL;
    n->previous = NULL;

    #ifdef DEBUG
        printf("Have allocated memory for linked node and assigned data\n");
    #endif // DEBUG

    return n;
}

bool isEmpty(linked_list *ll)
{
    #ifdef DEBUG
        printf("Checking emptyness of linked list\n");
    #endif // DEBUG

    #ifdef DEBUG
        printf("List size: %d\n", ll->list_size);
    #endif // DEBUG


    if(ll->list_size == 0)
    {
        #ifdef DEBUG
            printf("Linked list is empty\n");
        #endif // DEBUG

        return true;
    }
    else
    {
        #ifdef DEBUG
            printf("Linked list is NOT empty\n");
        #endif // DEBUG

        return false;
    }
}


/* Add a new node onto the linked list then return a pointer to the new node */
node* add_node(linked_list *ll, void *data)
{
    node *new_node, *root_node;

    #ifdef DEBUG
        printf("Adding node to linked list\n");
    #endif // DEBUG

    new_node = init_node(data);

    if(isEmpty(ll))
    {

        #ifdef DEBUG
            printf("Assigned nodes next and previous to self\n");
        #endif // DEBUG

        new_node->next = new_node;
        new_node->previous = new_node;

        #ifdef DEBUG
            printf("Assigning linked lists root node to new node\n");
        #endif // DEBUG

        ll->root_node = new_node;

    }
    else
    {
        root_node = ll->root_node; // Get a reference to the link lists root node

        #ifdef DEBUG
            printf("Placing new node in between root node and root node -> next\n");
        #endif // DEBUG

        new_node->next = root_node->next;
        new_node->next->previous = new_node;
        root_node->next = new_node;
        new_node->previous = root_node;
    }

    ll->list_size++;

    #ifdef DEBUG
        printf("New node has been added\n");
    #endif // DEBUG

    return new_node;
}

void traverse(linked_list *linked_list, void (*functionPtr)(void *data))
{
    node *root_node, *current;

    if(isEmpty(linked_list) || linked_list == NULL)
    {
        return;
    }

    root_node = linked_list->root_node;

    #ifdef DEBUG
        printf("About to traverse linked list\n");
    #endif // DEBUG

    current = root_node;
    do
    {
        #ifdef DEBUG
            printf("About to perform function on node\n");
        #endif // DEBUG
        (*functionPtr)(current->data);
        current = current->next;

    }while(current != root_node);

    #ifdef DEBUG
        printf("Done traversing linked list\n");
    #endif // DEBUG
}

void remove_node(linked_list *ll, node *n)
{
    #ifdef DEBUG
        printf("About to remove node from list\n");
    #endif // DEBUG

    if(n != NULL)
    {
        n->previous->next = n->next;
        n->next->previous = n->previous;
    }

    #ifdef DEBUG
        printf("Done removing node from list\n");
    #endif // DEBUG

    ll->list_size--;

    destroy_node(n);
}

void destroy_node(node *n)
{
    #ifdef DEBUG
        printf("About to free nodes memory\n");
    #endif // DEBUG

    n->data = NULL;
    n->next = NULL;
    n->previous = NULL;

    free(n);
    n = NULL;

    #ifdef DEBUG
        printf("Done freeing nodes memory\n");
    #endif // DEBUG
}

void destroy_list(linked_list *ll)
{
    node *root_node, *current, *next;

    #ifdef DEBUG
        printf("Destroying linked list\n");
    #endif // DEBUG

    if(ll == NULL)
    {
        return;
    }

    if(!isEmpty(ll))
    {
        root_node = ll->root_node;

        current = root_node;
        while(ll->list_size > 0)
        {
            next = current->next;

            #ifdef DEBUG
                printf("Removing node: %d\n", ll->list_size);
            #endif // DEBUG

            destroy_node(current);

            ll->list_size--;

            current = next;

        }
    }

    free(ll);
    ll = NULL;

    #ifdef DEBUG
        printf("Done Destroying linked list\n");
    #endif // DEBUG
}

void traverse_comparison(linked_list *ll, void(*functionPtr)(linked_list *ll, void *data, void *comparison_data), void *comparison)
{
	node *root_node, *current;
	int i =0;

	if (isEmpty(ll) || ll == NULL)
	{
		return;
	}

	root_node = ll->root_node;

#ifdef DEBUG
	printf("About to traverse linked list\n");
#endif // DEBUG

	current = root_node->next;
	do
	{
#ifdef DEBUG
		printf("About to perform function on node\n");
#endif // DEBUG
		(*functionPtr)(ll, current, comparison);
		current = current->next;
		i++;

	} while (i < ll->list_size);

#ifdef DEBUG
	printf("Done traversing linked list\n");
#endif // DEBUG
}