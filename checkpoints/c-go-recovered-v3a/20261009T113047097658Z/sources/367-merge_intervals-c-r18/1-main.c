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

    int count = 0;
    long long start = L[0];
    long long end = R[0];

    for (int i = 1; i < n; i++) {
        // Merge if overlapping or sharing endpoint: overlap condition is end >= next.start - 1? 
        // No, problem says "overlap (including shared endpoints, but NOT merely adjacent integers)"
        // Closed intervals [a,b] and [c,d] overlap if max(a,c) <= min(b,d).
        // They do NOT merge if they are just adjacent like [1,2] and [3,4] because 2+1=3, no gap but not sharing endpoint.
        // Overlap condition: end >= next.L - 1? No.
        // If we have [1,2] and [2,3], they share endpoint 2, so merge -> [1,3].
        // If we have [1,2] and [3,4], no shared endpoint, no overlap, don't merge.
        // So condition is: end >= next.L (since intervals are closed, if end == next.L, they share that point).
        if (end >= L[i]) {
            if (R[i] > end) {
                end = R[i];
            }
        } else {
            count++;
            start = L[i];
            end = R[i];
        }
    }
    count++; // last interval

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        // We need to output the merged intervals. But we only stored start/end of current merge.
        // We need to recompute or store them. Let's redo with storing.
    }

    // Actually, let's redo: store merged intervals in arrays.
    free(L);
    free(R);

    n = 0;
    long long *mL = malloc(200 * sizeof(long long));
    long long *mR = malloc(200 * sizeof(long long));
    int mcount = 0;

    start = L[0];
    end = R[0];

    for (int i = 1; i < n; i++) {
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

    free(mL);
    free(mR);
    return 0;
}