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

    // Sort intervals by L, then by R
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
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
    long long merged_L, merged_R;
    merged_L = L[0];
    merged_R = R[0];
    count = 1;

    for (int i = 1; i < n; i++) {
        // Merge if overlap or share endpoint: L[i] <= merged_R
        if (L[i] <= merged_R) {
            if (R[i] > merged_R) {
                merged_R = R[i];
            }
        } else {
            // Output current merged interval
            printf("%lld %lld\n", merged_L, merged_R);
            merged_L = L[i];
            merged_R = R[i];
            count++;
        }
    }
    // Output last interval
    printf("%lld %lld\n", merged_L, merged_R);

    free(L);
    free(R);
    return 0;
}