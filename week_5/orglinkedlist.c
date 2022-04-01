#include <stdio.h>
#include <stdlib.h>

//define node type
typedef struct node
    {
        long int num;
        struct node *ptr;
    }
    node;

//prototype functions
node *new_node(int base);
void print_num(node *first, int amount);
void freeall(node *first);

int main (int argc, char *argv[])
{
    //check for valid user inputs
    if (argv[1] == 0)
    {
        printf("Usage: input value between 1 and 10\n");
        return 1;
    }

    int userval = atoi(argv[1]);

    if (userval > 10 || userval < 1)
    {
        printf("Usage: input value between 1 and 10\n");
        return 2;
    }

    //call function to make inital list (size based on used input)
    node *first = new_node(userval);

    //add new node after header to list
    node *newnode = malloc(sizeof(node));
    if (newnode == NULL)
    {
        printf("could not allocate memory\n");
        return 3;
    }

    newnode->ptr = first->ptr;
    newnode->num = 666;
    first->ptr = newnode;

    //add new node to end of list
    node *lastnode = malloc(sizeof(node));
    if (lastnode == NULL)
    {
        printf("could not allocate memory\n");
        return 4;
    }
    //WIP -- address of last element found. not sure how to change address of last element to addres off new element.
    for (node *tmp = first; tmp != NULL; tmp = tmp->ptr)
    {
        lastnode->ptr = tmp;
    }


    lastnode->num = 999;

    //call print list function
    print_num(first, 0);

    //call free allocated memory function
    freeall(first);
}

node *new_node(int base)
{
    struct node *head = malloc(sizeof(node));
    if (head == NULL)
    {
        printf("could not allocate memory\n");
        exit(1);
    }

    if (base > 1)
    {
        base--;
        head->ptr = new_node(base);
        head->num = head->ptr->num * 2;
    }
    else
    {
        head->ptr = NULL;
        head->num = 100;
    }
    return head;
}

void print_num(node *first, int amount)
{
    // Handle base case
    if (first == NULL)
    {
        return;
    }

    // Print values
    printf("Link # %i, value = %li\n", amount, first->num);
    print_num(first->ptr, amount + 1);
}

void freeall(node *first)
{
    if (first == NULL)
    {
        return;
    }

    freeall(first->ptr);
    free(first);
}
