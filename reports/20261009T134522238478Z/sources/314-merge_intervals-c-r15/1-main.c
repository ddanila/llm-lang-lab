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
    int *idx = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) idx[i] = i;

    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (L[idx[j]] < L[idx[i]] || 
                (L[idx[j]] == L[idx[i]] && R[idx[j]] < R[idx[i]])) {
                int tmp = idx[i];
                idx[i] = idx[j];
                idx[j] = tmp;
            }
        }
    }

    // Merge intervals
    int count = 1;
    for (int i = 1; i < N; i++) {
        long long currentL = L[idx[i]];
        long long currentR = R[idx[i]];
        if (currentL <= count - 1 + 1) { // Overlap or share endpoint: currentL <= merged_R + 1 is not correct for closed intervals
            // For closed intervals [a,b] and [c,d], they overlap if c <= b.
            // Since we sorted by L, currentL >= previous L.
            // Check if currentL <= previous R (merged interval)
            // But we need to track the merged interval's R.
        }
    }

    // Let's redo merging properly
    long long *mergedL = malloc(N * sizeof(long long));
    long long *mergedR = malloc(N * sizeof(long long));
    int m = 0;

    mergedL[0] = L[idx[0]];
    mergedR[0] = R[idx[0]];

    for (int i = 1; i < N; i++) {
        if (L[idx[i]] <= mergedR[m]) { // Overlap or share endpoint
            if (R[idx[i]] > mergedR[m]) {
                mergedR[m] = R[idx[i]];
            }
        } else {
            m++;
            mergedL[m] = L[idx[i]];
            mergedR[m] = R[idx[i]];
        }
    }

    printf("%d\n", m + 1);
    for (int i = 0; i <= m; i++) {
        printf("%lld %lld\n", mergedL[i], mergedR[i]);
    }

    free(L);
    free(R);
    free(idx);
    free(mergedL);
    free(mergedR);

    return 0;
}