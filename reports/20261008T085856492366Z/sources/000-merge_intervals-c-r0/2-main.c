#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    if (n == 0) {
        printf("0\n");
        return 0;
    }

    long long *L = malloc(n * sizeof(long long));
    long long *R = malloc(n * sizeof(long long));

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &L[i], &R[i]);
    }

    // Sort by L, then by R
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (L[j] > L[j + 1] || (L[j] == L[j + 1] && R[j] > R[j + 1])) {
                long long tmpL = L[j];
                long long tmpR = R[j];
                L[j] = L[j + 1];
                R[j] = R[j + 1];
                L[j + 1] = tmpL;
                R[j + 1] = tmpR;
            }
        }
    }

    // Merge intervals
    int count = 0;
    long long start = L[0];
    long long end = R[0];

    for (int i = 1; i < n; i++) {
        if (L[i] <= end) { // Overlap or shared endpoint
            if (R[i] > end) {
                end = R[i];
            }
        } else {
            count++;
            start = L[i];
            end = R[i];
        }
    }
    count++; // Last interval

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", start, end);
        if (i < count - 1) {
            // Move to next merged interval
            int idx = 0;
            long long curL = start;
            long long curR = end;
            while (idx < n && (curL != L[idx] || curR != R[idx])) {
                idx++;
            }
            idx++; // Skip the merged one
            while (idx < n) {
                if (L[idx] <= curR) {
                    if (R[idx] > curR) curR = R[idx];
                } else {
                    break;
                }
                idx++;
            }
            start = L[idx];
            end = curR;
        }
    }

    free(L);
    free(R);

    return 0;
}