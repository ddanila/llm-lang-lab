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
    int merged_count = 0;
    long long *merged_L = malloc(N * sizeof(long long));
    long long *merged_R = malloc(N * sizeof(long long));
    if (!merged_L || !merged_R) return 0;

    merged_L[0] = L[0];
    merged_R[0] = R[0];
    merged_count = 1;

    for (int i = 1; i < N; i++) {
        // Merge if overlap: L[i] <= current_R
        if (L[i] <= merged_R[merged_count - 1]) {
            if (R[i] > merged_R[merged_count - 1]) {
                merged_R[merged_count - 1] = R[i];
            }
        } else {
            merged_count++;
            merged_L[merged_count - 1] = L[i];
            merged_R[merged_count - 1] = R[i];
        }
    }

    printf("%d\n", merged_count);
    for (int i = 0; i < merged_count; i++) {
        printf("%lld %lld\n", merged_L[i], merged_R[i]);
    }

    free(L);
    free(R);
    free(merged_L);
    free(merged_R);
    return 0;
}