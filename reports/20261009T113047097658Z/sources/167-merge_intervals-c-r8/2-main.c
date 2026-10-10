#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

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

    // Sort by L ascending, then R ascending
    for (int i = 0; i < N - 1; i++) {
        int j = i + 1;
        while (j < N) {
            if (L[j] < L[i]) {
                long long tmpL = L[i]; L[i] = L[j]; L[j] = tmpL;
                long long tmpR = R[i]; R[i] = R[j]; R[j] = tmpR;
            } else if (L[j] == L[i]) {
                if (R[j] < R[i]) {
                    long long tmpR2 = R[i]; R[i] = R[j]; R[j] = tmpR2;
                }
            }
            j++;
        }
    }

    // Merge intervals
    int count = 1;
    long long currentL = L[0];
    long long currentR = R[0];

    for (int i = 1; i < N; i++) {
        if (currentR >= L[i]) {
            // Overlapping or shared endpoint -> merge
            if (R[i] > currentR) {
                currentR = R[i];
            }
        } else {
            // No overlap, output current interval and start new one
            printf("%lld %lld\n", currentL, currentR);
            count++;
            currentL = L[i];
            currentR = R[i];
        }
    }
    // Output the last interval
    printf("%lld %lld\n", currentL, currentR);

    free(L);
    free(R);
    return 0;
}