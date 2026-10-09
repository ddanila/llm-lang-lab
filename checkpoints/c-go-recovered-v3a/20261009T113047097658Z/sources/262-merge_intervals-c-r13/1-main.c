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

    long long *L = malloc(n * sizeof(long long));
    long long *R = malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &L[i], &R[i]);
    }

    // Sort by L, then by R
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
        // Check if intervals overlap or share endpoints
        // Closed intervals [L, R] and [nextL, nextR] overlap if nextL <= end
        if ((long long)L[i] <= end) {
            // Merge
            if (R[i] > end) {
                end = R[i];
            }
        } else {
            // No overlap, output previous interval
            count++;
            start = L[i];
            end = R[i];
        }
    }
    // Output last interval
    count++;

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", L[i], R[i]);
    }

    free(L);
    free(R);
    return 0;
}