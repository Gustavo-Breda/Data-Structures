#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
struct node 
{   

    int key;
    int sum;

    Node* l;
    Node* r;

};

enum AVL_balance 
{
    AVL_RIGHT_HEAVY = 1,
    AVL_LEFT_HEAVY = -1,
    AVL_BALANCED = 0,
};

Node* AVL_find (Node* root, int k);
Node* AVL_node (int key);

void AVL_insert_recursive (Node** root, int x, int* h);
void AVL_insert (Node** root, int x);

void AVL_remove_recursive (Node** root, int k, int* h);
void AVL_remove (Node** root, int k);

void AVL_L_rotation (Node** root, int* h);
void AVL_R_rotation (Node** root, int* h);
void AVL_traversal (Node* root);

void node_balance_after_insert (Node** n, int side, int* h);
void node_balance_after_remove (Node** n, int side, int* h);

void node_remove (Node** n, int* h);
void node_trade (Node* x, Node* y); 

Node* node_leftmost (Node* n);

void to_RIGHT (Node* x, Node* y);
void to_LEFT (Node* x, Node* y);


int main () 
{

    /* AVL 

        CONCEPT: IT IS A COMPLETE BINARY TREE WICH HAS ALWAYS H(N) = LOG N
        COMPLEXITY: HAS O(LOG N) IN WORST CASE TO EACH DICT OPERATION
    
    */

    return 0;

}


Node* AVL_find (Node* root, int k) 
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
        return AVL_find (root -> l, k);
    }
    else 
    {
        return AVL_find (root -> r, k);
    }

}
Node* AVL_node (int key) 
{

    Node* new_node = (Node*) malloc (sizeof(Node));
    if (new_node != NULL) 
    {   
        new_node -> key = key;
        new_node -> l = NULL;
        new_node -> r = NULL;
        new_node -> sum = 0;

        return new_node;
    }
    else 
    {
        printf ("\nAllocation error");
        exit (1);
    }

}

void AVL_insert_recursive (Node** root, int x, int* h) 
{

    Node* aux = *root;
    if (aux == NULL) 
    {
        *root = AVL_node (x);
        *h = 1;
    }
    else if (aux -> key < x) 
    {
        AVL_insert_recursive (&(aux -> r), x, h);
        if (*h == 1) 
        {
            node_balance_after_insert (root, 1, h);
        }
    }
    else if (aux -> key > x) 
    {
        AVL_insert_recursive (&(aux -> l), x, h);
        if (*h == 1) 
        {
            node_balance_after_insert (root, 0, h);
        }
    }
    else 
    {
        return;
    }

}
void AVL_insert (Node** root, int x) 
{
    
    int h = 0;

    AVL_insert_recursive (root, x, &h);

}

void AVL_remove_recursive (Node** root, int k, int* h) 
{

    Node* aux = *root;
    if (aux == NULL) 
    {
        return;
    }
    else if (aux -> key < k) 
    {   
        AVL_remove_recursive (&(aux -> r), k, h);
        if (*h == 1) 
        {
            node_balance_after_remove (root, 0, h);
        }
    }
    else if (aux -> key > k) 
    {
        AVL_remove_recursive (&(aux -> l), k, h);
        if (*h == 1) 
        {
            node_balance_after_remove (root, 1, h);
        }
    }
    else 
    {
        node_remove (root, h);
    }

}
void AVL_remove (Node** root, int k) 
{

    int h = 0;

    AVL_remove_recursive (root, k, &h);

}

void AVL_L_rotation (Node** root, int* h) 
{

    Node* X = *root;
    Node* Y = X -> r;

    // CASES: EVALUATE IF IS LEFT-ROTATION, RIGHT-LEFT ROTATION OR REMOVE-SITUATION
    if (Y -> sum == AVL_RIGHT_HEAVY) 
    {
        to_LEFT (X, Y);

        X -> sum = AVL_BALANCED;
        Y -> sum -= 1;
        
        *root = Y;
        *h = 0;
    }
    else if (Y -> sum == AVL_BALANCED)
    {
        to_LEFT (X, Y);

        X -> sum = AVL_RIGHT_HEAVY;
        Y -> sum = AVL_LEFT_HEAVY;
        
        *root = Y;
        *h = 0;
    }
    else 
    {
        Node* Z = Y -> l;

        to_RIGHT (Y, Z);
        to_LEFT (X, Z);

        if (Z -> sum == 1) 
        {
            X -> sum = AVL_LEFT_HEAVY;
            Y -> sum = AVL_BALANCED;
        }
        else if (Z -> sum == 1) 
        {
            X -> sum = AVL_BALANCED;
            Y -> sum = AVL_RIGHT_HEAVY;
        }
        else 
        {
            X -> sum = AVL_BALANCED;
            Y -> sum = AVL_BALANCED;
        }

        Z -> sum = 0;
        *root = Z;
        *h = 0;
    }

}
void AVL_R_rotation (Node** root, int* h) 
{

    Node* X = *root;
    Node* Y = X -> l;

    // CASES: EVALUATE IF IS RIGHT-ROTATION, LEFT-RIGHT ROTATION OR REMOVE-SITUATION
    if (Y -> sum == AVL_LEFT_HEAVY) 
    {
        to_RIGHT (X, Y);

        X -> sum = AVL_BALANCED;
        Y -> sum += 1;

        *root = Y;
        *h = 0;
    }
    else if (Y -> sum == AVL_BALANCED)
    {
        to_RIGHT (X, Y);

        X -> sum = AVL_LEFT_HEAVY;
        Y -> sum = AVL_RIGHT_HEAVY;
        
        *root = Y;
        *h = 0;
    }
    else 
    {
        Node* Z = Y -> r;

        to_LEFT (Y, Z);
        to_RIGHT (X, Z);

        if (Z -> sum == -1) 
        {
            X -> sum = AVL_RIGHT_HEAVY;
            Y -> sum = AVL_BALANCED;
        }
        else if (Z -> sum == 1) 
        {
            X -> sum = AVL_BALANCED;
            Y -> sum = AVL_LEFT_HEAVY;
        }
        else 
        {
            X -> sum = AVL_BALANCED;
            Y -> sum = AVL_BALANCED;
        }

        Z -> sum = 0;
        (*root) = Z;
        *h = 0;
    }

}
void AVL_traversal (Node* root) 
{
    
    if (root != NULL) 
    {   
        printf ("%d ", root -> key);
        AVL_traversal (root -> l);
        AVL_traversal (root -> r);
        return;
    }

}

// AUX FUNCTIONS
void node_balance_after_insert (Node** n, int side, int* h) 
{

    // SIDE == 0 MEANS THE NODE WAS INSERTED IN LEFT-SIDE
    Node* aux = *n;
    if (side == 0) 
    {
        if (aux -> sum == AVL_RIGHT_HEAVY) 
        {
            aux -> sum = AVL_BALANCED;
            *h = 0;
        }
        else if (aux -> sum == AVL_BALANCED) 
        {
            aux -> sum = AVL_LEFT_HEAVY;
        }
        else 
        {
            AVL_R_rotation (n, h);
        }
    }
    else 
    {
        if (aux -> sum == AVL_LEFT_HEAVY) 
        {
            aux -> sum = AVL_BALANCED;
            *h = 0;
        }
        else if (aux -> sum == AVL_BALANCED) 
        {
            aux -> sum = AVL_RIGHT_HEAVY;
        }
        else 
        {
            AVL_L_rotation (n, h);
        }
    }

}
void node_balance_after_remove (Node** n, int side, int* h) 
{

    // SIDE == 0 MEANS THE NODE WAS REMOVED IN RIGHT-SIDE
    Node* aux = *n;
    if (side == 0) 
    {
        if (aux -> sum == AVL_RIGHT_HEAVY) 
        {
            aux -> sum = AVL_BALANCED;
        }
        else if (aux -> sum == AVL_BALANCED) 
        {
            aux -> sum = AVL_LEFT_HEAVY;
            *h = 0;
        }
        else 
        {
            AVL_R_rotation (n, h);
        }
    }
    else 
    {
        if (aux -> sum == AVL_LEFT_HEAVY) 
        {
            *h = 1;
            aux -> sum = AVL_BALANCED;
        }
        else if (aux -> sum == AVL_BALANCED) 
        {
            aux -> sum = AVL_RIGHT_HEAVY;
            *h = 0;
        }
        else 
        {
            AVL_L_rotation (n, h);
        }
    }

}

void node_remove (Node** n, int* h) 
{

    Node* aux = *n;

    // CASE 1: THE NODE HAS LESS THAN ONE SON
    if (aux -> l == NULL || aux -> r == NULL) 
    {
        Node* temp = (aux -> l ? aux -> l : aux -> r);

        *n = temp;
        *h = 1;

        free (aux);    

        return;
    }

    // CASE 2: THE NODE HAS TWO SONS SO WE TRADE THE POSITION WITH THE RIGHT-LEFTMOST CHILD 
    Node* Lmost = node_leftmost (aux -> r);

    node_trade (aux, Lmost);

    AVL_remove_recursive (&(aux -> r), Lmost -> key, h);
    if (*h == 1) 
    {
        node_balance_after_remove (n, 0, h);
    }

}
void node_trade (Node* x, Node* y) 
{
    
    int aux = x -> key;
    x -> key = y -> key;
    y -> key = aux;

}

Node* node_leftmost (Node* n) 
{

    if (n -> l == NULL) 
    {
        return n;
    }
    else 
    {
        return node_leftmost (n -> l);
    }

}

void to_RIGHT (Node* x, Node* y) 
{

    x -> l = y -> r;
    y -> r = x;

}
void to_LEFT (Node* x, Node* y) 
{

    x -> r = y -> l;
    y -> l = x;

}
