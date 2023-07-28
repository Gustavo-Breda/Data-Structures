#include <stdio.h>
#include <stdlib.h>

// CIURA GAP WHICH HAS THE BEST CASE PERFOMANCE OF O(N * (Log N)^2)
int GAP [8] = {701, 301, 132, 57, 23, 10, 4, 1};

void SL_IS (int* vector, int size);
void SL_BS (int* vector, int size);
void SL_SS (int* vector, int size);
void SL_ShS (int* vector, int size);

void SL_MS (int* vector, int size);
void SL_QS (int* vector, int init, int end);

void MG (int* vector, int* r_vector, int r_size, int* l_vector, int l_size);
void DNF (int* vector, int init, int end, int* max, int* min); 
void show (int* vector, int size);
void trade (int* a, int* b);

int partition (int* vector, int init, int end); 
int median (int* v, int a, int b);


int main () 
{

    /* EXAMPLE 


        int reversed_sorted_list [] = {98, 91, 87, 84, 79, 76, 75, 73, 69, 65};

        int size = sizeof(reversed_sorted_list) / sizeof(reversed_sorted_list[0]);

        SL_QS (reversed_sorted_list, size);

        show (reversed_sorted_list, size);

    */

    return 0;

}


void SL_IS (int* vector, int size) 
{
 
    /* INSERTION SORT 
    
        CONCEPT: STABLE COMPARISON BASED ALGORITHM THAT WORKS LIKE WE SORTING CARDS IN OUR HANDS
        COMPLEXITY: IT HAS O(N^2) ON ALL CASES

    */

    if (size <= 1) 
    {
        return;
    }

    for (int index_external = 1; index_external < size; index_external ++) 
    {

        // S1: THE EXTERNAL INDEX'S CARD USED AS REFERENCE OF "OUTER" FOR
        int data = vector [index_external];

        // S2: UPDATE THE INDEX INTERNAL
        int index_internal = index_external;

        // S3: FIND THE SMALLER
        for (index_internal -= 1; (index_internal >= 0) && (vector [index_internal] >= data); index_internal --) 
        {
            vector [index_internal + 1] = vector [index_internal];
        }

        // STEP 4: UPDATE THE VALUE
        vector [index_internal + 1] = data;

    }

}
void SL_BS (int* vector, int size) 
{

    /* BUBBLE SORT 

        CONCEPT: STABLE COMPARISOM BASED ALGORITHM
        COMPLEXITY: WORST CASE HAS O(N^2) BUT AUGMENTED VERSION BETTER CASE HAS O(N)

    */

    if (size <= 1) 
    {
        return;
    }

    // OUTER LOOP: ITERATES OVER THE VECTORS'S UNSORTED PART 
    for (int index_external = size - 1; index_external > 0; index_external --) 
    {

        // S1: VAR TO STORE IF THE ITERATION HAD TRADE
        int trades = 0;

        // S1: COMPARE EACH ELEMENT ANT PUT THE MINOR BEHIND, THE HIGHER REMAIN IN LAST POSITION
        for (int index_internal = 1; index_internal <= index_external; index_internal ++) 
        {

            int i = index_internal - 1;

            if (vector [i] >= vector [index_internal]) 
            {
                trade (&(vector [index_internal]), &(vector[i]));
                trades = 1;
            }
            
        }

        // S2: IF HAS NO TRADES SO THE LIST IS ALREADY SORTED
        if (trades == 0) 
        {
            break;
        }

    }
    
}
void SL_SS (int* vector, int size) 
{

    /* SELECTION SORT 

        CONCEPT: NOT STABLE COMPARISON BASED ALGORITHM 
        COMPLEXITY: IT HAS O(N^2) IN ALL CASES

    */

    if (size <= 1) 
    {
        return;
    }

    // OUTER LOOP: ITERATES OVER THE VECTOR'S UNSORTED PART
    for (int index_external = 0; index_external < size; index_external ++) 
    {
        
        // S1: VAR TO STORE THE REFERENCE VALUE
        int aux_index = index_external;

        // INNER LOOP: ITERATE OVER SO AS TO FIND THE MINIMUM VALUE
        for (int index_internal = index_external + 1; index_internal < size; index_internal ++) 
        {

            if (vector [aux_index] > vector [index_internal]) 
            {
                aux_index = index_internal;
            }

        }
        
        // S2: UPDATE THE VECTOR INDEX POSITION AND UPDATE THE LOOP ITERATION
        trade (&vector [index_external], &vector [aux_index]);        

    }

}
void SL_ShS (int* vector, int size) 
{
    
    /* SHELL SORT 

        CONCEPT: VARIATION OF INSERTION SORT WORKING OVER GAPS
        COMPLEXITY: IT HAS O(N^2) BUT IN THE BETTER CASE HAS O(N * lN)
    
    */

    if (size <= 1) 
    {
        return;
    }

    for (int i = 0; i < 8; i ++) 
    {

        int value = GAP [i];

        // OUTER LOOP: ITERATATION START ON GAP [value] TO SIZE
        for (int index_external = value; index_external < size; index_external ++) 
        {
            
            // S1: UPDATE THE VALUE USED AS REFERENCE
            int key = vector [index_external];
            int index_internal;

            // S2: FIND THE SMALLLER SEPARATED BY THE GAP AND HIGHER THAN THE INDEX EXTERNAL
            for (index_internal = index_external; (index_internal >= value) && (vector [index_internal - value] > key); index_internal -= value) 
            {
                vector [index_internal] = vector [index_internal - value];
            }

            // S3: UPDATE THE VALUE ON INDEX EXTERNAL
            vector [index_internal] = key;

        }

    }

}

void SL_MS (int* vector, int size) 
{

    /* MERGE SORT 

        CONCEPT: STABLE DIVIDE-TO-CONQUER BASED ALGORITHM AND NECESSITIES ADDITIONAL MEMORY TO WORK
        COMPLEXITY: THE WORST CASE HAS O(N * lN)

    */

    if (size <= 1) 
    {
        return;
    }

    int center = size / 2;
    int r_size = size - center;
    int l_size = center;

    // S1: CREATE THE VECTORS
    int* r_vector = (int*) malloc (r_size * sizeof(int));
    int* l_vector = (int*) malloc (l_size * sizeof(int));

    // S2: ASSIGN THE VALUES TO EACH VECTOR
    for (int i = 0; i < l_size; i ++) 
    {
        l_vector [i] = vector [i];
    }
    for (int i = center; i < r_size + center; i ++) 
    {
        r_vector [i - center] = vector [i];
    }

   // S3: REPEAT THE ABOVE STEPS THROUGH THE SUB-ARRAYS
   SL_MS (r_vector, r_size);
   SL_MS (l_vector, l_size);
   
   // S4: BOUND THE TWO SUB-ARRAYS
   MG (vector, r_vector, r_size, l_vector, l_size);

   // S5: FREE THE TWO SUB-ARRAYS CREATED
   free (r_vector);
   free (l_vector);

}
void SL_QS (int* vector, int init, int end) 
{

    /* QUICK SORT 

        CONCEPT: STABLE AND IN-PLACE DIVIDED-TO-CONQUER BASED ALGORITHM 
        COMPLEXITY: THE WORST CASE HAS O(N^2) BUT AVERAGE HAS O(N * ln) AND BETTER CAN HAS O(N) IF USED DNF (MANY EQUAL ELEMENTS)

    */
   
    if (end <= init) 
    {
        return;
    }


    /* LOMUTO ALGOTITHM

        // S1: PIVOT SELECTION THROUGH THE PARTITION ALGORITHM
        int partition_index = partition (vector, init, end);

        // S2: CALL RECURSIVELY THE TWO VECTORS CREATED
        SL_QS (vector, init, partition_index - 1);
        SL_QS (vector, partition_index + 1, end);

    */
    
    // S1: PIVOT SELECTION THROUGH THE DUTCH-NATIONAL-FLAG ALGORITHM
    int max, min;
    DNF (vector, init, end, &max, &min);

    // S2: CALL RECURSIVELY THE SUB-ARRAYS
    SL_QS (vector, init, min - 1);
    SL_QS (vector, max + 1, end); 
   
}

// AUX FUNCTIONS
void MG (int* vector, int* r_vector, int r_size, int* l_vector, int l_size) 
{

    // CONCEPT: SORTING LIKE ASSESS THE TOP OF TWO PILES
    int r_TOP = 0;
    int l_TOP = 0;
    int i = 0;

    // S4.1: MAKE THE COMPARISONS BETWEEN THE "TOP OF PILES"
    while ((r_TOP < r_size) && (l_TOP < l_size))
    {

        if (r_vector [r_TOP] <= l_vector [l_TOP]) 
        {
            vector [i++] = r_vector [r_TOP++];
        }
        else 
        {
            vector [i++] = l_vector [l_TOP++];
        }

    }

    // S4.2: EMPTYING THE REMAINING ELEMENTS OF r_vector
    while (r_TOP < r_size) 
    {
        vector [i++] = r_vector [r_TOP++];
    }

    // S4.2: EMPTYING THE REMAINING ELEMENTS OF l_vector
    while (l_TOP < l_size) 
    {
        vector [i++] = l_vector [l_TOP++];
    }

}
void DNF (int* vector, int init, int end, int* max, int* min) 
{

    int pivot = vector [init];

    int i = init;
    *min = init;
    *max = end;

    // CONCEPT: THE ALGORITHYM DIVIDE THE ARRAY ON SECTIONS {<= && == && >=} IN COMPARISON TO THE PIVOT
    while (i <= *max) 
    {
        
        if (vector [i] < pivot) 
        {
            trade (&(vector[i]), &(vector[*min]));
            i ++;
            (*min)++;
        } 
        else if (vector [i] > pivot) 
        {
            trade (&(vector[i]), &(vector[*max]));
            (*max)--;
        } 
        else 
        {
            i++;
        }

    }

}
void show (int* vector, int size) 
{

    printf ("List:");
    for (int i = 0; i < size; i ++)
    {
        printf (" %d", vector [i]);
    } 
    
}
void trade (int* a, int* b) 
{

    int aux = *a;
    *a = *b;
    *b = aux;

}

int partition (int* vector, int init, int end) 
{
    
    // S1: FIND THE MEDIAN BETWEEN THE VALUES TO HELP IN CERTAIN SCENARIOS
    int index = median (vector, init, end);
    int pivot = vector [index];
    
    // S2: PUT THE MEDIAN AT THE FINAL
    if (pivot != vector [end]) 
    {
        trade (&(vector [index]), &(vector [end]));
    }

    int RIGHT = end;
    int LEFT = init;

    // S3: LESSER THAN PIVOT TO ITS LEFT AND GREATER TO ITS RIGHT
    while (RIGHT > LEFT) 
    {   

        while (vector [RIGHT] >= pivot) 
        {
            RIGHT--;
        }

        while (vector [LEFT] <= pivot)
        {
            LEFT++;
        }

        if (RIGHT > LEFT) 
        {   
            trade (&(vector [LEFT++]), &(vector [RIGHT--]));
        }

    }

    // S4: UPDATE THE PIVOT CORRECT INDEX
    trade (&(vector[LEFT]), &(vector[end]));
    index = LEFT;

    return LEFT;

}
int median (int* v, int a, int b) 
{

    int mid = (a + b) / 2;

    if ((v [a] >= v [b] && v [a] <= v [mid]) || (v [a] <= v [b] && v[a] >= v [mid])) 
    {
        return a;
    } 
    else if ((v [b] >= v[a] && v [b] <= v [mid]) || (v [b] <= v[a] && v [b] >= v [mid])) 
    {
        return b;
    } 
    else 
    {
        return mid;
    }

}
