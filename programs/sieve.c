/*
======================================================================
Sieve of Eratosthenes | 'Κόσκινο του Ερατοσθένη'
> Stress test: array-heavy branching across a 'boolean' bitmap.
> Marks composite numbers by stepping through multiples of each prime.
=======================================================================
*/
#define N 10000000

static int A[N];

int main (int argc, char **argv){
    int n = N;
    for(int i=0 ; i<n ; i++)
        A[i]=1;
    A[0]=0;
    A[1]=0;
    for(int p = 2 ; p * p <= n ; p++)
        for(int i=p*p ; i < n ; i+=p)
            A[i]=0;
    return 0;
}
