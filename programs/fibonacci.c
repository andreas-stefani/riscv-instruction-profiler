/*
========================================================================
Fibonacci Number Calculator - Stack Stress Test
> Stress test: exponential 2^n recursive calls, hammers the call stack.
> Naive implementation intentional — no memoization.
========================================================================
*/
#define N 42

int fib(int n){
    if( n== 1 || n == 2)
        return 1;
    return fib(n-1)+fib(n-2);
}

int main (int argc, char **argv){
    int n = N;
    fib(n);
    return 0;
}
