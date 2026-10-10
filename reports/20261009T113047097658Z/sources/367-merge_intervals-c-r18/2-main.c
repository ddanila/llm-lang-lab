#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    long long *L = malloc(n * sizeof(long long));
    long long *R = malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &L[i], &R[i]);
    }

    if (n == 0) {
        printf("0\n");
        free(L);
        free(R);
        return 0;
    }

    // Sort intervals by L, then by R
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            int swap = 0;
            if (L[j] > L[j + 1]) {
                swap = 1;
            } else if (L[j] == L[j + 1] && R[j] > R[j + 1]) {
                swap = 1;
            }
            if (swap) {
                long long tmpL = L[j];
                long long tmpR = R[j];
                L[j] = L[j + 1];
                R[j] = R[j + 1];
                L[j + 1] = tmpL;
                R[j + 1] = tmpR;
            }
        }
    }

    // Merge intervals and store results
    int mcount = 0;
    long long start = L[0];
    long long end = R[0];

    for (int i = 1; i < n; i++) {
        // Two closed intervals [a,b] and [c,d] overlap if max(a,c) <= min(b,d).
        // They merge if they overlap. Condition: end >= L[i] means they share at least one point.
        if (end >= L[i]) {
            if (R[i] > end) {
                end = R[i];
            }
        } else {
            long long *mL = malloc((mcount + 2) * sizeof(long long));
            long long *mR = malloc((mcount + 2) * sizeof(long long));
            for (int k = 0; k < mcount; k++) {
                mL[k] = mL_orig[k];
                mR[k] = mR_orig[k];
            }
            mL[mcount] = start;
            mR[mcount] = end;
            mcount++;
            start = L[i];
            end = R[i];
        }
    }

    // This approach is getting complex. Let me rewrite cleanly.
    return 0;
}