#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
struct node 
{   

    int height;
    int key;
    
    Node* l;
    Node* r;

};

Node* BST_search (Node* root, int k);
Node* BST_node (int key);

void BST_remove (Node** root, int x);
void BST_insert (Node** root, int x);

void BST_traversal (Node* root);
void BST_ht (Node* root);

void node_trade (Node* x, Node* y);
void node_remove (Node** n); 

Node** node_leftmost (Node** n);
int node_ht (Node* root);


int main () 
{

    return 0;

}


Node* BST_search (Node* root, int k) 
{

    if (root == NULL) 
    {
        return NULL;
    }
    if (root -> key == k) 
    {
        return root;
    }
    else if (root -> key > k) 
    {
        return BST_search (root -> l, k);
    }
    else 
    {
        return BST_search (root -> r, k);
    }

}
Node* BST_node (int key) 
{

    Node* new_node = (Node*) malloc (sizeof(Node));
    if (new_node != NULL) 
    {
        new_node -> height = 0;
        new_node -> key = key;
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

void BST_insert (Node** root, int x) 
{

    Node* aux = *root;

    if (aux == NULL) 
    {
        *root = BST_node (x);
        return;
    }

    if (x < aux -> key) 
    {
        BST_insert (&(aux -> l), x);
    }
    else if (x > aux -> key) 
    {
        BST_insert (&(aux -> r), x);
    }
    else 
    {
        printf ("\nKey invalid");
    }

}    
void BST_remove (Node** root, int x) 
{

    Node* node_x = BST_search (*root, x);

    if (node_x == NULL) 
    {
        printf ("\nKey error");
        return;
    }

    // CASES: THE NODE HAS LESS THAN ONE SON OR HAS TWO SONS
    if (node_x -> l == NULL || node_x -> r == NULL) 
    {
        node_remove (&node_x);
    }
    else 
    {
        node_trade (*node_leftmost (&(node_x -> r)), node_x);

        node_remove (node_leftmost (&(node_x -> r)));
    }

    // THIS WAY TAKES O(N) IN ALL CASES TO RECALCULTE THE HEIGHT
    BST_ht (*root);

} 

void BST_traversal (Node* root) 
{
    
    // Preoder traversal
    if (root != NULL) 
    {   
        printf ("Height of %d: %d\n", root -> key, root -> height);
        BST_traversal (root -> l);
        BST_traversal (root -> r);
        return;
    }

    /* Postoder traversal 

        if (root != NULL) 
        {   
            BST_traversal (root -> l);
            BST_traversal (root -> r);
            printf ("%d ", root -> key);
            return;
        }

    */
    
    /* Inorder traversal 

        if (root != NULL) 
        {   
            BST_traversal (root -> l);
            printf ("%d ", root -> key);
            BST_traversal (root -> r);
            return;
        } 

    */

}
void BST_ht (Node* root) 
{

    if (root -> l != NULL) 
    {
        BST_ht (root -> l);
    }
    if (root -> r != NULL) 
    {
        BST_ht (root -> r);
    }

    int h = node_ht (root);

    root -> height = h;

}

void node_trade (Node* x, Node* y) 
{
    
    int aux = x -> key;
    x -> key = y -> key;
    y -> key = aux;

    aux = x -> height;
    x -> height = y -> height;
    y -> height = aux;

}
void node_remove (Node** n) 
{

    Node* aux = *n;

    Node* temp = aux -> l ? aux -> l : aux -> r;

    *n = temp;

    free (aux);

    return;

}

Node** node_leftmost (Node** n) 
{

    if ((*n) -> l == NULL) 
    {
        return n;
    }
    else 
    {
        return node_leftmost (&((*n) -> l));
    }

}
int node_ht (Node* root) 
{
    
    if (root == NULL) 
    {
        return 0;
    } 
    else 
    {   
        int l_height = node_ht (root -> l);
        int r_height = node_ht (root -> r);
        return ((l_height > r_height) ? l_height + 1 : r_height + 1);
    }

}
