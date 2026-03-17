/*
=====================================================================
Prime Factorization - Arithmetic Stress Test
> Stress test: trial division up to sqrt(n), hammers integer div/mod.
> Use a large semiprime (p*q) for maximum ALU stress.
======================================================================
*/
#define P 999999000001

int main (int argc, char **argv){
    // long long to fit
    long long p = P;
            // i <= sqrt(p) same as i*i <= p
    for(long long i=2 ; i*i <= p ; i++){
        while(p % i == 0){
            p = p/i ;
        }
    }
    return 0;
}