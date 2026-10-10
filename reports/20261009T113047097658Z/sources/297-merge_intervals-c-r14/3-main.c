#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    if (N == 0) {
        printf("0\n");
        return 0;
    }

    long *L = malloc(N * sizeof(long));
    long *R = malloc(N * sizeof(long));
    if (!L || !R) {
        free(L); free(R);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        scanf("%ld %ld", &L[i], &R[i]);
    }

    // Sort intervals by L, then by R
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if (L[j] > L[j + 1] || (L[j] == L[j + 1] && R[j] > R[j + 1])) {
                long tmpL = L[j];
                long tmpR = R[j];
                L[j] = L[j + 1];
                R[j] = R[j + 1];
                L[j + 1] = tmpL;
                R[j + 1] = tmpR;
            }
        }
    }

    // Merge intervals and store them in original arrays
    int merged_count = 0;
    long cur_L = L[0];
    long cur_R = R[0];

    for (int i = 1; i < N; i++) {
        // Intervals overlap if L[i] <= cur_R (closed intervals, shared endpoints merge)
        if (L[i] <= cur_R) {
            if (R[i] > cur_R) {
                cur_R = R[i];
            }
        } else {
            // No overlap, push current and start new
            L[merged_count] = cur_L;
            R[merged_count] = cur_R;
            merged_count++;
            cur_L = L[i];
            cur_R = R[i];
        }
    }
    // Push the last interval
    L[merged_count] = cur_L;
    R[merged_count] = cur_R;

    printf("%d\n", merged_count);
    for (int i = 0; i < merged_count; i++) {
        printf("%ld %ld\n", L[i], R[i]);
    }

    free(L); free(R);
    return 0;
}