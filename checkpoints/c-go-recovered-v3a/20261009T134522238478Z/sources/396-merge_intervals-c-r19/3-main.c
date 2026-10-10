#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long long *L = malloc(N > 0 ? sizeof(long long) * N : 0);
    long long *R = malloc(N > 0 ? sizeof(long long) * N : 0);
    if (!L || !R) {
        free(L); free(R);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        scanf("%lld %lld", &L[i], &R[i]);
    }

    if (N == 0) {
        printf("0\n");
        free(L); free(R);
        return 0;
    }

    // Sort intervals by L, then by R
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            int swap = 0;
            if (L[j] > L[j + 1]) swap = 1;
            else if (L[j] == L[j + 1] && R[j] > R[j + 1]) swap = 1;
            if (swap) {
                long long tL = L[j]; L[j] = L[j + 1]; L[j + 1] = tL;
                long long tR = R[j]; R[j] = R[j + 1]; R[j + 1] = tR;
            }
        }
    }

    // Collect merged intervals into arrays
    int count = 0;
    long long start = L[0], end = R[0];

    for (int i = 1; i < N; i++) {
        if (L[i] <= end) {
            // Overlap or share endpoint, merge
            if (R[i] > end) end = R[i];
        } else {
            // No overlap, push current interval and start new one
            count++;
            L[count] = start;
            R[count] = end;
            start = L[i];
            end = R[i];
        }
    }
    // Push the last interval
    count++;
    L[count] = start;
    R[count] = end;

    printf("%d\n", count);
    for (int i = 0; i <= count; i++) {
        printf("%lld %lld\n", L[i], R[i]);
    }

    free(L); free(R);
    return 0;
}