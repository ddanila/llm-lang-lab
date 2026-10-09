#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    int *L = malloc(N > 0 ? sizeof(int) * N : 0);
    int *R = malloc(N > 0 ? sizeof(int) * N : 0);
    if (!L || !R && N > 0) {
        free(L);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &L[i], &R[i]);
    }

    if (N == 0) {
        printf("0\n");
        free(L);
        free(R);
        return 0;
    }

    // Sort by L, then by R for stability
    int idx[201];
    for (int i = 0; i < N; i++) idx[i] = i;

    // Simple bubble sort for N <= 200
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (L[idx[j]] > L[idx[j + 1]] || 
                (L[idx[j]] == L[idx[j + 1]] && R[idx[j]] > R[idx[j + 1]])) {
                int tmp = idx[j];
                idx[j] = idx[j + 1];
                idx[j + 1] = tmp;
            }
        }
    }

    // Merge intervals into a separate array
    int *mL = malloc(N > 0 ? sizeof(int) * N : 0);
    int *mR = malloc(N > 0 ? sizeof(int) * N : 0);
    
    int count = 0;
    mL[0] = L[idx[0]];
    mR[0] = R[idx[0]];
    count = 1;

    for (int i = 1; i < N; i++) {
        if (L[idx[i]] <= mR[count - 1]) {
            // Overlap or shared endpoint -> merge
            if (R[idx[i]] > mR[count - 1]) {
                mR[count - 1] = R[idx[i]];
            }
        } else {
            // No overlap -> new interval
            mL[count] = L[idx[i]];
            mR[count] = R[idx[i]];
            count++;
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d %d\n", mL[i], mR[i]);
    }

    free(L);
    free(R);
    free(mL);
    free(mR);
    return 0;
}