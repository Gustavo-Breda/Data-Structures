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

Node* LHP_search (Node* root, int x);
Node* LHP_node (int data);

void LHP_decrease (Node** root, Node* x, int k);
void LHP_remove (Node** root, Node* x);
void LHP_insert (Node** root, int x);

void LHP_remove_minimum (Node** root);
void LHP_remodel (Node* node);

Node* LHP_Psearch (Node* root, Node* x);
Node* LHP_union (Node* ha, Node* hb);


int main () 
{
    
    /* Leftist HEAP 

        USE: EASIEST HEAP WHICH MERGE TWO HEAPS IN O(LOG N)

    */

    return 0;

}


Node* LHP_search (Node* root, int x) 
{

    Node* result = NULL;

    if (root -> data == x) 
    {
        return root;
    }

    result = LHP_search (root -> l, x);
    if (result != NULL) 
    {
        return result;
    }

    result = LHP_search (root -> r, x);
    if (result != NULL) 
    {
        return result;
    }

    return NULL;

}
Node* LHP_node (int data) 
{

    Node* new_node = (Node*) malloc (sizeof (Node));
    if (new_node != NULL) 
    {
        new_node -> data = data;
        new_node -> Prank = 1;

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

void LHP_decrease (Node** root, Node* x, int k) 
{

    if (x == *root) 
    {
        (*root) -> data = k;
        return;
    }
    else 
    {
        Node* parent_x = LHP_Psearch (*root, x);
        x -> data = k;

        // IF THE NEW DATA IS EVEN HIGHER THAN THE PARENT SO WE DO NOTHING
        if (parent_x -> data <= x -> data) 
        {
            return;
        }
        else 
        {
            // STEPS: REMOVING THE SUB-TREE (OR NODE) REMODEL THE TREE AND INSERT THE SUB-TREE REMOVED
            if (parent_x -> l == x) 
            {
                parent_x -> l = NULL;
            }
            else 
            {
                parent_x -> r = NULL;
            }
            
            LHP_remodel (parent_x);

            Node* aux = parent_x;  
            while (aux != *root) 
            {
                aux = LHP_Psearch (*root, aux);
                LHP_remodel (aux);
            }
            LHP_remodel (*root);

            *root = LHP_union (*root, x);
        }
    }

}
void LHP_remove (Node** root, Node* x) 
{

    LHP_decrease (root, x, INT_MIN);
    printf ("\nNova Root: %d", (*root) -> data);
    LHP_remove_minimum (root);

}
void LHP_insert (Node** root, int x) 
{

    Node* new_node = LHP_node (x);
    *root = LHP_union (*root, new_node);
    
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
        return;
    }

    if (node -> l -> Prank < node -> r -> Prank) 
    {
        Node* temp = node -> l;
        node -> l = node -> r;
        node -> r = temp;
        node -> Prank = node -> r -> Prank + 1;
    }

}

Node* LHP_Psearch (Node* root, Node* x) 
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

    result = LHP_Psearch (root -> l, x);
    if (result != NULL) 
    {
        return result;
    }

    result = LHP_Psearch (root -> r, x);
    if (result != NULL) 
    {
        return result;
    }

    return NULL;

}
Node* LHP_union (Node* ha, Node* hb) 
{

    if (ha == NULL) return hb;
    if (hb == NULL) return ha;
    
    // S1: THE SMALLEST IS THE ROOT
    if (ha -> data > hb -> data) 
    {
        Node* temp = ha;
        ha = hb;
        hb = temp;
    }
    
    // S2: PUT (hb) ON LAST NULL RIGHT CHILD AND REASSIGN RIGHT CHILDS
    ha -> r = LHP_union (ha -> r, hb);
    
    // S3: ASSESS THE CONDITIONS AND MAKE ADJUSTMENTS DURING THE UP-RECURSION
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
