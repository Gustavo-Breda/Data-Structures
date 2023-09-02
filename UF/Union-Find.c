#include <stdio.h>
#include <stdlib.h>

void union_set (int* PV, int* RV, int size, int sa, int sb);
int find_set (int* PV, int x);


int main () 
{

    /* UNION-FIND 

        USE: EASE ALGORITHM TO OPERATE IN DISJOINT SETS

    */

    return 0;

}


void union_set (int* PV, int* RV, int size, int sa, int sb) 
{

    if (sa >= size || sb >= size) 
    {
        return;
    }

    int parent_a = find_set (PV, sa);
    int parent_b = find_set (PV, sb);

    int rank_a = RV [parent_a];
    int rank_b = RV [parent_b];

    if (rank_a > rank_b) 
    {
        PV [parent_b] = parent_a;
    }
    else if (rank_a < rank_b) 
    {
        PV [parent_a] = parent_b;
    }
    else 
    {
        PV [parent_a] = parent_b;
        RV [parent_b] += 1;   
    }

}
int find_set (int* PV, int x) 
{

    // PATH HALVING COMPRESSION
    if (PV [x] != x) 
    {
        PV [x] = find_set (PV, PV [x]);
    }

    // PATH HALVING SEPARATION 
    // int y = PV [x]
    // if (y == x)
    // {
    //      return y
    // }
    //
    // int z = PV [y]
    // if (PV [z] == z)
    // {
    //      return z
    // }
    // else
    // {
    //      PV [x] = find_set (PV, z);
    // }

    // PATH HALVING (OFF) 
    // while (PV [x] != x)
    // {
    //      x = PV [x];
    // }

    return PV [x];

}
