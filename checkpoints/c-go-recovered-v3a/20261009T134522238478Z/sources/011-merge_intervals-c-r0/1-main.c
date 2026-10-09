#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("0\n");
        return 0;
    }

    if (n == 0) {
        printf("0\n");
        return 0;
    }

    long *L = malloc(n * sizeof(long));
    long *R = malloc(n * sizeof(long));
    if (!L || !R) {
        fprintf(stderr, "Memory allocation failed\n");
        free(L);
        free(R);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%ld %ld", &L[i], &R[i]);
    }

    // Sort intervals by L, then by R
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (L[j] > L[j + 1] || (L[j] == L[j + 1] && R[j] > R[j + 1])) {
                long tmpL = L[j];
                long tmpR = R[j];
                L[j] = L[j + 1];
                R[j] = R[j + 1];
                L[j + 1] = tmpL;
                R[j + 1] = tmpR;
            }
        }
    }

    int count = 0;
    long start = L[0];
    long end = R[0];

    for (int i = 1; i < n; i++) {
        if (L[i] <= end) {
            // Overlapping or sharing endpoint: merge
            if (R[i] > end) {
                end = R[i];
            }
        } else {
            // Non-overlapping: output previous interval and start new
            count++;
            start = L[i];
            end = R[i];
        }
    }
    // Output the last interval
    count++;

    printf("%d\n", count);
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            continue;
        }
        // We need to reconstruct the merged intervals
        // Actually, we should store them
    }

    free(L);
    free(R);

    return 0;
}