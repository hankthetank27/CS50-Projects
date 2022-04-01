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
void addmiddle(node *ogstart, int placement);

int main (int argc, char *argv[])
{
    //check for valid user inputs
    if (argv[1] == 0 && argv[2] == 0)
    {
        printf("Usage: input total value, and shift value between 1 and 10\n");
        return 1;
    }
    
    int userval = atoi(argv[1]) - 1;
    int shift = atoi(argv[2]);
    
    if (userval > 10 || userval < 1 || shift > 10  || shift < 1)
    {
        printf("Usage: input total value, and shift value between 1 and 10\n");
        return 2;
    }
    
    //call function to make inital list (size based on used input)
    node *first = new_node(userval);
    
    //add new node to user input index value into list
    addmiddle(first, shift);
    
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
    printf("Link # %i, value = %li\n", amount + 1, first->num);
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

void addmiddle(node *ogstart, int placement)
{
    node *newnode = malloc(sizeof(node));
    if (newnode == NULL)
    {
        printf("could not allocate memory\n");
        exit(2);
    }
    
    node *pre = ogstart;
    node *curr = ogstart;
    for (int i = 0; i < placement - 1; i++) 
    {
        if (curr == NULL)
        {
            newnode->ptr = NULL;
            break;
        }
        else
        {
            pre = curr;
            curr = curr->ptr;
            newnode->ptr = curr;
        }
    }
    newnode->num = 666;
    pre->ptr = newnode;
    return;
}