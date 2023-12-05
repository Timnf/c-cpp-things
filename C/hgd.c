#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double hypergeometric(int k, int n, int M, int N) {
    return exp(lgamma(M+1) + lgamma(N-M+1) + lgamma(n+1) + lgamma(N-n+1) - lgamma(k+1) - lgamma(M-k+1) - lgamma(n-k+1) - lgamma(N-n-M+k+1));
}

int main() {
    int k = 3;
    int n = 5;
    int M = 10;
    int N = 20;
    printf("P(X=%d) = %g\n", k, hypergeometric(k, n, M, N));
    return 0;
}