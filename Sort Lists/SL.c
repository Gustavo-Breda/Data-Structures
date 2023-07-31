#include <stdio.h> 
#include <stdlib.h>

typedef struct queue Queue;
struct queue 
{   

    int* vector;

    int length;
    int head;
    int tail;

};

typedef struct stack Stack;
struct stack 
{   

    int* vector;
    int top;

};

Queue* SQ_create (int size); 
Stack* SS_create (int size);

void SQ_show (Queue* Q);
void SS_show (Stack* S); 

void SQ_enqueue (Queue* Q, int data);
void SS_push (Stack* S, int data); 

int SQ_dequeue (Queue* Q);
int SS_pop (Stack* S);


int main () 
{

    /*  SEQUENTIAL LISTS EXAMPLE 

        Queue* queue = SQ_create (100);
        Stack* stack = SS_create (100);
        
        SQ_show (queue);
        SS_show (stack);

        free (queue -> vector); // Free the memory allocated for the vectors.
        free (queue);
        free (stack -> vector); // Free the memory allocated for the vectors.
        free (stack);
    
    */

    return 0;

}


Queue* SQ_create (int size) 
{

    Queue* Q = malloc (sizeof (Queue));
    if (Q != NULL)
    {
        Q -> vector = (int*) malloc ((size + 1) * sizeof (int));
        Q -> length = size;
        Q -> head = 1;
        Q -> tail = 1;

        int input;
        int i = 1;

        printf ("\nElements of Queue (non-numeric to descontinue): \n");
        while ((scanf ("%d", &input)) == 1) 
        {
            
            SQ_enqueue (Q, input);
            
            if (++i == size) 
            {
                printf ("Maximum size reached");
                break;
            }

        }
        getchar ();
        
        return Q;
    }
    else 
    {
        printf ("\nAllocation error");
        exit(1);
    }

}
Stack* SS_create (int size) 
{

    Stack* S = (Stack*) malloc (sizeof(Stack));
    if (S != NULL) 
    {
        S -> vector = (int*) malloc ((size + 1) * sizeof(int));
        S -> top = 0;
        
        int input;
        int i = 1;

        printf ("\nElements of Stack (non-numeric to descontinue): \n");
        while ((scanf ("%d", &input)) == 1) 
        {
            
            SS_push (S, input);
            
            if (++i == size + 1) 
            {
                printf ("Maximum size reached");
                break;
            }

        }
        getchar ();
        
        return S;        
    }
    else 
    {
        printf ("\nAllocation error");
        exit(1);
    }

}

void SQ_show (Queue* Q) 
{

    if (Q -> head == Q -> tail) 
    {
        printf ("\nEmpty Queue\n");
    }
    else 
    {
        printf ("\nQueue: ");
        for (int i = Q -> head; i < Q -> tail; i++) 
        {
            printf ("%d ", Q -> vector [i]);
        }
    }
    
}
void SS_show (Stack* S) 
{

    if (S -> top == 0) 
    {
        printf ("Empty Stack");
    }
    else 
    {
        printf ("\nStack: ");
        for (int i = 1; i <= S -> top; i++) 
        {
            printf ("%d ", S -> vector [i]);
        }
    }
    
}

void SQ_enqueue (Queue* Q, int data) 
{

    if (Q -> head == Q -> tail + 1 || (Q -> head == 1 && Q -> tail == Q -> length)) 
    {
        printf ("\n Full Queue \n");
        return;
    }
    
    Q -> vector [Q -> tail] = data;

    if (Q -> tail == Q -> length) 
    {
        Q -> tail = 1;
    }
    else 
    {
        Q -> tail += 1;
    }

}
void SS_push (Stack* S, int data) 
{

    S -> top += 1;
    S -> vector [S -> top] = data;

}

int SQ_dequeue (Queue* Q) 
{

    if (Q -> head == Q -> tail )
    {
        printf ("\n Empty Queue \n");
        exit (1);
    }

    int x = Q -> vector [Q -> head];

    if (Q -> head == Q -> length) 
    {
        Q -> head = 1;
    }
    else 
    {
        Q -> head += 1;
    }
    return x;

}
int SS_pop (Stack* S) 
{

    if (S -> top == 0) 
    {
        printf ("\n Empty Stack \n");
        exit (1);
    }
    else 
    {
        S -> top -= 1;
        return (S -> vector [S -> top + 1]);
    }

}
