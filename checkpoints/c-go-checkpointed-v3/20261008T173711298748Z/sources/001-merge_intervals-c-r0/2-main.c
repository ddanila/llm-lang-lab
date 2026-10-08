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
    if (!L || !R) {
        free(L);
        free(R);
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        scanf("%lld %lld", &L[i], &R[i]);
    }

    // Sort by L, then by R
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
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

    int count = 0;
    long long current_start = L[0];
    long long current_end = R[0];

    for (int i = 1; i < n; ++i) {
        if (L[i] <= current_end) {
            // Overlap or shared endpoint, merge
            if (R[i] > current_end) {
                current_end = R[i];
            }
        } else {
            // No overlap, push current interval and start new one
            count++;
            current_start = L[i];
            current_end = R[i];
        }
    }
    count++; // Push the last interval

    printf("%d\n", count);
    for (int i = 0; i < count; ++i) {
        printf("%lld %lld\n", current_start, current_end);
    }

    free(L);
    free(R);
    return 0;
}