#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node Node;
struct node 
{   
    
    int marked;
    int order;
    int data;

    Node* father;
    Node* child;

    Node* r;
    Node* l;

};

typedef struct Fibonacci FHP;
struct Fibonacci 
{   

    Node* min;
    int n;

};

FHP* FHP_union (FHP* H1, FHP* H2);
FHP* FHP_create ();

Node* FHP_remove_minimum (FHP* H); 
Node* FHP_minimun (FHP* H); 
Node* FHP_node (int data);

void FHP_link (FHP* H, Node* y, Node* x); 
void FHP_insert (FHP* H, int data);
void FHP_delete (FHP* H, Node* x);
void FHP_consolidate (FHP* H); 

void FHP_decrease (FHP* H, Node* x, int k);
void FHP_cut (FHP* H, Node* x, Node* y);
void FHP_cascade_cut (FHP* H, Node* y);

void CDLL_concatenate (Node* ra, Node* rb);
void CDLL_insert (Node* x, Node* y);
void CDLL_remove (Node* x);

void trade (Node** a, Node** b);
int F (int n);


int main () 
{

    /* FIBONACCI HEAP 

        // USE: NUMBER OF "EXTRACT MINIMUN" AND "DELETE" IS LOWER IN COMPARISOM TO OTHER OPERATIONS
        // BIG O: EXTRACT MINIMUM AND DELETE HAS O(LOG(N)) AND THE REST HAS (AMORTIZED) O(1) 

    */

    return 0;

}


FHP* FHP_union (FHP* H1, FHP* H2) 
{

    FHP* H = FHP_create ();
    H -> min = H1 -> min;

    CDLL_concatenate (H1 -> min, H2 -> min);

    if (H1 -> min == NULL || (H2 -> min != NULL && H2 -> min < H1 -> min)) 
    {
        H -> min = H2 -> min;
    }
    H -> n = H1 -> n + H2 -> n;
    
    return H;
    
}
FHP* FHP_create () 
{

    FHP* root = (FHP*) malloc (sizeof (FHP));
    if (root != NULL) 
    {
        root -> min = NULL;
        root -> n = 0;

        return root;
    }
    else 
    {
        printf ("\nAllocation error");
        exit (1);
    }
    
}

Node* FHP_remove_minimum (FHP* H) 
{

    Node* z = FHP_minimun (H);

    if (z != NULL) 
    {
        Node* aux_cc = NULL;
        Node* aux = z;

        // S1: REMOVE EACH CHILD OF MINIMUM NODE AND PLACE IT TO LINKED LIST
        if (aux -> child != NULL) 
        {
            aux_cc = aux -> child;

            do 
            {

                aux = aux_cc -> r;
                
                CDLL_insert (H -> min, aux_cc);

                aux_cc -> father = NULL;
                aux_cc = aux;

            } while (aux != z -> child);
        }

        // S2: REMOVE Z FROM LINKED LIST
        CDLL_remove (z);
        H -> n -= 1;

        // S3: FORM THE NEW MINIMUM
        if (z == z -> r) 
        {
            H -> min = NULL;
            return NULL;
        }
        else 
        {
            H -> min = z -> r;

            // FREE THE OLD CONECTIONS OF Z
            z -> child = NULL;
            z -> r = z;
            z -> l = z;

            FHP_consolidate (H);
        }
    }

    return z;

}
Node* FHP_minimun (FHP* H) 
{
    
    if (H -> min == NULL) 
    {
        printf ("\n Fibonacci Heap Empty \n");
        return NULL;
    }
    return (H -> min);

}
Node* FHP_node (int data) 
{

    Node* new_node = (Node*) malloc (sizeof (Node));
    if (new_node != NULL) 
    {
        new_node -> data = data;
        new_node -> marked = 0;
        new_node -> order = 0;

        new_node -> father = NULL;
        new_node -> child = NULL;
        new_node -> r = new_node;
        new_node -> l = new_node;

        return new_node;
    }
    else 
    {
        printf ("\nAllocation error");
        exit (1);
    }
    
}

void FHP_link (FHP* H, Node* y, Node* x) 
{

    // REMOVE Y FROM THE ROOT LIST
    CDLL_remove (y);

    if (H -> min == y) 
    {
        H -> min = H -> min -> r;
    }

    // PUT Y ON THE ROOT LIST OF THE CHILDRENS OF X
    if (x -> child != NULL) 
    {
        CDLL_insert (x -> child, y);
    }
    else 
    {
        y -> r = y;
        y -> l = y;
    }

    y -> father = x;
    x -> child = y; 

    x -> order += 1;
    y -> marked = 0;

}
void FHP_insert (FHP* H, int data) 
{

    Node* node = FHP_node (data);

    if (H -> min == NULL) 
    {
        H -> min = node;
    }
    else 
    {
        CDLL_insert (H -> min, node);

        if (H -> min -> data > data) 
        {
            H -> min = node;
        }
    }

    H -> n += 1;

}
void FHP_delete (FHP* H, Node* x) 
{

    FHP_decrease (H, x, INT_MIN);
    FHP_remove_minimum (H);

}
void FHP_consolidate (FHP* H) 
{

    // S1: CREATE THE AUXILIAR ARRAY OF POINTERS
    Node* aux_vector [F(H -> n)];
    for (int i = 0; i <= F(H -> n); i ++) 
    {
        aux_vector [i] = NULL;
    }

    Node* aux_x = H -> min;
    Node* aux_y = NULL;
    Node* aux_t = NULL;
    int aux_o;

    // S2: EACH NODE OF H ROOT LIST TO AUX_VECTOR
    do 
    {

        aux_t = aux_x -> r;
        aux_o = aux_x -> order;

        while (aux_vector [aux_o] != NULL) 
        {

            aux_y = aux_vector [aux_o];
            if (aux_y -> data < aux_x -> data) 
            {
                trade (&aux_y, &aux_x);
            }
            
            FHP_link (H, aux_y, aux_x);
            aux_vector [aux_o] = NULL;
            aux_o += 1;

        }

        aux_vector [aux_o] = aux_x;

        aux_x = aux_t;

    } while (aux_t != H -> min);

    H -> min = NULL;
    // S3: RECREATE THE H LINKED LIST
    for (int i = 0; i <= F(H -> n); i ++) 
    {
        if (aux_vector [i] != NULL) 
        {
            if (H -> min == NULL) 
            {
                H -> min = aux_vector [i];
            }
            else 
            {
                CDLL_insert (H -> min, aux_vector [i]);
                if (H -> min -> data > aux_vector [i] -> data) 
                {
                    H -> min = aux_vector [i];
                }
            }
        }
    }

}

void FHP_decrease (FHP* H, Node* x, int k) 
{

    if (x -> data < k) 
    {
        printf ("\nInvalid data");
        exit (1);
    }
    
    Node* y = x -> father;
    x -> data = k;

    if (y != NULL && x -> data < y -> data) 
    {
        FHP_cut (H, x, y);
        FHP_cascade_cut (H, y);
    }
    if (x -> data < H -> min -> data) 
    {
        H -> min = x;
    }

}
void FHP_cut (FHP* H, Node* x, Node* y) 
{
    
    CDLL_remove (x);
    CDLL_insert (H -> min, x);

    x -> father = NULL;
    x -> marked = 0;
    y -> order -= 1;

}
void FHP_cascade_cut (FHP* H, Node* y) 
{
    
    Node* z = y -> father;
    if (z != NULL) 
    {
        if (y -> marked == 0) 
        {
             y -> marked = 1;
        }
        else 
        {
            FHP_cut (H, y, z);
            FHP_cascade_cut (H, z);
        }
    }

}

// CIRCULAR DOUBLY LINKED LIST FUNCTIONS
void CDLL_concatenate (Node* ra, Node* rb) 
{
    
    if (ra == NULL) 
    {
        return;
    }
    else if (rb == NULL) 
    {
        return;
    }

    Node* aux_rb = rb -> r;
    Node* aux_ra = ra;

    while (aux_ra -> r != aux_ra) 
    {
        aux_ra = aux_ra -> r;
    }

    rb -> r = ra;
    ra -> l = rb;

    aux_rb -> l = aux_ra;
    aux_ra -> r = aux_rb;

}
void CDLL_insert (Node* x, Node* y) 
{

    // UPDATE THE BROTHERHOOD OF LEFT NODE OF x
    x -> l -> r = y;
    y -> l = x -> l;

    // UPDATE THE LEFT x BROTHERHOOD
    x -> l = y;
    y -> r = x;

}
void CDLL_remove (Node* x) 
{

    x -> r -> l = x -> l;
    x -> l -> r = x -> r;

}

// AUX FUNCTIONS
void trade (Node** a, Node** b) 
{

    Node* aux = *a;
    *a = *b;
    *b = aux;

}
int F (int n) 
{

    // EXPLANATION: FUNCTION TO CALCULATE LOG (n)
    int result = -1;
    while (n > 0) 
    {
        n >>= 1;
        result ++;
    }
    
    return result;

}
