#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node Node;
struct node 
{   

    int Prank;
    int data;

    Node* l;
    Node* r;

};

Node* LHP_node (int data);

void LHP_decrease (Node* root, Node* x, int k);
void LHP_remove (Node** root, Node* x);
void LHP_insert (Node** root, int x);

void LHP_remove_minimum (Node** root);
Node* LHP_find_father (Node* root, Node* x);

Node* LHP_union (Node* ha, Node* hb);
void LHP_remodel (Node* node);


int main () 
{
    
    /* Leftist HEAP 

        USE: EASIEST HEAP WHICH MERGE TWO HEAPS IN O(LOG N)

    */

    /* EXAMPLE 

        Node* root = NULL;

        LHP_insert (&root, 7);
        LHP_insert (&root, 12);
        LHP_insert (&root, 8);
        LHP_insert (&root, 9);
        LHP_insert (&root, 30);
        LHP_insert (&root, 18);
        LHP_insert (&root, 17);
        LHP_insert (&root, 20);
        LHP_insert (&root, 25);

        printf ("\n7: %d", root -> data);
        printf ("\n12: %d", root -> r -> data);

        LHP_remove (&root, root -> l);

        printf ("\n8: %d", root -> data);

    */
    
    return 0;

}


Node* LHP_node (int data) 
{

    Node* new_node = (Node*) malloc (sizeof (Node));
    if (new_node != NULL) 
    {
        new_node -> data = data;
        new_node -> Prank = 0;

        new_node -> l = NULL;
        new_node -> r = NULL;
        return new_node;
    }
    else
    {
        printf ("\nAllocation error");
        exit (1);
    }

}

void LHP_decrease (Node* root, Node* x, int k) 
{

    if (x == root) 
    {
        root -> data = k;
        return;
    }
    else 
    {
        Node* x_father = LHP_find_father (root, x); 
        if (x_father -> data > x -> data) 
        {
            if (x_father -> l == x) 
            {
                x_father -> l = NULL;
            }
            else 
            {
                x_father -> r = NULL;
            }
            
            LHP_remodel (x_father);

            Node* aux = NULL;  
            while (aux != root) 
            {
                aux = LHP_find_father (root, aux);
                LHP_remodel (aux);
            }
            LHP_remodel (root);
        }
        LHP_union (root, x);
    }

}
void LHP_remove (Node** root, Node* x) 
{

    LHP_decrease (*root, x, INT_MIN);
    LHP_remove_minimum (root);

}
void LHP_insert (Node** root, int x) 
{

    Node* new_node = LHP_node (x);
    *root = LHP_union (*root, new_node);
    
}

// PROBABLY THERES A SMARTEST WAY TO DO THE DECREASE OPERATION
Node* LHP_find_father (Node* root, Node* x) 
{

    Node* result = NULL;

    if (root == NULL) 
    {
        return NULL;
    }
    if (root -> l == x || root -> r == x) 
    {
        return root;
    }

    result = LHP_find_father (root -> l, x);
    if (result != NULL) 
    {
        return result;
    }

    result = LHP_find_father (root -> r, x);
    if (result != NULL) 
    {
        return result;
    }

    return NULL;

}
void LHP_remove_minimum (Node** root) 
{

    if (*root == NULL) 
    {
        return;
    }

    Node* ha = (*root) -> l;
    Node* hb = (*root) -> r;

    free (*root);

    *root = LHP_union (ha, hb);
    
}

Node* LHP_union (Node* ha, Node* hb) 
{

    if (ha == NULL) return hb;
    if (hb == NULL) return ha;
    
    // RECURSION 1: THE SMALLEST IS THE ROOT
    if (ha -> data > hb -> data) 
    {
        Node* temp = ha;
        ha = hb;
        hb = temp;
    }
    
    // RECURSION 2: PUT (hb) ON LAST NULL RIGHT CHILD AND REASSIGN RIGHT CHILDS
    ha -> r = LHP_union (ha -> r, hb);
    
    // RECURSION 3: ASSESS THE CONDITIONS AND MAKE ADJUSTMENTS DURING THE UP-RECURSION
    if (ha -> l == NULL) 
    {
        ha -> l = ha -> r;
        ha -> r = NULL;
    }
    else 
    {
        if (ha -> l -> Prank < ha -> r -> Prank) 
        {
            Node* temp = ha -> l ;
            ha -> l = ha -> r;
            ha -> r = temp;
        }
        
        ha -> Prank = ha -> r -> Prank + 1;
    }
    
    return ha;
    
}
void LHP_remodel (Node* node) 
{

    if (node -> r == NULL) 
    {
        node -> Prank = 1;
        return;
    }
    else if (node -> l == NULL) 
    {
        node -> l = node -> r;
        node -> r = NULL;

        node -> Prank = 1;
    }

    if (node -> l -> Prank < node -> r -> Prank) 
    {
        Node* temp = node -> l;
        node -> l = node -> r;
        node -> r = temp;
        node -> Prank = node -> r -> Prank + 1;
    }

}
