#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) {
        printf("0\n");
        return 0;
    }

    int *L = malloc(N * sizeof(int));
    int *R = malloc(N * sizeof(int));
    if (!L || !R) {
        free(L);
        free(R);
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &L[i], &R[i]);
    }

    // Sort by L, then by R if L is equal
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            int cmp = L[j + 1] - L[j];
            if (cmp > 0 || (cmp == 0 && R[j + 1] < R[j])) {
                int tmpL = L[j], tmpR = R[j];
                L[j] = L[j + 1];
                R[j] = R[j + 1];
                L[j + 1] = tmpL;
                R[j + 1] = tmpR;
            }
        }
    }

    if (N == 0) {
        free(L);
        free(R);
        printf("0\n");
        return 0;
    }

    // Collect merged intervals
    int *mergedL = malloc(N * sizeof(int));
    int *mergedR = malloc(N * sizeof(int));
    if (!mergedL || !mergedR) {
        free(L);
        free(R);
        printf("0\n");
        return 0;
    }

    int curL = L[0];
    int curR = R[0];
    int merged_count = 1;

    for (int i = 1; i < N; i++) {
        if (curR >= L[i]) {
            // Overlap or shared endpoint, merge
            if (R[i] > curR) {
                curR = R[i];
            }
        } else {
            // No overlap, store current and start new
            mergedL[merged_count - 1] = curL;
            mergedR[merged_count - 1] = curR;
            curL = L[i];
            curR = R[i];
            merged_count++;
        }
    }
    // Store last interval
    mergedL[merged_count - 1] = curL;
    mergedR[merged_count - 1] = curR;

    printf("%d\n", merged_count);
    for (int i = 0; i < merged_count; i++) {
        printf("%d %d\n", mergedL[i], mergedR[i]);
    }

    free(L);
    free(R);
    free(mergedL);
    free(mergedR);
    return 0;
}