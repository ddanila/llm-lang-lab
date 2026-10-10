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

    // Sort by L ascending
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
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

    int merged_count = 0;
    for (int i = 0; i < n; i++) {
        if (merged_count == 0) {
            L[merged_count] = L[i];
            R[merged_count] = R[i];
        } else if (L[i] <= R[merged_count - 1]) {
            if (R[i] > R[merged_count - 1]) {
                R[merged_count - 1] = R[i];
            }
        } else {
            merged_count++;
            L[merged_count] = L[i];
            R[merged_count] = R[i];
        }
    }

    printf("%d\n", merged_count + 1);
    for (int i = 0; i <= merged_count; i++) {
        printf("%ld %ld\n", L[i], R[i]);
    }

    free(L);
    free(R);
    return 0;
}