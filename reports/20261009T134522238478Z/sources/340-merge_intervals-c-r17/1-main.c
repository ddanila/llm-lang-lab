#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    int *L = NULL, *R = NULL;
    if (N > 0) {
        L = malloc(N * sizeof(int));
        R = malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &L[i], &R[i]);
        }
    }

    if (N == 0) {
        printf("0\n");
        free(L);
        free(R);
        return 0;
    }

    // Sort by L ascending, then R ascending
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (L[i] > L[j] || (L[i] == L[j] && R[i] > R[j])) {
                int tmpL = L[i]; L[i] = L[j]; L[j] = tmpL;
                int tmpR = R[i]; R[i] = R[j]; R[j] = tmpR;
            }
        }
    }

    // Merge intervals
    int count = 1;
    for (int i = 1; i < N; i++) {
        // Overlap if L[i] <= current_R (closed intervals, overlap at endpoints)
        if (L[i] <= R[count - 1]) {
            // Merge: extend current interval if needed
            if (R[i] > R[count - 1]) {
                R[count - 1] = R[i];
            }
        } else {
            count++;
            L[count - 1] = L[i];
            R[count - 1] = R[i];
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d %d\n", L[i], R[i]);
    }

    free(L);
    free(R);
    return 0;
}