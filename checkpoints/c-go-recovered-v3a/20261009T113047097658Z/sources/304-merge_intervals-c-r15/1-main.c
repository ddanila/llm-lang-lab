#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("0\n");
        return 0;
    }

    long long *L = malloc(n * sizeof(long long));
    long long *R = malloc(n * sizeof(long long));
    if (!L || !R) {
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
    
    // Initialize with the first interval
    merged_L = L[0];
    merged_R = R[0];
    count = 1;

    for (int i = 1; i < n; i++) {
        // Overlap if current L <= previous merged R
        if (L[i] <= merged_R) {
            // Merge: extend the right endpoint if needed
            if (R[i] > merged_R) {
                merged_R = R[i];
            }
        } else {
            // No overlap, start a new interval
            count++;
            merged_L = L[i];
            merged_R = R[i];
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", merged_L, merged_R);
        if (i < count - 1) {
            // Move to next interval
            int j = 0;
            while (j < count && (L[j] != merged_L || R[j] != merged_R)) {
                j++;
            }
            merged_L = L[j];
            merged_R = R[j];
        }
    }

    free(L);
    free(R);
    return 0;
}