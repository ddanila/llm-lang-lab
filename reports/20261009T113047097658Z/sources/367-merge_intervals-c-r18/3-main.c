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
    long long *mL = malloc((n + 1) * sizeof(long long));
    long long *mR = malloc((n + 1) * sizeof(long long));
    
    long long start = L[0];
    long long end = R[0];

    for (int i = 1; i < n; i++) {
        // Two closed intervals [a,b] and [c,d] overlap if max(a,c) <= min(b,d).
        // They merge if they share at least one point: end >= L[i]
        if (end >= L[i]) {
            if (R[i] > end) {
                end = R[i];
            }
        } else {
            mL[mcount] = start;
            mR[mcount] = end;
            mcount++;
            start = L[i];
            end = R[i];
        }
    }
    mL[mcount] = start;
    mR[mcount] = end;
    mcount++;

    printf("%d\n", mcount);
    for (int i = 0; i < mcount; i++) {
        printf("%lld %lld\n", mL[i], mR[i]);
    }

    free(L);
    free(R);
    free(mL);
    free(mR);
    return 0;
}