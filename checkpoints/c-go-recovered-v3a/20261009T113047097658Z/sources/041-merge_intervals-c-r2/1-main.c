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
    for (int i = 0; i < n; i++) {
        scanf("%ld %ld", &L[i], &R[i]);
    }

    // Sort by L, then R
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

    int count = 1;
    long curL = L[0];
    long curR = R[0];

    for (int i = 1; i < n; i++) {
        // Merge if overlap: curR >= L[i] (closed intervals, shared endpoints merge)
        if (curR >= L[i]) {
            if (R[i] > curR) {
                curR = R[i];
            }
        } else {
            count++;
            curL = L[i];
            curR = R[i];
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%ld %ld\n", curL, curR);
        if (i < count - 1) {
            // Move to next merged interval
            int j = 1;
            while (j < n && L[count + j - 1] == curL) {
                // Skip same start points already handled
                j++;
            }
            // Actually we need to output each merged interval once.
            // Let's restructure: collect merged intervals first.
        }
    }

    free(L);
    free(R);
    return 0;
}