#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) {
        printf("0\n");
        return 0;
    }

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

    // Sort intervals by L ascending, then R ascending
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            int swapped = 0;
            if (L[j] > L[j + 1]) {
                long long tmpL = L[j];
                L[j] = L[j + 1];
                L[j + 1] = tmpL;
                swapped = 1;
            } else if (L[j] == L[j + 1] && R[j] > R[j + 1]) {
                long long tmpL = L[j];
                L[j] = L[j + 1];
                L[j + 1] = tmpL;
                long long tmpR = R[j];
                R[j] = R[j + 1];
                R[j + 1] = tmpR;
                swapped = 1;
            }
            if (swapped) {
                long long tmpR = R[j];
                R[j] = R[j + 1];
                R[j + 1] = tmpR;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < N; i++) {
        if (i == 0) {
            L[count] = L[i];
            R[count] = R[i];
        } else {
            // Check overlap: [L[i], R[i]] overlaps with [L[count], R[count]]
            // Overlap condition: L[i] <= R[count] (closed intervals, shared endpoints merge)
            if (L[i] <= R[count]) {
                // Merge: extend the right endpoint if needed
                if (R[i] > R[count]) {
                    R[count] = R[i];
                }
            } else {
                count++;
                L[count] = L[i];
                R[count] = R[i];
            }
        }
    }

    printf("%d\n", count + 1);
    for (int i = 0; i <= count; i++) {
        printf("%lld %lld\n", L[i], R[i]);
    }

    free(L);
    free(R);
    return 0;
}