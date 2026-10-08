#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    if (N == 0) {
        printf("0\n");
        return 0;
    }

    long long *L = malloc(N * sizeof(long long));
    long long *R = malloc(N * sizeof(long long));
    for (int i = 0; i < N; i++) {
        scanf("%lld %lld", &L[i], &R[i]);
    }

    // Sort by L, then by R
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if (L[j] > L[j + 1] || (L[j] == L[j + 1] && R[j] > R[j + 1])) {
                long long tempL = L[j];
                long long tempR = R[j];
                L[j] = L[j + 1];
                R[j] = R[j + 1];
                L[j + 1] = tempL;
                R[j + 1] = tempR;
            }
        }
    }

    int count = 0;
    long long start = L[0], end = R[0];
    for (int i = 1; i < N; i++) {
        if (L[i] <= end) { // overlap or shared endpoint
            if (R[i] > end) end = R[i];
        } else {
            count++;
            start = L[i];
            end = R[i];
        }
    }
    count++; // last interval

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", start, end);
    }

    free(L);
    free(R);
    return 0;
}