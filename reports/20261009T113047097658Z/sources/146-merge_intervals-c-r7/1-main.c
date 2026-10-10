#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    int *L = malloc(N * sizeof(int));
    int *R = malloc(N * sizeof(int));
    if (!L || !R) return 1;

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &L[i], &R[i]);
    }

    if (N == 0) {
        printf("0\n");
        free(L);
        free(R);
        return 0;
    }

    // Sort by L, then by R
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if (L[j] > L[j + 1] || (L[j] == L[j + 1] && R[j] > R[j + 1])) {
                int tmpL = L[j];
                int tmpR = R[j];
                L[j] = L[j + 1];
                R[j] = R[j + 1];
                L[j + 1] = tmpL;
                R[j + 1] = tmpR;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < N; i++) {
        if (i == 0 || L[i] > R[count - 1]) {
            count++;
        } else {
            // Merge: extend the end of the current interval
            if (R[i] > R[count - 1]) {
                R[count - 1] = R[i];
            }
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