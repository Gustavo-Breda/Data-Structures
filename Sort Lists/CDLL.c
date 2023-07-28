#include <stdio.h> 
#include <stdlib.h>

typedef struct list List;
struct list 
{   

    Node* head;
    Node* tail;

};

typedef struct node Node;
struct node 
{  

    Node* next;
    Node* prev;
    int data;
    
};

Node* CDLL_search (List* L, int data);
Node* CDLL_node (int data);

void CDLL_remove (List* L, Node* node);
void CDLL_show (List* L);
void CDLL_free (List *L);

void CDLL_insert_start (List* L, int data);
void CDLL_remove_start (List* L);

void CDLL_insert_final (List* L, int data);
void CDLL_remove_final (List* L);

void insert_node (Node* na, Node* nb);
void remove_node (Node* na);


int main () 
{

    // LINKED LIST: DOUBLY LINKED, CIRCULAR AND WITH HEAD AND TAIL POINTERS
    List* L = malloc (sizeof (List));
    L -> head = NULL;
    L -> tail = NULL;

    return 0;

}


Node* CDLL_search (List* L, int data) 
{   

    Node* aux = L -> head;
    do 
    {

        if (aux -> data == data) 
        {
            return aux;
        }
        aux = aux -> next;

    } while (aux != L -> head);

    printf ("\ninvalid data");
    return NULL;

}
Node* CDLL_node (int data) 
{

    Node* new_node = (Node*) malloc (sizeof(Node));
    if (new_node != NULL) 
    {
        new_node -> data = data;
        new_node -> next = new_node;
        new_node -> prev = new_node;

        return new_node;
    }
    else 
    {
        printf ("\nAllocation error");
        exit (1);
    }

}

void CDLL_remove (List* L, Node* node) 
{

    if (L -> head == NULL) 
    {
        printf ("\nEmpty List");
        return;
    }

    if (L -> head == node) 
    {
        CDLL_remove_start (L);
    } 
    else if (L -> tail == node) 
    {
        CDLL_remove_final (L);
    } 
    else 
    {   
        remove_node (node);
    }

}
void CDLL_show (List* L) 
{

    Node* aux = L -> head;
    printf ("Lista: ");
    if (aux != NULL) 
    {

        do 
        {
            printf ("%d ", aux -> data);
            aux = aux -> next;
        } while (aux != L -> head);

    }

}
void CDLL_free (List *L) 
{
    if (L == NULL) 
    {
        return;
    }

    Node* aux = L -> head;
    while (aux != NULL) 
    {
        Node* temp = aux;
        aux = aux -> next;
        free (temp);
    }

    L -> head = NULL;
    L -> tail = NULL;

    free (L);

}

void CDLL_insert_start (List* L, int data) 
{

    Node* new_node = CDLL_node (data);
    if (L -> head == NULL) 
    {   
        L -> head = new_node;
        L -> tail = new_node;
    } 
    else 
    {
        insert_node (L -> head -> prev, new_node);
        L -> head = new_node;
    }

}
void CDLL_remove_start (List* L) 
{

    if (L -> head == NULL) 
    {
        return;
    }
    
    Node* aux = L -> head -> next;
    remove_node (L -> head); 
    L -> head = aux;

}

void CDLL_insert_final (List* L, int data) 
{

    Node* new_node = CDLL_node (data);
    if (L -> head == NULL) 
    {   
        L -> head = new_node;
        L -> tail = new_node;
    } 
    else 
    {
        insert_node (L -> tail, new_node);
        L -> tail = new_node;
    }
    
}
void CDLL_remove_final (List* L) 
{

    if (L -> head == NULL) 
    {
        return;
    }

    Node* aux = L -> tail -> prev;
    remove_node (L -> tail); 
    L -> tail = aux;

}

// AUX FUNCTIONS
void insert_node (Node* na, Node* nb) 
{

    na -> next -> prev = nb;
    nb -> next = na -> next -> prev;

    na -> next = nb;
    nb -> prev = na;

}
void remove_node (Node* na) 
{

    na -> prev -> next = na -> next;
    na -> next -> prev = na -> prev;

    na -> next = NULL;
    na -> prev = NULL;
    free (na);
    
}
