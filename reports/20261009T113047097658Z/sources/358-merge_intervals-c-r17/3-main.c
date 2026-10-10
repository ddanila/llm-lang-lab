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
    int num_merged = 0;
    long long merged_L[200], merged_R[200];

    merged_L[num_merged] = L[0];
    merged_R[num_merged] = R[0];
    for (int i = 1; i < n; ++i) {
        if (L[i] <= merged_R[num_merged]) {
            if (R[i] > merged_R[num_merged]) {
                merged_R[num_merged] = R[i];
            }
        } else {
            num_merged++;
            merged_L[num_merged] = L[i];
            merged_R[num_merged] = R[i];
        }
    }

    printf("%d\n", num_merged + 1);
    for (int i = 0; i <= num_merged; ++i) {
        printf("%lld %lld\n", merged_L[i], merged_R[i]);
    }

    free(L);
    free(R);
    return 0;
}