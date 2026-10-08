#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) {
        return 0;
    }

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
                long long tmpL = L[j];
                long long tmpR = R[j];
                L[j] = L[j + 1];
                R[j] = R[j + 1];
                L[j + 1] = tmpL;
                R[j + 1] = tmpR;
            }
        }
    }

    int merged_count = 0;
    long long current_L = L[0];
    long long current_R = R[0];

    for (int i = 1; i < N; i++) {
        // Merge if overlapping: L[i] <= current_R
        if (L[i] <= current_R) {
            if (R[i] > current_R) {
                current_R = R[i];
            }
        } else {
            merged_count++;
            current_L = L[i];
            current_R = R[i];
        }
    }

    // Add the last interval
    merged_count++;

    printf("%d\n", merged_count);
    
    for (int i = 0; i < N; i++) {
        if (L[i] > current_R) {
            printf("%lld %lld\n", L[i], R[i]);
            current_L = L[i];
            current_R = R[i];
        } else if (R[i] > current_R) {
            current_R = R[i];
        }
    }

    free(L);
    free(R);
    return 0;
}