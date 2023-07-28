#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
struct node 
{   

    int data;
    Node* next;

};

Node* LL_search (Node** root, int data);
Node* LL_node (int data);

void LL_copy (Node* root, Node* c_root);
void LL_show (Node* root);

void LL_remove (Node** root, Node* node);
void LL_insert (Node** root, int data);

void LL_suffix_sum (Node* root);


int main () 
{

    // LINKED LIST: SORTED AND WITHOUT HEAD AND TAIL NODES
    Node* LL = LL_create ();

    return 0;

}


Node* LL_search (Node** root, int data)
{

    Node* aux = *root;

    while (aux != NULL) 
    {
        if (aux -> data == data)
        {
            return aux;
        }
        aux = aux -> next;
    }
    printf ("\nInvalid data");

}
Node* LL_node (int data) 
{

    Node* new_node = (Node*) malloc (sizeof(Node));
    if (new_node != NULL) 
    {
        new_node -> data = data;
        new_node -> next = NULL;
    }
    else 
    {
        printf ("\nAllocation error");
        exit (1);
    }
    return new_node;
}

void LL_copy (Node* root, Node* c_root) 
{

    if (root == NULL) 
    {
        return;
    }

    Node* aux = root;

    while (aux != NULL) 
    {
        insert_final (c_root, aux -> data);
        aux = aux -> next;
    }

}
void LL_show (Node* root) 
{

    Node* aux = root;
    printf ("\nList: ");
    while (aux != NULL) 
    {
        printf ("%d ", aux -> data);
        aux = aux -> next;
    }

} 

void LL_remove (Node** root, Node* node) 
{   

    if (*root == NULL) 
    {
        return;
    }

    Node* aux = *root;
    while (aux -> next != NULL) 
    {
        if (aux -> next = node) 
        {
            aux -> next = aux -> next -> next;
        }
        aux = aux -> next;
    }
    
}
void LL_insert (Node** root, int data) 
{

    // INSERT IN SORTED LIST: THIS WAY HAS O(N**2) 
    Node* new = LL_node (data);
    Node* aux = root;

    // SORTED LIST: THIS WAY HAS O(N^2) 
    if (aux == NULL) 
    {   
        root = new;
    }
    else if (aux -> data > data) 
    {   
        new -> next = aux;
        root = new;
    } 
    else 
    {
        // SEARCH THE INDEX OF NEW
        while (aux -> next != NULL) 
        {
            if (aux -> next -> data <= data) 
            {
                aux = aux -> next;
            } 
            else 
            {
                break;
            }
        }

        if (aux -> next == NULL) 
        {
            aux -> next = new;
        } 
        else 
        {
            Node* aux_next = aux -> next;
            aux -> next = new;
            new -> next = aux_next;
        }
    }

}

void LL_suffix_sum (Node* root) 
{   

    if (root == NULL) 
    {
        return;
    }

    // COMPLEXITY: THIS WAY HAS O(2N) OR O(N)
    int sum = 0;
    Node* aux = root;
    while (aux -> next != NULL) 
    {
        sum += aux -> data;
    }
    
    aux = root;
    int sum_reversed = sum;
    while (aux -> next != NULL) 
    {
        sum_reversed -= aux -> data;
        aux -> data += sum_reversed;
    }

}
