#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node Node;
struct node 
{   

    int order;
    int data;

    Node* brother;
    Node* father;
    Node* child;

};

Node* BHP_create (int size);
Node* BHP_node (int data);

Node* BHP_minimum (Node* vector);
Node* BHP_find (Node* vector, int x);
Node* BHP_find_node (Node* node, int x);

void BHP_decrease (Node* vector, int x, int k);
void BHP_remove (Node* vector);

void BHP_heapify (Node* vector, Node* node);
void BHP_insert (Node* vector, int data);
void BHP_union (Node* na, Node* nb);


int main () 
{

    /* EXAMPLE 
    
        Node* B = BHP_create (10);

        for (int i = 1; i <= 16; i ++) 
        {
            BHP_insert (B, i);
        }

        BHP_remove (B);

        Node* minimum = BHP_minimum (vector);

        printf ("\nROOT HEAP B3: %d", vector[3].data);
        printf ("\nMINIMUN VALUE IN HEAP VECTOR: %d\n\n", minimum -> data);
    
    */

    return 0;

}


Node* BHP_create (int size) 
{

    Node* new_vector = malloc (size * sizeof (Node));
    if (new_vector != NULL) 
    {
        for (int i = 0; i < size; i ++) 
        {
            new_vector [i] = *BHP_node (0);
        }

        // CREATE SENTINEL NODE TO AVOID "SIZE" ARGUMENT IN EVERY FUNCTION
        Node sentinel;
        sentinel.order = 0;
        sentinel.child = NULL;
        sentinel.father = NULL;
        sentinel.brother = NULL;
        sentinel.data = INT_MAX;

        new_vector [size] = sentinel;
    }

    return new_vector;
    
}
Node* BHP_node (int data) 
{

    Node* new_node = (Node*) malloc (sizeof (Node));
    if (new_node != NULL) 
    {
        new_node -> data = data;
        new_node -> order = 0;

        new_node -> brother = NULL;
        new_node -> father = NULL;
        new_node -> child = NULL;
    }

    return new_node;

}

Node* BHP_minimum (Node* vector) 
{

    Node* aux = NULL;

    for (int i = 0; vector [i].data != INT_MAX; i ++) 
    {
        if ((vector [i].data) != 0) 
        {
            if (aux == NULL) 
            {
                aux = &(vector [i]);
            }
            else if ((vector [i].data) < aux -> data) 
            {
                aux = &(vector [i]);
            }
        }
    }

    return aux;
    
}
Node* BHP_find (Node* vector, int x) 
{

    Node* aux = NULL;
    for (int i = 0; vector[i].data != INT_MAX; i++) 
    {

        // S1: FIND FOR EACH VECTOR ELEMENT
        if (vector[i].data == x) 
        {
            aux = vector[i].child;
        }
        else if (vector[i].data != 0) 
        {
            aux = BHP_find_node (vector[i].child, x);
        }

        // S2: RETURN THE ANSWER OF THE FIND
        if (aux != NULL) 
        {
            return aux;
        }

    }

    return NULL;

}
Node* BHP_find_node (Node* node, int x) 
{

    Node* result = NULL;

    if (node == NULL) 
    {
        return NULL;
    }
    
    if (node -> data == x) 
    {
        return node;
    }
    
    result = BHP_find_node (node -> child, x);
    if (result != NULL) 
    {
        return result;
    }
    
    result = BHP_find_node (node -> brother, x);
    if (result != NULL) 
    {
        return result;
    }
    
    return NULL;

}

void BHP_decrease (Node* vector, int x, int k) 
{

    // S1: FIND THE NODE
    Node* node = BHP_find (vector, x);
    if (node == NULL) 
    { 
        return;
    }
    
    // S2: UPDATE NODE DATA
    node -> data = k;

    // S3: HEAPIFY UPWARDS
    while (node -> father != NULL && (node -> data < node -> father -> data))
    {

        int temp = node -> data;
        node -> data = node -> father -> data;
        node -> father -> data = temp;

        node = node -> father;

    }

}
void BHP_remove (Node* vector) 
{

    Node* aux_ch;
    Node* node;
    Node* aux;

    node = BHP_minimum (vector);
    if (node == NULL) 
    {
        return;
    }

    // S1: REDEFINE THE NODE'S POSITIONS
    aux = node -> child; 
    while (aux -> child != NULL) 
    {

        aux_ch = aux -> child;
        aux -> child = aux -> child -> brother;

        aux_ch -> brother = NULL;
        aux_ch -> father = NULL;

        BHP_heapify (vector, aux_ch);

    }

    // S2: UPDATE THE NODE VECTOR
    node -> child = NULL;
    node -> order = 0;
    node -> data = 0;
    
}

void BHP_heapify (Node* vector, Node* node) 
{
    
    // S1: (o) IS USED TO TRACK THE CURRENT ORDER
    int o = node -> order;
    int i = o;

    // S2: IF (V [o] == NULL) THEN ORDER DOESNT CHANGE AND LOOP STOP
    while (o >= i) 
    {   
        if (vector [o].data == INT_MAX) 
        {
            return;
        }

        // S3: REMOVE THE OLD RELATIONSHIPS OF VECTOR NODE
        if (node -> father != NULL) 
        {
            node -> father -> child = NULL;
            node -> father -> order = 0;
            node -> father -> data = 0;
        }
        
        BHP_union (node, &(vector [o]));
        node = vector [o].child;

        o = node -> order;
        i++;

    }

}
void BHP_insert (Node* vector, int data) 
{

    Node* new_node = BHP_node (data); 

    BHP_heapify (vector, new_node);

}
void BHP_union (Node* na, Node* nb) 
{

    // CASE 1: THE NEXT VECTOR NODE IS EMPTY
    if (nb -> data == 0) 
    {
        na -> father = nb;

        nb -> child = na;
        nb -> data = na -> data;
        nb -> order = na -> order;
    }
    // CASE 2: THE NEXT VECTOR NODE IS HIGHER
    else if (na -> data < nb -> data) 
    {
        // S1: UPDATE THE nb ROOT FATHER
        nb -> child -> father = na;
        na -> father = nb;

        // S2: UPDATE THE BROTHERHOOD
        if (na -> child != NULL) 
        {
            Node* aux = na -> child;

            // S3: FIND THE YOUNGER CHILD OF na
            while (aux -> brother != NULL) 
            {
                aux = aux -> brother;
            }
            aux -> brother = nb -> child;
        }
        else 
        {
            na -> child = nb -> child;
        }

        // S4: UPDATE THE nb STATS
        nb -> child = na;
        nb -> order += 1;
        nb -> child -> order += 1;
    }
    else 
    {
        na -> father = nb -> child;

        if (nb -> child -> child != NULL) 
        {
            Node* aux = nb -> child -> child;

            while (aux -> brother != NULL) 
            {
                aux = aux -> brother;
            }
            aux -> brother = na;
        }
        else 
        {
            nb -> child -> child = na;
        }

        nb -> child -> order += 1;
        nb -> order += 1;
    }

}
