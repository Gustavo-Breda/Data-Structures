#include <stdio.h>
#include <stdlib.h>

void HP_insert_max (int* list, int key, int* n);
void HP_remove_max (int* list, int* n);
void HP_sort (int* list, int n);

void HP_maxify (int* list, int index, int n);
void HP_max (int* list, int index, int n);
void HP_min (int* list, int index, int n);

int father (int i);
int lson (int i);
int rson (int i);


int main () 
{

    /* HEAP 

        // USE: lists or vectors when nodes has numbers, however, is necessary assess if MAX or MIN

        // FATHER: (i / 2) or (i - 1 / 2)
        // RIGHT-CHILD: (2i + 1) or (2i + 2)
        // LEFT-CHILD: (2i) or (2i + 1)

    */

    return 0;

}


void HP_insert_max (int* list, int key, int* n) 
{
    
    // OVERVIEW: WE HAVE TWO OPERATIONS CONDENSED AT HERE (INSERT_KEY AND INCREASE_KEY)
    int temp;
    int i;
    
    *n += 1;
    list [*n] = key;

    i = *n;
    while ((i >= 0) && (list [father (i)] < list [i])) 
    {
        temp = list [father (i)];
        list [father (i)] = list [i];
        list [i] = temp;

        i = father (i);
    }

}
void HP_remove_max (int* list, int* n) 
{

    if (*n < 0) 
    {
        return;
    }
    else 
    {
        list [0] = list [*n];
        HP_max (list, 0, *n - 1);
        *n -= 1;
    }

}
void HP_sort (int* list, int n) 
{

    // OVERVIEW: HAS O(N LN) AND SORTS IN PLACE
    int temp;
    int i;

    // S1: CONTRUCT HEAP
    HP_maxify (list, father (n), n);

    // S2: FIRST NODE POSITION TO LAST AND MAX-HEAP IT
    for (i = n; i >= 1; i --) 
    {
        temp = list [0];
        list [0] = list [i];
        list [i] = temp;

        HP_max (list, 0, i - 1);
    }

}

void HP_maxify (int* list, int index, int n) 
{

    for (int i = index; i >= 0; i --) 
    {
        HP_max (list, i, n);
    }

}
void HP_max (int* list, int index, int n) 
{

    int largest;
    int ls;
    int rs;

    ls = lson (index);
    rs = rson (index);

    if (ls <= n && list [ls] > list [index]) 
    {
        largest = ls;
    }
    else 
    {
        largest = index;
    }

    if (rs <= n && list [rs] > list [largest]) 
    {
        largest = rs;
    }
    
    if (largest != index) 
    {
        int temp = list [index];
        list [index] = list [largest];
        list [largest] = temp;

        HP_max (list, largest, n);
    }

}
void HP_min (int* list, int index, int n) 
{

    int smallest;
    int ls;
    int rs;

    ls = lson (index);
    rs = rson (index);

    if (ls <= n && list [ls] < list [index]) 
    {
        smallest = ls;
    }
    else 
    {
        smallest = index;
    }

    if (rs <= n && list [rs] < list [smallest]) 
    {
        smallest = rs;
    }
    
    if (smallest != index) 
    {
        int temp = list [index];
        list [index] = list [smallest];
        list [smallest] = temp;

        HP_min (list, smallest, n);
    }


}

// AUX FUNCTIONS
int father (int i) 
{
    return ((i - 1) / 2);
}
int lson (int i) 
{
    return (2 * i + 1);
}
int rson (int i) 
{
    return (2 * i + 2);
}
