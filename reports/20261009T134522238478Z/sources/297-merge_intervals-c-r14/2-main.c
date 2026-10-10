#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    long *L = malloc(n * sizeof(long));
    long *R = malloc(n * sizeof(long));
    for (int i = 0; i < n; i++) {
        scanf("%ld %ld", &L[i], &R[i]);
    }

    if (n == 0) {
        printf("0\n");
        free(L);
        free(R);
        return 0;
    }

    // Sort by L ascending, then R descending for stable merge
    int k = n;
    for (int i = 0; i < k - 1; i++) {
        for (int j = 0; j < k - i - 1; j++) {
            if (L[j] > L[j + 1]) {
                long tmp = L[j];
                L[j] = L[j + 1];
                L[j + 1] = tmp;
                tmp = R[j];
                R[j] = R[j + 1];
                R[j + 1] = tmp;
            }
        }
    }

    int m = 0;
    for (int i = 0; i < n; i++) {
        if (m == 0) {
            L[m] = L[i];
            R[m] = R[i];
        } else {
            // Check if current interval overlaps with last merged interval
            if (L[i] <= R[m - 1]) {
                // Merge: extend the end if needed
                if (R[i] > R[m - 1]) {
                    R[m - 1] = R[i];
                }
            } else {
                // No overlap, add as new interval
                m++;
                L[m] = L[i];
                R[m] = R[i];
            }
        }
    }

    printf("%d\n", m + 1);
    for (int i = 0; i <= m; i++) {
        printf("%ld %ld\n", L[i], R[i]);
    }

    free(L);
    free(R);
    return 0;
}