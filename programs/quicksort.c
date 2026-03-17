/*
 = *=======================================================================
 Quicksort - Divide & Conquer Sorting
 > Stress test: stresses CPU comparisons, swaps and recursive call stack.
 > Uses middle-element pivot partitioning on a randomly generated array.
 =========================================================================
 */
#define N 1000
#define LOOPS 1000

long seed=1;
long my_rand(){
    seed = seed*1103515245 + 12345;
    return (seed & 0x7FFFFFFF);
}

void QuickSort(int *A, int l, int r){
    if(l>=r)
        return;
    int i=l, j=r, temp;
    int pivot = A[(l+r)/2];
    while(i <= j){
        while(A[i] < pivot) i++;
        while(A[j] > pivot) j--;
        if(i <= j){
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++; j--;
        }
    }
    QuickSort(A, l, j);
    QuickSort(A, i, r);
}

int main (int argc, char **argv){
    int n = N;
    int A[n];

    // repeat LOOPS times, to avoid stack overflow
    for(int j=0 ; j < LOOPS ; j++){
        for(int i=0 ; i<n ; i++)
            A[i]=my_rand()%n;
        int l=0,r=n-1;
        QuickSort(A,l,r);
    }
    return 0;
}
