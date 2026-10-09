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

    // Sort by L ascending, then R ascending if equal
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            int swapL = L[j], swapR = R[j];
            if (L[j + 1] < L[j] || (L[j + 1] == L[j] && R[j + 1] < R[j])) {
                L[j] = L[j + 1];
                R[j] = R[j + 1];
                L[j + 1] = swapL;
                R[j + 1] = swapR;
            }
        }
    }

    if (N == 0) {
        free(L);
        free(R);
        printf("0\n");
        return 0;
    }

    // Collect merged intervals into separate arrays
    int *mergedL = malloc(N * sizeof(int));
    int *mergedR = malloc(N * sizeof(int));
    if (!mergedL || !mergedR) {
        free(L);
        free(R);
        printf("0\n");
        return 0;
    }

    int merged_idx = 0;
    int curL = L[0];
    int curR = R[0];

    for (int i = 1; i < N; i++) {
        if (curR >= L[i]) {
            // Overlap or shared endpoint, merge
            if (R[i] > curR) {
                curR = R[i];
            }
        } else {
            // No overlap, save current and start new
            mergedL[merged_idx] = curL;
            mergedR[merged_idx] = curR;
            merged_idx++;
            curL = L[i];
            curR = R[i];
        }
    }
    // Save last interval
    mergedL[merged_idx] = curL;
    mergedR[merged_idx] = curR;

    printf("%d\n", merged_idx + 1);
    for (int i = 0; i <= merged_idx; i++) {
        printf("%d %d\n", mergedL[i], mergedR[i]);
    }

    free(L);
    free(R);
    free(mergedL);
    free(mergedR);
    return 0;
}