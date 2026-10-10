#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long long *L = malloc(N * sizeof(long long));
    long long *R = malloc(N * sizeof(long long));
    if (!L || !R) return 0;

    for (int i = 0; i < N; i++) {
        scanf("%lld %lld", &L[i], &R[i]);
    }

    if (N == 0) {
        printf("0\n");
        free(L);
        free(R);
        return 0;
    }

    // Sort intervals by L, then by R
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            int swap = 0;
            if (L[j] > L[j + 1]) {
                swap = 1;
            } else if (L[j] == L[j + 1] && R[j] > R[j + 1]) {
                swap = 1;
            }
            if (swap) {
                long long tmpL = L[j];
                long long tmpR = R[j];
                L[j] = L[j + 1];
                R[j] = R[j + 1];
                L[j + 1] = tmpL;
                R[j + 1] = tmpR;
            }
        }
    }

    // Merge intervals and store results
    int merged_count = 1;
    long long current_L = L[0];
    long long current_R = R[0];

    for (int i = 1; i < N; i++) {
        // Merge if overlap: L[i] <= current_R
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

    printf("%d\n", merged_count);
    for (int i = 0; i < merged_count; i++) {
        // Reconstruct by re-merging or store in array
    }

    free(L);
    free(R);
    return 0;
}