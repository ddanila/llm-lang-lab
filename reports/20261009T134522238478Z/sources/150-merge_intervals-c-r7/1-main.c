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

    // Merge intervals
    int merged_count = 0;
    for (int i = 0; i < N; i++) {
        if (merged_count == 0) {
            L[merged_count] = L[idx[i]];
            R[merged_count] = R[idx[i]];
        } else {
            if (L[idx[i]] <= R[merged_count]) {
                // Overlap or shared endpoint -> merge
                R[merged_count] = (R[idx[i]] > R[merged_count]) ? R[idx[i]] : R[merged_count];
            } else {
                // No overlap -> new interval
                merged_count++;
                L[merged_count] = L[idx[i]];
                R[merged_count] = R[idx[i]];
            }
        }
    }

    printf("%d\n", merged_count + 1);
    for (int i = 0; i <= merged_count; i++) {
        printf("%d %d\n", L[i], R[i]);
    }

    free(L);
    free(R);
    return 0;
}