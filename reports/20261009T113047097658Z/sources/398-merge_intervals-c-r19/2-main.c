#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long long *L = malloc(N * sizeof(long long));
    long long *R = malloc(N * sizeof(long long));
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

    // Use arrays to store merged intervals
    int merged_count = 0;
    for (int i = 0; i < N; i++) {
        if (merged_count == 0) {
            L[merged_count] = L[i];
            R[merged_count] = R[i];
        } else {
            // Check if intervals overlap or share an endpoint
            if (R[merged_count - 1] >= L[i]) {
                // Merge: extend the current interval's right endpoint
                if (R[i] > R[merged_count - 1]) {
                    R[merged_count - 1] = R[i];
                }
            } else {
                // No overlap, add new interval
                merged_count++;
                L[merged_count] = L[i];
                R[merged_count] = R[i];
            }
        }
    }

    printf("%d\n", merged_count);
    for (int i = 0; i < merged_count; i++) {
        printf("%lld %lld\n", L[i], R[i]);
    }

    free(L);
    free(R);
    return 0;
}