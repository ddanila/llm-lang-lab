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

    // Merge intervals - store results in arrays
    long long *merged_L = malloc(n * sizeof(long long));
    long long *merged_R = malloc(n * sizeof(long long));
    int count = 0;

    merged_L[count] = L[0];
    merged_R[count] = R[0];
    count++;

    for (int i = 1; i < n; i++) {
        if (L[i] <= merged_R[count - 1]) { // Overlap or shared endpoint
            if (R[i] > merged_R[count - 1]) {
                merged_R[count - 1] = R[i];
            }
        } else {
            merged_L[count] = L[i];
            merged_R[count] = R[i];
            count++;
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", merged_L[i], merged_R[i]);
    }

    free(L);
    free(R);
    free(merged_L);
    free(merged_R);

    return 0;
}