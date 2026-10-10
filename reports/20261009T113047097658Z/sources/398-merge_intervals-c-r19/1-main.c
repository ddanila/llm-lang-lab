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

    int merged_count = 0;
    long long cur_L = L[0];
    long long cur_R = R[0];

    for (int i = 1; i < N; i++) {
        // Check if intervals overlap or share an endpoint
        if (cur_R >= L[i]) {
            // Merge: extend the current interval's right endpoint
            if (R[i] > cur_R) {
                cur_R = R[i];
            }
        } else {
            // No overlap, output the current merged interval and start a new one
            merged_count++;
            cur_L = L[i];
            cur_R = R[i];
        }
    }

    // Output the last merged interval
    merged_count++;

    printf("%d\n", merged_count);
    for (int i = 0; i < merged_count; i++) {
        printf("%lld %lld\n", L[i], R[i]);
    }

    free(L);
    free(R);
    return 0;
}