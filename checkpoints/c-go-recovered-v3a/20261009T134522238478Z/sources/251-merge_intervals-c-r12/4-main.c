#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("0\n");
        return 0;
    }

    long long *L = malloc((n + 1) * sizeof(long long));
    long long *R = malloc((n + 1) * sizeof(long long));
    if (!L || !R) {
        free(L);
        free(R);
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &L[i], &R[i]);
    }

    if (n == 0) {
        printf("0\n");
        free(L);
        free(R);
        return 0;
    }

    // Sort intervals by L, then R
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

    // Merge intervals into a separate array starting at index n
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (count == 0) {
            L[n + count] = L[i];
            R[n + count] = R[i];
        } else if (L[i] <= R[n + count]) {
            // overlap or shared endpoint - merge
            if (R[i] > R[n + count]) {
                R[n + count] = R[i];
            }
        } else {
            // no overlap - add new interval
            count++;
            L[n + count] = L[i];
            R[n + count] = R[i];
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", L[n + i], R[n + i]);
    }

    free(L);
    free(R);
    return 0;
}