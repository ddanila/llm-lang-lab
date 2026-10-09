#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    long long *L = malloc(n * sizeof(long long));
    long long *R = malloc(n * sizeof(long long));
    if (!L || !R) return 1;

    for (int i = 0; i < n; ++i) {
        scanf("%lld %lld", &L[i], &R[i]);
    }

    if (n == 0) {
        printf("0\n");
        free(L);
        free(R);
        return 0;
    }

    // Sort by L ascending, then by R ascending
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
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

    // Merge and store results in arrays
    int merged_count = 0;
    long long merged_L[200], merged_R[200];

    merged_L[merged_count] = L[0];
    merged_R[merged_count] = R[0];
    for (int i = 1; i < n; ++i) {
        if (L[i] <= merged_R[merged_count]) {
            if (R[i] > merged_R[merged_count]) {
                merged_R[merged_count] = R[i];
            }
        } else {
            merged_count++;
            merged_L[merged_count] = L[i];
            merged_R[merged_count] = R[i];
        }
    }

    printf("%d\n", merged_count);
    for (int i = 0; i <= merged_count; ++i) {
        printf("%lld %lld\n", merged_L[i], merged_R[i]);
    }

    free(L);
    free(R);
    return 0;
}