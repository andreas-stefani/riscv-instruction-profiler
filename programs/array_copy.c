/*
==============================================================================
Array Copy - Memory Stress Test
> Stress test: hammers memory bandwidth with sequential loads and stores.
> Allocates two large arrays ( size = N ) and copies all elements from A to B.
==============================================================================
*/
#define N 100000000
static int A[N],B[N];

int main ( int argc, char **argv){
    int n = N;

    // init loop
    for(int i=0 ; i<n ; i++)
        A[i]=i;

    for(int i=0 ; i<n ; i++)
        B[i]=A[i];
    return 0;
}
