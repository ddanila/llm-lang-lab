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

    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &L[i], &R[i]);
    }

    // Sort by L ascending, then by R ascending
    int *idx = malloc(N * sizeof(int));
    for (int i = 0; i < N; ++i) idx[i] = i;

    // Simple bubble sort (N <= 200)
    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < N - i - 1; ++j) {
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
    if (N > 0) {
        merged_count = 1;
        for (int i = 0; i < N - 1; ++i) {
            int idx_curr = idx[i];
            int idx_next = idx[i + 1];

            // Check if intervals overlap or touch at endpoints
            // Overlap: L_next <= R_curr
            if (L[idx_next] <= R[idx_curr]) {
                // Merge: extend the current interval's R to max(R_curr, R_next)
                if (R[idx_next] > R[idx_curr]) {
                    R[idx_curr] = R[idx_next];
                }
            } else {
                // No overlap, move to next interval
                merged_count++;
                idx[merged_count + 1] = idx_next; // Not needed but for clarity
            }
        }
    }

    printf("%d\n", merged_count);
    for (int i = 0; i < merged_count; ++i) {
        printf("%d %d\n", L[idx[i]], R[idx[i]]);
    }

    free(L);
    free(R);
    free(idx);
    return 0;
}